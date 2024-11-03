#include "../utils/common.hpp"

 /* AVL �� */
class AVLTree {
private:
    /* ���½ڵ�߶� */
    void updateHeight(TreeNode* node) {
        // �ڵ�߶ȵ�����������߶� + 1
        node->height = max(height(node->left), height(node->right)) + 1;
    }

    /* �������� */
    TreeNode* rightRotate(TreeNode* node) {
        TreeNode* child = node->left;
        TreeNode* grandChild = child->right;
        // �� child Ϊԭ�㣬�� node ������ת
        child->right = node;
        node->left = grandChild;
        // ���½ڵ�߶�
        updateHeight(node);
        updateHeight(child);
        // ������ת�������ĸ��ڵ�
        return child;
    }

    /* �������� */
    TreeNode* leftRotate(TreeNode* node) {
        TreeNode* child = node->right;
        TreeNode* grandChild = child->left;
        // �� child Ϊԭ�㣬�� node ������ת
        child->left = node;
        node->right = grandChild;
        // ���½ڵ�߶�
        updateHeight(node);
        updateHeight(child);
        // ������ת�������ĸ��ڵ�
        return child;
    }

    /* ִ����ת������ʹ���������»ָ�ƽ�� */
    TreeNode* rotate(TreeNode* node) {
        // ��ȡ�ڵ� node ��ƽ������
        int _balanceFactor = balanceFactor(node);
        // ��ƫ��
        if (_balanceFactor > 1) {
            if (balanceFactor(node->left) >= 0) {
                // ����
                return rightRotate(node);
            }
            else {
                // ������������
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
        }
        // ��ƫ��
        if (_balanceFactor < -1) {
            if (balanceFactor(node->right) <= 0) {
                // ����
                return leftRotate(node);
            }
            else {
                // ������������
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
        }
        // ƽ������������ת��ֱ�ӷ���
        return node;
    }

    /* �ݹ����ڵ㣨���������� */
    TreeNode* insertHelper(TreeNode* node, int val) {
        if (node == nullptr)
            return new TreeNode(val);
        /* 1. ���Ҳ���λ�ò�����ڵ� */
        if (val < node->val)
            node->left = insertHelper(node->left, val);
        else if (val > node->val)
            node->right = insertHelper(node->right, val);
        else
            return node;    // �ظ��ڵ㲻���룬ֱ�ӷ���
        updateHeight(node); // ���½ڵ�߶�
        /* 2. ִ����ת������ʹ���������»ָ�ƽ�� */
        node = rotate(node);
        // ���������ĸ��ڵ�
        return node;
    }

    /* �ݹ�ɾ���ڵ㣨���������� */
    TreeNode* removeHelper(TreeNode* node, int val) {
        if (node == nullptr)
            return nullptr;
        /* 1. ���ҽڵ㲢ɾ�� */
        if (val < node->val)
            node->left = removeHelper(node->left, val);
        else if (val > node->val)
            node->right = removeHelper(node->right, val);
        else {
            if (node->left == nullptr || node->right == nullptr) {
                TreeNode* child = node->left != nullptr ? node->left : node->right;
                // �ӽڵ����� = 0 ��ֱ��ɾ�� node ������
                if (child == nullptr) {
                    delete node;
                    return nullptr;
                }
                // �ӽڵ����� = 1 ��ֱ��ɾ�� node
                else {
                    delete node;
                    node = child;
                }
            }
            else {
                // �ӽڵ����� = 2 ��������������¸��ڵ�ɾ�������øýڵ��滻��ǰ�ڵ�
                TreeNode* temp = node->right;
                while (temp->left != nullptr) {
                    temp = temp->left;
                }
                int tempVal = temp->val;
                node->right = removeHelper(node->right, temp->val);
                node->val = tempVal;
            }
        }
        updateHeight(node); // ���½ڵ�߶�
        /* 2. ִ����ת������ʹ���������»ָ�ƽ�� */
        node = rotate(node);
        // ���������ĸ��ڵ�
        return node;
    }

public:
    TreeNode* root; // ���ڵ�

    /* ��ȡ�ڵ�߶� */
    int height(TreeNode* node) {
        // �սڵ�߶�Ϊ -1 ��Ҷ�ڵ�߶�Ϊ 0
        return node == nullptr ? -1 : node->height;
    }

    /* ��ȡƽ������ */
    int balanceFactor(TreeNode* node) {
        // �սڵ�ƽ������Ϊ 0
        if (node == nullptr)
            return 0;
        // �ڵ�ƽ������ = �������߶� - �������߶�
        return height(node->left) - height(node->right);
    }

    /* ����ڵ� */
    void insert(int val) {
        root = insertHelper(root, val);
    }

    /* ɾ���ڵ� */
    void remove(int val) {
        root = removeHelper(root, val);
    }

    /* ���ҽڵ� */
    TreeNode* search(int val) {
        TreeNode* cur = root;
        // ѭ�����ң�Խ��Ҷ�ڵ������
        while (cur != nullptr) {
            // Ŀ��ڵ��� cur ����������
            if (cur->val < val)
                cur = cur->right;
            // Ŀ��ڵ��� cur ����������
            else if (cur->val > val)
                cur = cur->left;
            // �ҵ�Ŀ��ڵ㣬����ѭ��
            else
                break;
        }
        // ����Ŀ��ڵ�
        return cur;
    }

    /*���췽��*/
    AVLTree() : root(nullptr) {
    }

    /*��������*/
    ~AVLTree() {
        freeMemoryTree(root);
    }
};

void testInsert(AVLTree& tree, int val) {
    tree.insert(val);
    cout << "\n����ڵ� " << val << " ��AVL ��Ϊ" << endl;
    printTree(tree.root);
}

void testRemove(AVLTree& tree, int val) {
    tree.remove(val);
    cout << "\nɾ���ڵ� " << val << " ��AVL ��Ϊ" << endl;
    printTree(tree.root);
}

/* Driver Code */
int main() {
    /* ��ʼ���� AVL �� */
    AVLTree avlTree;

    /* ����ڵ� */
    // ���ע����ڵ��AVL ������α���ƽ���
    testInsert(avlTree, 1);
    testInsert(avlTree, 2);
    testInsert(avlTree, 3);
    testInsert(avlTree, 4);
    testInsert(avlTree, 5);
    testInsert(avlTree, 8);
    testInsert(avlTree, 7);
    testInsert(avlTree, 9);
    testInsert(avlTree, 10);
    testInsert(avlTree, 6);

    /* �����ظ��ڵ� */
    testInsert(avlTree, 7);

    /* ɾ���ڵ� */
    // ���עɾ���ڵ��AVL ������α���ƽ���
    testRemove(avlTree, 8); // ɾ����Ϊ 0 �Ľڵ�
    testRemove(avlTree, 5); // ɾ����Ϊ 1 �Ľڵ�
    testRemove(avlTree, 4); // ɾ����Ϊ 2 �Ľڵ�

    /* ��ѯ�ڵ� */
    TreeNode* node = avlTree.search(7);
    cout << "\n���ҵ��Ľڵ����Ϊ " << node << "���ڵ�ֵ = " << node->val << endl;
}
