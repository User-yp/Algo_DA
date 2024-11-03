#include "../utils/common.hpp"

 /* ��������ʵ�ֵĶ��� */
class LinkedListQueue {
private:
    ListNode* front, * rear; // ͷ�ڵ� front ��β�ڵ� rear
    int queSize;

public:
    LinkedListQueue() {
        front = nullptr;
        rear = nullptr;
        queSize = 0;
    }

    ~LinkedListQueue() {
        // ��������ɾ���ڵ㣬�ͷ��ڴ�
        freeMemoryLinkedList(front);
    }

    /* ��ȡ���еĳ��� */
    int size() {
        return queSize;
    }

    /* �ж϶����Ƿ�Ϊ�� */
    bool isEmpty() {
        return queSize == 0;
    }

    /* ��� */
    void push(int num) {
        // ��β�ڵ����� num
        ListNode* node = new ListNode(num);
        // �������Ϊ�գ�����ͷ��β�ڵ㶼ָ��ýڵ�
        if (front == nullptr) {
            front = node;
            rear = node;
        }
        // ������в�Ϊ�գ��򽫸ýڵ���ӵ�β�ڵ��
        else {
            rear->next = node;
            rear = node;
        }
        queSize++;
    }

    /* ���� */
    int pop() {
        int num = peek();
        // ɾ��ͷ�ڵ�
        ListNode* tmp = front;
        front = front->next;
        // �ͷ��ڴ�
        delete tmp;
        queSize--;
        return num;
    }

    /* ���ʶ���Ԫ�� */
    int peek() {
        if (size() == 0)
            throw out_of_range("����Ϊ��");
        return front->val;
    }

    /* ������ת��Ϊ Vector ������ */
    vector<int> toVector() {
        ListNode* node = front;
        vector<int> res(size());
        for (int i = 0; i < res.size(); i++) {
            res[i] = node->val;
            node = node->next;
        }
        return res;
    }
};

/* Driver Code */
int main() {
    /* ��ʼ������ */
    LinkedListQueue* queue = new LinkedListQueue();

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

    // �ͷ��ڴ�
    delete queue;

    return 0;
}
