#include "../utils/common.hpp"

 /* ���ڻ�������ʵ�ֵĶ��� */
class ArrayQueue {
private:
    int* nums;       // ���ڴ洢����Ԫ�ص�����
    int front;       // ����ָ�룬ָ�����Ԫ��
    int queSize;     // ���г���
    int queCapacity; // ��������

public:
    ArrayQueue(int capacity) {
        // ��ʼ������
        nums = new int[capacity];
        queCapacity = capacity;
        front = queSize = 0;
    }

    ~ArrayQueue() {
        delete[] nums;
    }

    /* ��ȡ���е����� */
    int capacity() {
        return queCapacity;
    }

    /* ��ȡ���еĳ��� */
    int size() {
        return queSize;
    }

    /* �ж϶����Ƿ�Ϊ�� */
    bool isEmpty() {
        return size() == 0;
    }

    /* ��� */
    void push(int num) {
        if (queSize == queCapacity) {
            cout << "��������" << endl;
            return;
        }
        // �����βָ�룬ָ���β���� + 1
        // ͨ��ȡ�����ʵ�� rear Խ������β����ص�ͷ��
        int rear = (front + queSize) % queCapacity;
        // �� num �������β
        nums[rear] = num;
        queSize++;
    }

    /* ���� */
    int pop() {
        int num = peek();
        // ����ָ������ƶ�һλ����Խ��β�����򷵻ص�����ͷ��
        front = (front + 1) % queCapacity;
        queSize--;
        return num;
    }

    /* ���ʶ���Ԫ�� */
    int peek() {
        if (isEmpty())
            throw out_of_range("����Ϊ��");
        return nums[front];
    }

    /* ������ת��Ϊ Vector ������ */
    vector<int> toVector() {
        // ��ת����Ч���ȷ�Χ�ڵ��б�Ԫ��
        vector<int> arr(queSize);
        for (int i = 0, j = front; i < queSize; i++, j++) {
            arr[i] = nums[j % queCapacity];
        }
        return arr;
    }
};

/* Driver Code */
int main() {
    /* ��ʼ������ */
    int capacity = 10;
    ArrayQueue* queue = new ArrayQueue(capacity);

    /* Ԫ����� */
    queue->push(1);
    queue->push(3);
    queue->push(2);
    queue->push(5);
    queue->push(4);
    cout << "���� queue = ";
    printVector(queue->toVector());

    /* ���ʶ���Ԫ�� */
    int peek = queue->peek();
    cout << "����Ԫ�� peek = " << peek << endl;

    /* Ԫ�س��� */
    peek = queue->pop();
    cout << "����Ԫ�� pop = " << peek << "�����Ӻ� queue = ";
    printVector(queue->toVector());

    /* ��ȡ���еĳ��� */
    int size = queue->size();
    cout << "���г��� size = " << size << endl;

    /* �ж϶����Ƿ�Ϊ�� */
    bool empty = queue->isEmpty();
    cout << "�����Ƿ�Ϊ�� = " << empty << endl;

    /* ���Ի������� */
    for (int i = 0; i < 10; i++) {
        queue->push(i);
        queue->pop();
        cout << "�� " << i << " ����� + ���Ӻ� queue = ";
        printVector(queue->toVector());
    }

    // �ͷ��ڴ�
    delete queue;

    return 0;
}
