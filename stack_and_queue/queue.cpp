#include "../utils/common.hpp"

 /* Driver Code */
int main() {
    /* ��ʼ������ */
    queue<int> queue;

    /* Ԫ����� */
    queue.push(1);
    queue.push(3);
    queue.push(2);
    queue.push(5);
    queue.push(4);
    cout << "���� queue = ";
    printQueue(queue);

    /* ���ʶ���Ԫ�� */
    int front = queue.front();
    cout << "����Ԫ�� front = " << front << endl;

    /* Ԫ�س��� */
    queue.pop();
    cout << "����Ԫ�� front = " << front << "�����Ӻ� queue = ";
    printQueue(queue);

    /* ��ȡ���еĳ��� */
    int size = queue.size();
    cout << "���г��� size = " << size << endl;

    /* �ж϶����Ƿ�Ϊ�� */
    bool empty = queue.empty();
    cout << "�����Ƿ�Ϊ�� = " << empty << endl;

    return 0;
}
