#include "../utils/common.hpp"

 /* �󶥶� */
class MaxHeap {
private:
    // ʹ�ö�̬���飬�������뿼����������
    vector<int> maxHeap;

    /* ��ȡ���ӽڵ������ */
    int left(int i) {
        return 2 * i + 1;
    }

    /* ��ȡ���ӽڵ������ */
    int right(int i) {
        return 2 * i + 2;
    }

    /* ��ȡ���ڵ������ */
    int parent(int i) {
        return (i - 1) / 2; // ��������
    }

    /* �ӽڵ� i ��ʼ���ӵ������ѻ� */
    void siftUp(int i) {
        while (true) {
            // ��ȡ�ڵ� i �ĸ��ڵ�
            int p = parent(i);
            // ����Խ�����ڵ㡱�򡰽ڵ������޸���ʱ�������ѻ�
            if (p < 0 || maxHeap[i] <= maxHeap[p])
                break;
            // �������ڵ�
            swap(maxHeap[i], maxHeap[p]);
            // ѭ�����϶ѻ�
            i = p;
        }
    }

    /* �ӽڵ� i ��ʼ���Ӷ����׶ѻ� */
    void siftDown(int i) {
        while (true) {
            // �жϽڵ� i, l, r ��ֵ���Ľڵ㣬��Ϊ ma
            int l = left(i), r = right(i), ma = i;
            if (l < size() && maxHeap[l] > maxHeap[ma])
                ma = l;
            if (r < size() && maxHeap[r] > maxHeap[ma])
                ma = r;
            // ���ڵ� i �������� l, r Խ�磬����������ѻ�������
            if (ma == i)
                break;
            swap(maxHeap[i], maxHeap[ma]);
            // ѭ�����¶ѻ�
            i = ma;
        }
    }

public:
    /* ���췽�������������б��� */
    MaxHeap(vector<int> nums) {
        // ���б�Ԫ��ԭ�ⲻ����ӽ���
        maxHeap = nums;
        // �ѻ���Ҷ�ڵ�������������нڵ�
        for (int i = parent(size() - 1); i >= 0; i--) {
            siftDown(i);
        }
    }

    /* ��ȡ�Ѵ�С */
    int size() {
        return maxHeap.size();
    }

    /* �ж϶��Ƿ�Ϊ�� */
    bool isEmpty() {
        return size() == 0;
    }

    /* ���ʶѶ�Ԫ�� */
    int peek() {
        return maxHeap[0];
    }

    /* Ԫ����� */
    void push(int val) {
        // ��ӽڵ�
        maxHeap.push_back(val);
        // �ӵ������ѻ�
        siftUp(size() - 1);
    }

    /* Ԫ�س��� */
    void pop() {
        // �пմ���
        if (isEmpty()) {
            throw out_of_range("��Ϊ��");
        }
        // �������ڵ�������Ҷ�ڵ㣨������Ԫ����βԪ�أ�
        swap(maxHeap[0], maxHeap[size() - 1]);
        // ɾ���ڵ�
        maxHeap.pop_back();
        // �Ӷ����׶ѻ�
        siftDown(0);
    }

    /* ��ӡ�ѣ���������*/
    void print() {
        cout << "�ѵ������ʾ��";
        printVector(maxHeap);
        cout << "�ѵ���״��ʾ��" << endl;
        TreeNode* root = vectorToTree(maxHeap);
        printTree(root);
        freeMemoryTree(root);
    }
};

/* Driver Code */
int main() {
    /* ��ʼ���󶥶� */
    vector<int> vec{ 9, 8, 6, 6, 7, 5, 2, 1, 4, 3, 6, 2 };
    MaxHeap maxHeap(vec);
    cout << "\n�����б����Ѻ�" << endl;
    maxHeap.print();

    /* ��ȡ�Ѷ�Ԫ�� */
    int peek = maxHeap.peek();
    cout << "\n�Ѷ�Ԫ��Ϊ " << peek << endl;

    /* Ԫ����� */
    int val = 7;
    maxHeap.push(val);
    cout << "\nԪ�� " << val << " ��Ѻ�" << endl;
    maxHeap.print();

    /* �Ѷ�Ԫ�س��� */
    peek = maxHeap.peek();
    maxHeap.pop();
    cout << "\n�Ѷ�Ԫ�� " << peek << " ���Ѻ�" << endl;
    maxHeap.print();

    /* ��ȡ�Ѵ�С */
    int size = maxHeap.size();
    cout << "\n��Ԫ������Ϊ " << size << endl;

    /* �ж϶��Ƿ�Ϊ�� */
    bool isEmpty = maxHeap.isEmpty();
    cout << "\n���Ƿ�Ϊ�� " << isEmpty << endl;

    return 0;
}
