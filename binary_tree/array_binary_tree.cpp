#include "../utils/common.hpp"

 /* �����ʾ�µĶ������� */
class ArrayBinaryTree {
public:
    /* ���췽�� */
    ArrayBinaryTree(vector<int> arr) {
        tree = arr;
    }

    /* �б����� */
    int size() {
        return tree.size();
    }

    /* ��ȡ����Ϊ i �ڵ��ֵ */
    int val(int i) {
        // ������Խ�磬�򷵻� INT_MAX �������λ
        if (i < 0 || i >= size())
            return INT_MAX;
        return tree[i];
    }

    /* ��ȡ����Ϊ i �ڵ�����ӽڵ������ */
    int left(int i) {
        return 2 * i + 1;
    }

    /* ��ȡ����Ϊ i �ڵ�����ӽڵ������ */
    int right(int i) {
        return 2 * i + 2;
    }

    /* ��ȡ����Ϊ i �ڵ�ĸ��ڵ������ */
    int parent(int i) {
        return (i - 1) / 2;
    }

    /* ������� */
    vector<int> levelOrder() {
        vector<int> res;
        // ֱ�ӱ�������
        for (int i = 0; i < size(); i++) {
            if (val(i) != INT_MAX)
                res.push_back(val(i));
        }
        return res;
    }

    /* ǰ����� */
    vector<int> preOrder() {
        vector<int> res;
        dfs(0, "pre", res);
        return res;
    }

    /* ������� */
    vector<int> inOrder() {
        vector<int> res;
        dfs(0, "in", res);
        return res;
    }

    /* ������� */
    vector<int> postOrder() {
        vector<int> res;
        dfs(0, "post", res);
        return res;
    }

private:
    vector<int> tree;

    /* ������ȱ��� */
    void dfs(int i, string order, vector<int>& res) {
        // ��Ϊ��λ���򷵻�
        if (val(i) == INT_MAX)
            return;
        // ǰ�����
        if (order == "pre")
            res.push_back(val(i));
        dfs(left(i), order, res);
        // �������
        if (order == "in")
            res.push_back(val(i));
        dfs(right(i), order, res);
        // �������
        if (order == "post")
            res.push_back(val(i));
    }
};

/* Driver Code */
int main() {
    // ��ʼ��������
    // ʹ�� INT_MAX �����λ nullptr
    vector<int> arr = { 1, 2, 3, 4, INT_MAX, 6, 7, 8, 9, INT_MAX, INT_MAX, 12, INT_MAX, INT_MAX, 15 };
    TreeNode* root = vectorToTree(arr);
    cout << "\n��ʼ��������\n";
    cout << "�������������ʾ��\n";
    printVector(arr);
    cout << "�������������ʾ��\n";
    printTree(root);

    // �����ʾ�µĶ�������
    ArrayBinaryTree abt(arr);

    // ���ʽڵ�
    int i = 1;
    int l = abt.left(i), r = abt.right(i), p = abt.parent(i);
    cout << "\n��ǰ�ڵ������Ϊ " << i << "��ֵΪ " << abt.val(i) << "\n";
    cout << "�����ӽڵ������Ϊ " << l << "��ֵΪ " << (l != INT_MAX ? to_string(abt.val(l)) : "nullptr") << "\n";
    cout << "�����ӽڵ������Ϊ " << r << "��ֵΪ " << (r != INT_MAX ? to_string(abt.val(r)) : "nullptr") << "\n";
    cout << "�丸�ڵ������Ϊ " << p << "��ֵΪ " << (p != INT_MAX ? to_string(abt.val(p)) : "nullptr") << "\n";

    // ������
    vector<int> res = abt.levelOrder();
    cout << "\n�������Ϊ�� ";
    printVector(res);
    res = abt.preOrder();
    cout << "ǰ�����Ϊ�� ";
    printVector(res);
    res = abt.inOrder();
    cout << "�������Ϊ�� ";
    printVector(res);
    res = abt.postOrder();
    cout << "�������Ϊ�� ";
    printVector(res);

    return 0;
}
