#include "../utils/common.hpp"

 /* �жϵ�ǰ״̬�Ƿ�Ϊ�� */
bool isSolution(vector<TreeNode*>& state) {
    return !state.empty() && state.back()->val == 7;
}

/* ��¼�� */
void recordSolution(vector<TreeNode*>& state, vector<vector<TreeNode*>>& res) {
    res.push_back(state);
}

/* �ж��ڵ�ǰ״̬�£���ѡ���Ƿ�Ϸ� */
bool isValid(vector<TreeNode*>& state, TreeNode* choice) {
    return choice != nullptr && choice->val != 3;
}

/* ����״̬ */
void makeChoice(vector<TreeNode*>& state, TreeNode* choice) {
    state.push_back(choice);
}

/* �ָ�״̬ */
void undoChoice(vector<TreeNode*>& state, TreeNode* choice) {
    state.pop_back();
}

/* �����㷨�������� */
void backtrack(vector<TreeNode*>& state, vector<TreeNode*>& choices, vector<vector<TreeNode*>>& res) {
    // ����Ƿ�Ϊ��
    if (isSolution(state)) {
        // ��¼��
        recordSolution(state, res);
    }
    // ��������ѡ��
    for (TreeNode* choice : choices) {
        // ��֦�����ѡ���Ƿ�Ϸ�
        if (isValid(state, choice)) {
            // ���ԣ�����ѡ�񣬸���״̬
            makeChoice(state, choice);
            // ������һ��ѡ��
            vector<TreeNode*> nextChoices{ choice->left, choice->right };
            backtrack(state, nextChoices, res);
            // ���ˣ�����ѡ�񣬻ָ���֮ǰ��״̬
            undoChoice(state, choice);
        }
    }
}

/* Driver Code */
int main() {
    TreeNode* root = vectorToTree(vector<int>{1, 7, 3, 4, 5, 6, 7});
    cout << "\n��ʼ��������" << endl;
    printTree(root);

    // �����㷨
    vector<TreeNode*> state;
    vector<TreeNode*> choices = { root };
    vector<vector<TreeNode*>> res;
    backtrack(state, choices, res);

    cout << "\n������и��ڵ㵽�ڵ� 7 ��·����Ҫ��·���в�����ֵΪ 3 �Ľڵ�" << endl;
    for (vector<TreeNode*>& path : res) {
        vector<int> vals;
        for (TreeNode* node : path) {
            vals.push_back(node->val);
        }
        printVector(vals);
    }
}
