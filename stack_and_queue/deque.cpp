#include "../utils/common.hpp"

 /* Driver Code */
int main() {
    /* ��ʼ��˫����� */
    deque<int> deque;

    /* Ԫ����� */
    deque.push_back(2);
    deque.push_back(5);
    deque.push_back(4);
    deque.push_front(3);
    deque.push_front(1);
    cout << "˫����� deque = ";
    printDeque(deque);

    /* ����Ԫ�� */
    int front = deque.front();
    cout << "����Ԫ�� front = " << front << endl;
    int back = deque.back();
    cout << "��βԪ�� back = " << back << endl;

    /* Ԫ�س��� */
    deque.pop_front();
    cout << "���׳���Ԫ�� popFront = " << front << "�����׳��Ӻ� deque = ";
    printDeque(deque);
    deque.pop_back();
    cout << "��β����Ԫ�� popLast = " << back << "����β���Ӻ� deque = ";
    printDeque(deque);

    /* ��ȡ˫����еĳ��� */
    int size = deque.size();
    cout << "˫����г��� size = " << size << endl;

    /* �ж�˫������Ƿ�Ϊ�� */
    bool empty = deque.empty();
    cout << "˫������Ƿ�Ϊ�� = " << empty << endl;

    return 0;
}
