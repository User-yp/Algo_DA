#include "../utils/common.hpp"

 /* Driver Code */
int main() {
    /* ��ʼ��ջ */
    stack<int> stack;

    /* Ԫ����ջ */
    stack.push(1);
    stack.push(3);
    stack.push(2);
    stack.push(5);
    stack.push(4);
    cout << "ջ stack = ";
    printStack(stack);

    /* ����ջ��Ԫ�� */
    int top = stack.top();
    cout << "ջ��Ԫ�� top = " << top << endl;

    /* Ԫ�س�ջ */
    stack.pop(); // �޷���ֵ
    cout << "��ջԪ�� pop = " << top << "����ջ�� stack = ";
    printStack(stack);

    /* ��ȡջ�ĳ��� */
    int size = stack.size();
    cout << "ջ�ĳ��� size = " << size << endl;

    /* �ж��Ƿ�Ϊ�� */
    bool empty = stack.empty();
    cout << "ջ�Ƿ�Ϊ�� = " << empty << endl;

    return 0;
}
