#include "../utils/common.hpp"

 /* ������� */
vector<int> levelOrder(TreeNode* root) {
    // ��ʼ�����У�������ڵ�
    queue<TreeNode*> queue;
    queue.push(root);
    // ��ʼ��һ���б����ڱ����������
    vector<int> vec;
    while (!queue.empty()) {
        TreeNode* node = queue.front();
        queue.pop();              // ���г���
        vec.push_back(node->val); // ����ڵ�ֵ
        if (node->left != nullptr)
            queue.push(node->left); // ���ӽڵ����
        if (node->right != nullptr)
            queue.push(node->right); // ���ӽڵ����
    }
    return vec;
}

/* Driver Code */
int main() {
    /* ��ʼ�������� */
    // ���������һ��������ֱ�����ɶ������ĺ���
    TreeNode* root = vectorToTree(vector<int>{1, 2, 3, 4, 5, 6, 7});
    cout << endl << "��ʼ��������\n" << endl;
    printTree(root);

    /* ������� */
    vector<int> vec = levelOrder(root);
    cout << endl << "��������Ľڵ��ӡ���� = ";
    printVector(vec);

    return 0;
}
