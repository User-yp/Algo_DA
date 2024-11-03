#include "../utils/common.hpp"

 /* ���������� */
class BinarySearchTree {
private:
    TreeNode* root;

public:
    /* ���췽�� */
    BinarySearchTree() {
        // ��ʼ������
        root = nullptr;
    }

    /* �������� */
    ~BinarySearchTree() {
        freeMemoryTree(root);
    }

    /* ��ȡ���������ڵ� */
    TreeNode* getRoot() {
        return root;
    }

    /* ���ҽڵ� */
    TreeNode* search(int num) {
        TreeNode* cur = root;
        // ѭ�����ң�Խ��Ҷ�ڵ������
        while (cur != nullptr) {
            // Ŀ��ڵ��� cur ����������
            if (cur->val < num)
                cur = cur->right;
            // Ŀ��ڵ��� cur ����������
            else if (cur->val > num)
                cur = cur->left;
            // �ҵ�Ŀ��ڵ㣬����ѭ��
            else
                break;
        }
        // ����Ŀ��ڵ�
        return cur;
    }

    /* ����ڵ� */
    void insert(int num) {
        // ����Ϊ�գ����ʼ�����ڵ�
        if (root == nullptr) {
            root = new TreeNode(num);
            return;
        }
        TreeNode* cur = root, * pre = nullptr;
        // ѭ�����ң�Խ��Ҷ�ڵ������
        while (cur != nullptr) {
            // �ҵ��ظ��ڵ㣬ֱ�ӷ���
            if (cur->val == num)
                return;
            pre = cur;
            // ����λ���� cur ����������
            if (cur->val < num)
                cur = cur->right;
            // ����λ���� cur ����������
            else
                cur = cur->left;
        }
        // ����ڵ�
        TreeNode* node = new TreeNode(num);
        if (pre->val < num)
            pre->right = node;
        else
            pre->left = node;
    }

    /* ɾ���ڵ� */
    void remove(int num) {
        // ����Ϊ�գ�ֱ����ǰ����
        if (root == nullptr)
            return;
        TreeNode* cur = root, * pre = nullptr;
        // ѭ�����ң�Խ��Ҷ�ڵ������
        while (cur != nullptr) {
            // �ҵ���ɾ���ڵ㣬����ѭ��
            if (cur->val == num)
                break;
            pre = cur;
            // ��ɾ���ڵ��� cur ����������
            if (cur->val < num)
                cur = cur->right;
            // ��ɾ���ڵ��� cur ����������
            else
                cur = cur->left;
        }
        // ���޴�ɾ���ڵ㣬��ֱ�ӷ���
        if (cur == nullptr)
            return;
        // �ӽڵ����� = 0 or 1
        if (cur->left == nullptr || cur->right == nullptr) {
            // ���ӽڵ����� = 0 / 1 ʱ�� child = nullptr / ���ӽڵ�
            TreeNode* child = cur->left != nullptr ? cur->left : cur->right;
            // ɾ���ڵ� cur
            if (cur != root) {
                if (pre->left == cur)
                    pre->left = child;
                else
                    pre->right = child;
            }
            else {
                // ��ɾ���ڵ�Ϊ���ڵ㣬������ָ�����ڵ�
                root = child;
            }
            // �ͷ��ڴ�
            delete cur;
        }
        // �ӽڵ����� = 2
        else {
            // ��ȡ��������� cur ����һ���ڵ�
            TreeNode* tmp = cur->right;
            while (tmp->left != nullptr) {
                tmp = tmp->left;
            }
            int tmpVal = tmp->val;
            // �ݹ�ɾ���ڵ� tmp
            remove(tmp->val);
            // �� tmp ���� cur
            cur->val = tmpVal;
        }
    }
};

/* Driver Code */
int main() {
    /* ��ʼ������������ */
    BinarySearchTree* bst = new BinarySearchTree();
    // ��ע�⣬��ͬ�Ĳ���˳������ɲ�ͬ�Ķ������������п�������һ������������
    vector<int> nums = { 8, 4, 12, 2, 6, 10, 14, 1, 3, 5, 7, 9, 11, 13, 15 };
    for (int num : nums) {
        bst->insert(num);
    }
    cout << endl << "��ʼ���Ķ�����Ϊ\n" << endl;
    printTree(bst->getRoot());

    /* ���ҽڵ� */
    TreeNode* node = bst->search(7);
    cout << endl << "���ҵ��Ľڵ����Ϊ " << node << "���ڵ�ֵ = " << node->val << endl;

    /* ����ڵ� */
    bst->insert(16);
    cout << endl << "����ڵ� 16 �󣬶�����Ϊ\n" << endl;
    printTree(bst->getRoot());

    /* ɾ���ڵ� */
    bst->remove(1);
    cout << endl << "ɾ���ڵ� 1 �󣬶�����Ϊ\n" << endl;
    printTree(bst->getRoot());
    bst->remove(2);
    cout << endl << "ɾ���ڵ� 2 �󣬶�����Ϊ\n" << endl;
    printTree(bst->getRoot());
    bst->remove(4);
    cout << endl << "ɾ���ڵ� 4 �󣬶�����Ϊ\n" << endl;
    printTree(bst->getRoot());

    // �ͷ��ڴ�
    delete bst;

    return 0;
}
