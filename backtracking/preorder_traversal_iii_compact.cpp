#include "../utils/common.hpp"

vector<TreeNode*> path;
vector<vector<TreeNode*>> res;

/* ǰ������������� */
void preOrder(TreeNode* root) {
    // ��֦
    if (root == nullptr || root->val == 3) {
        return;
    }
    // ����
    path.push_back(root);
    if (root->val == 7) {
        // ��¼��
        res.push_back(path);
    }
    preOrder(root->left);
    preOrder(root->right);
    // ����
    path.pop_back();
}

/* Driver Code */
int main() {
    TreeNode* root = vectorToTree(vector<int>{1, 7, 3, 4, 5, 6, 7});
    cout << "\n��ʼ��������" << endl;
    printTree(root);

    // ǰ�����
    preOrder(root);

    cout << "\n������и��ڵ㵽�ڵ� 7 ��·����Ҫ��·���в�����ֵΪ 3 �Ľڵ�" << endl;
    for (vector<TreeNode*>& path : res) {
        vector<int> vals;
        for (TreeNode* node : path) {
            vals.push_back(node->val);
        }
        printVector(vals);
    }
}
