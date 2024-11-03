#include "../utils/common.hpp"

 /* ��������ʵ�ֵ�ջ */
class ArrayStack {
private:
    vector<int> stack;

public:
    /* ��ȡջ�ĳ��� */
    int size() {
        return stack.size();
    }

    /* �ж�ջ�Ƿ�Ϊ�� */
    bool isEmpty() {
        return stack.size() == 0;
    }

    /* ��ջ */
    void push(int num) {
        stack.push_back(num);
    }

    /* ��ջ */
    int pop() {
        int num = top();
        stack.pop_back();
        return num;
    }

    /* ����ջ��Ԫ�� */
    int top() {
        if (isEmpty())
            throw out_of_range("ջΪ��");
        return stack.back();
    }

    /* ���� Vector */
    vector<int> toVector() {
        return stack;
    }
};

/* Driver Code */
int main() {
    /* ��ʼ��ջ */
    ArrayStack* stack = new ArrayStack();

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
