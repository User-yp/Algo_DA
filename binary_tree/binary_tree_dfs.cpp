#include "../utils/common.hpp"

 // ��ʼ���б����ڴ洢��������
vector<int> vec;

/* ǰ����� */
void preOrder(TreeNode* root) {
    if (root == nullptr)
        return;
    // �������ȼ������ڵ� -> ������ -> ������
    vec.push_back(root->val);
    preOrder(root->left);
    preOrder(root->right);
}

/* ������� */
void inOrder(TreeNode* root) {
    if (root == nullptr)
        return;
    // �������ȼ��������� -> ���ڵ� -> ������
    inOrder(root->left);
    vec.push_back(root->val);
    inOrder(root->right);
}

/* ������� */
void postOrder(TreeNode* root) {
    if (root == nullptr)
        return;
    // �������ȼ��������� -> ������ -> ���ڵ�
    postOrder(root->left);
    postOrder(root->right);
    vec.push_back(root->val);
}

/* Driver Code */
int main() {
    /* ��ʼ�������� */
    // ���������һ��������ֱ�����ɶ������ĺ���
    TreeNode* root = vectorToTree(vector<int>{1, 2, 3, 4, 5, 6, 7});
    cout << endl << "��ʼ��������\n" << endl;
    printTree(root);

    /* ǰ����� */
    vec.clear();
    preOrder(root);
    cout << endl << "ǰ������Ľڵ��ӡ���� = ";
    printVector(vec);

    /* ������� */
    vec.clear();
    inOrder(root);
    cout << endl << "��������Ľڵ��ӡ���� = ";
    printVector(vec);

    /* ������� */
    vec.clear();
    postOrder(root);
    cout << endl << "��������Ľڵ��ӡ���� = ";
    printVector(vec);

    return 0;
}
