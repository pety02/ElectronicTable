#include <iostream>
#include <vector>
#include <string>

#include "CmdInterpreter.h"
#include "ExpressionParser.h"
#include "Table.h"

struct Workflow {
    std::string input;
    std::string output;
    bool expectFailure;
    std::string description;
};

void evaluateAll(Table& table) {
    for (const auto& el : table.getCells()) {
        double value = ExpressionParser::evaluate(
            el.second.expression,
            table,
            el.first
        );
        table.setCachedValue(value, el.first);
    }
}

void executeWorkflow(const Workflow& wf) {
    CmdInterpreter cmd;
    Table table;

    std::cout << "\n========================================\n";
    std::cout << "WORKFLOW: " << wf.description << "\n";
    std::cout << "INPUT: " << wf.input << "\n";
    std::cout << "========================================\n";

    try {
        cmd.load(wf.input, table);

        std::cout << "\n--- Expressions ---\n";
        cmd.printAllExpressions(table);

        std::cout << "\n--- Evaluating ---\n";
        evaluateAll(table);

        std::cout << "\n--- Values ---\n";
        cmd.printAllValues(table);

        if (!wf.output.empty()) {
            std::cout << "\n--- Saving to " << wf.output << " ---\n";
            cmd.save(wf.output, table);

            std::cout << "\n--- Reload & Verify ---\n";
            Table verify;
            cmd.load(wf.output, verify);
            evaluateAll(verify);
            cmd.printAllValues(verify);
        }

        if (wf.expectFailure) {
            std::cerr << "Expected failure but workflow succeeded\n";
        } else {
            std::cout << "Workflow completed successfully\n";
        }
    }
    catch (const std::exception& e) {
        if (wf.expectFailure) {
            std::cout << "Expected failure caught: " << e.what() << "\n";
        } else {
            throw;
        }
    }
}

int main() {
    std::vector<Workflow> workflows = {
    {
        "../public/workflow_init.csv",
        "../public/out_init.csv",
        false,
        "Base arithmetic and absolute references"
    },
    {
        "../public/workflow_relative.csv",
        "../public/out_relative.csv",
        false,
        "Relative cell references"
    },
    {
        "../public/workflow_logic.csv",
        "../public/out_logic.csv",
        false,
        "Logical operators and IF expressions"
    },
    {
        "../public/workflow_complex.csv",
        "../public/out_complex.csv",
        false,
        "Complex dependency chains"
    },
    {
        "../public/workflow_division_by_zero.csv",
        "",
        true,
        "Division by zero detection"
    },
    {
        "../public/workflow_missing_reference.csv",
        "",
        true,
        "Missing cell reference detection"
    },
    {
        "../public/workflow_deep_nesting.csv",
        "../public/out_deep.csv",
        false,
        "Deeply nested IF expressions"
    }
    };

    for (const auto& wf : workflows) {
        try {
            executeWorkflow(wf);
        }
        catch (const std::exception& e) {
            std::cerr << "\nUNEXPECTED ERROR: " << e.what() << "\n";
        }
    }

    std::cout << "\n=== ALL WORKFLOWS EXECUTED ===\n";

    return 0;
}