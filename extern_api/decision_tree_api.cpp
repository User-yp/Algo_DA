// decision_tree_api.cpp  
#include "decision_tree_api.hpp"
#include "../decision_tree/decision_tree.cpp"


extern "C" {

    __declspec(dllexport) void RunDecisionTree(const char* trainFile, const char* testFile, const char* resultFile) {
        // 初始化决策树  
        DecisionTree* decisionTree = nullptr;
        InputReader trainInputReader(trainFile);
        decisionTree = new DecisionTree(trainInputReader.getTable());

        // 处理测试文件并生成结果  
        InputReader testInputReader(testFile);
        Table test = testInputReader.getTable();

        OutputPrinter outputPrinter(resultFile);
        outputPrinter.addLine(outputPrinter.joinByTab(test.attrName));
        for (int i = 0; i < test.data.size(); i++) {
            vector<string> result = test.data[i];
            result.push_back(decisionTree->guess(test.data[i]));
            outputPrinter.addLine(outputPrinter.joinByTab(result));
        }
        delete decisionTree;
    }


}