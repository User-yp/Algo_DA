#include "../utils/common.hpp"

vector<TreeNode*> res;

/* ǰ�����������һ */
void preOrder(TreeNode* root) {
    if (root == nullptr) {
        return;
    }
    if (root->val == 7) {
        // ��¼��
        res.push_back(root);
    }
    preOrder(root->left);
    preOrder(root->right);
}

/* Driver Code */
int main() {
    TreeNode* root = vectorToTree(vector<int>{1, 7, 3, 4, 5, 6, 7});
    cout << "\n��ʼ��������" << endl;
    printTree(root);

    // ǰ�����
    preOrder(root);

    cout << "\n�������ֵΪ 7 �Ľڵ�" << endl;
    vector<int> vals;
    for (TreeNode* node : res) {
        vals.push_back(node->val);
    }
    printVector(vals);
}
