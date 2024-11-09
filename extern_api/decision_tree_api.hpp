// decision_tree_api.h  
#ifndef DECISION_TREE_API_H  
#define DECISION_TREE_API_H  

#ifdef __cplusplus  
extern "C" {
#endif  

	__declspec(dllexport) void RunDecisionTree(const char* trainFile, const char* testFile, const char* resultFile);

#ifdef __cplusplus  
}
#endif  

#endif // DECISION_TREE_API_H