#include "../utils/common.hpp"

 /* ���ڻ�������ʵ�ֵ�˫����� */
class ArrayDeque {
private:
    vector<int> nums; // ���ڴ洢˫�����Ԫ�ص�����
    int front;        // ����ָ�룬ָ�����Ԫ��
    int queSize;      // ˫����г���

public:
    /* ���췽�� */
    ArrayDeque(int capacity) {
        nums.resize(capacity);
        front = queSize = 0;
    }

    /* ��ȡ˫����е����� */
    int capacity() {
        return nums.size();
    }

    /* ��ȡ˫����еĳ��� */
    int size() {
        return queSize;
    }

    /* �ж�˫������Ƿ�Ϊ�� */
    bool isEmpty() {
        return queSize == 0;
    }

    /* ���㻷���������� */
    int index(int i) {
        // ͨ��ȡ�����ʵ��������β����
        // �� i Խ������β���󣬻ص�ͷ��
        // �� i Խ������ͷ���󣬻ص�β��
        return (i + capacity()) % capacity();
    }

    /* ������� */
    void pushFirst(int num) {
        if (queSize == capacity()) {
            cout << "˫���������" << endl;
            return;
        }
        // ����ָ�������ƶ�һλ
        // ͨ��ȡ�����ʵ�� front Խ������ͷ����ص�β��
        front = index(front - 1);
        // �� num ���������
        nums[front] = num;
        queSize++;
    }

    /* ��β��� */
    void pushLast(int num) {
        if (queSize == capacity()) {
            cout << "˫���������" << endl;
            return;
        }
        // �����βָ�룬ָ���β���� + 1
        int rear = index(front + queSize);
        // �� num �������β
        nums[rear] = num;
        queSize++;
    }

    /* ���׳��� */
    int popFirst() {
        int num = peekFirst();
        // ����ָ������ƶ�һλ
        front = index(front + 1);
        queSize--;
        return num;
    }

    /* ��β���� */
    int popLast() {
        int num = peekLast();
        queSize--;
        return num;
    }

    /* ���ʶ���Ԫ�� */
    int peekFirst() {
        if (isEmpty())
            throw out_of_range("˫�����Ϊ��");
        return nums[front];
    }

    /* ���ʶ�βԪ�� */
    int peekLast() {
        if (isEmpty())
            throw out_of_range("˫�����Ϊ��");
        // ����βԪ������
        int last = index(front + queSize - 1);
        return nums[last];
    }

    /* �����������ڴ�ӡ */
    vector<int> toVector() {
        // ��ת����Ч���ȷ�Χ�ڵ��б�Ԫ��
        vector<int> res(queSize);
        for (int i = 0, j = front; i < queSize; i++, j++) {
            res[i] = nums[index(j)];
        }
        return res;
    }
};

/* Driver Code */
int main() {
    /* ��ʼ��˫����� */
    ArrayDeque* deque = new ArrayDeque(10);
    deque->pushLast(3);
    deque->pushLast(2);
    deque->pushLast(5);
    cout << "˫����� deque = ";
    printVector(deque->toVector());

    /* ����Ԫ�� */
    int peekFirst = deque->peekFirst();
    cout << "����Ԫ�� peekFirst = " << peekFirst << endl;
    int peekLast = deque->peekLast();
    cout << "��βԪ�� peekLast = " << peekLast << endl;

    /* Ԫ����� */
    deque->pushLast(4);
    cout << "Ԫ�� 4 ��β��Ӻ� deque = ";
    printVector(deque->toVector());
    deque->pushFirst(1);
    cout << "Ԫ�� 1 ������Ӻ� deque = ";
    printVector(deque->toVector());

    /* Ԫ�س��� */
    int popLast = deque->popLast();
    cout << "��β����Ԫ�� = " << popLast << "����β���Ӻ� deque = ";
    printVector(deque->toVector());
    int popFirst = deque->popFirst();
    cout << "���׳���Ԫ�� = " << popFirst << "�����׳��Ӻ� deque = ";
    printVector(deque->toVector());

    /* ��ȡ˫����еĳ��� */
    int size = deque->size();
    cout << "˫����г��� size = " << size << endl;

    /* �ж�˫������Ƿ�Ϊ�� */
    bool isEmpty = deque->isEmpty();
    cout << "˫������Ƿ�Ϊ�� = " << boolalpha << isEmpty << endl;
    return 0;
}
