#include "../utils/common.hpp"

 /* ��������ʵ�ֵ�ջ */
class LinkedListStack {
private:
    ListNode* stackTop; // ��ͷ�ڵ���Ϊջ��
    int stkSize;        // ջ�ĳ���

public:
    LinkedListStack() {
        stackTop = nullptr;
        stkSize = 0;
    }

    ~LinkedListStack() {
        // ��������ɾ���ڵ㣬�ͷ��ڴ�
        freeMemoryLinkedList(stackTop);
    }

    /* ��ȡջ�ĳ��� */
    int size() {
        return stkSize;
    }

    /* �ж�ջ�Ƿ�Ϊ�� */
    bool isEmpty() {
        return size() == 0;
    }

    /* ��ջ */
    void push(int num) {
        ListNode* node = new ListNode(num);
        node->next = stackTop;
        stackTop = node;
        stkSize++;
    }

    /* ��ջ */
    int pop() {
        int num = top();
        ListNode* tmp = stackTop;
        stackTop = stackTop->next;
        // �ͷ��ڴ�
        delete tmp;
        stkSize--;
        return num;
    }

    /* ����ջ��Ԫ�� */
    int top() {
        if (isEmpty())
            throw out_of_range("ջΪ��");
        return stackTop->val;
    }

    /* �� List ת��Ϊ Array ������ */
    vector<int> toVector() {
        ListNode* node = stackTop;
        vector<int> res(size());
        for (int i = res.size() - 1; i >= 0; i--) {
            res[i] = node->val;
            node = node->next;
        }
        return res;
    }
};

/* Driver Code */
int main() {
    /* ��ʼ��ջ */
    LinkedListStack* stack = new LinkedListStack();

    /* Ԫ����ջ */
    stack->push(1);
    stack->push(3);
    stack->push(2);
    stack->push(5);
    stack->push(4);
    cout << "ջ stack = ";
    printVector(stack->toVector());

    /* ����ջ��Ԫ�� */
    int top = stack->top();
    cout << "ջ��Ԫ�� top = " << top << endl;

    /* Ԫ�س�ջ */
    top = stack->pop();
    cout << "��ջԪ�� pop = " << top << "����ջ�� stack = ";
    printVector(stack->toVector());

    /* ��ȡջ�ĳ��� */
    int size = stack->size();
    cout << "ջ�ĳ��� size = " << size << endl;

    /* �ж��Ƿ�Ϊ�� */
    bool empty = stack->isEmpty();
    cout << "ջ�Ƿ�Ϊ�� = " << empty << endl;

    // �ͷ��ڴ�
    delete stack;

    return 0;
}
