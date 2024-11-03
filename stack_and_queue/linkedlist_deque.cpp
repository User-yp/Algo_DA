#include "../utils/common.hpp"

 /* ˫������ڵ� */
struct DoublyListNode {
    int val;              // �ڵ�ֵ
    DoublyListNode* next; // ��̽ڵ�ָ��
    DoublyListNode* prev; // ǰ���ڵ�ָ��
    DoublyListNode(int val) : val(val), prev(nullptr), next(nullptr) {
    }
};

/* ����˫������ʵ�ֵ�˫����� */
class LinkedListDeque {
private:
    DoublyListNode* front, * rear; // ͷ�ڵ� front ��β�ڵ� rear
    int queSize = 0;              // ˫����еĳ���

public:
    /* ���췽�� */
    LinkedListDeque() : front(nullptr), rear(nullptr) {
    }

    /* �������� */
    ~LinkedListDeque() {
        // ��������ɾ���ڵ㣬�ͷ��ڴ�
        DoublyListNode* pre, * cur = front;
        while (cur != nullptr) {
            pre = cur;
            cur = cur->next;
            delete pre;
        }
    }

    /* ��ȡ˫����еĳ��� */
    int size() {
        return queSize;
    }

    /* �ж�˫������Ƿ�Ϊ�� */
    bool isEmpty() {
        return size() == 0;
    }

    /* ��Ӳ��� */
    void push(int num, bool isFront) {
        DoublyListNode* node = new DoublyListNode(num);
        // ������Ϊ�գ����� front �� rear ��ָ�� node
        if (isEmpty())
            front = rear = node;
        // ������Ӳ���
        else if (isFront) {
            // �� node ���������ͷ��
            front->prev = node;
            node->next = front;
            front = node; // ����ͷ�ڵ�
            // ��β��Ӳ���
        }
        else {
            // �� node ���������β��
            rear->next = node;
            node->prev = rear;
            rear = node; // ����β�ڵ�
        }
        queSize++; // ���¶��г���
    }

    /* ������� */
    void pushFirst(int num) {
        push(num, true);
    }

    /* ��β��� */
    void pushLast(int num) {
        push(num, false);
    }

    /* ���Ӳ��� */
    int pop(bool isFront) {
        if (isEmpty())
            throw out_of_range("����Ϊ��");
        int val;
        // ���׳��Ӳ���
        if (isFront) {
            val = front->val; // �ݴ�ͷ�ڵ�ֵ
            // ɾ��ͷ�ڵ�
            DoublyListNode* fNext = front->next;
            if (fNext != nullptr) {
                fNext->prev = nullptr;
                front->next = nullptr;
            }
            delete front;
            front = fNext; // ����ͷ�ڵ�
            // ��β���Ӳ���
        }
        else {
            val = rear->val; // �ݴ�β�ڵ�ֵ
            // ɾ��β�ڵ�
            DoublyListNode* rPrev = rear->prev;
            if (rPrev != nullptr) {
                rPrev->next = nullptr;
                rear->prev = nullptr;
            }
            delete rear;
            rear = rPrev; // ����β�ڵ�
        }
        queSize--; // ���¶��г���
        return val;
    }

    /* ���׳��� */
    int popFirst() {
        return pop(true);
    }

    /* ��β���� */
    int popLast() {
        return pop(false);
    }

    /* ���ʶ���Ԫ�� */
    int peekFirst() {
        if (isEmpty())
            throw out_of_range("˫�����Ϊ��");
        return front->val;
    }

    /* ���ʶ�βԪ�� */
    int peekLast() {
        if (isEmpty())
            throw out_of_range("˫�����Ϊ��");
        return rear->val;
    }

    /* �����������ڴ�ӡ */
    vector<int> toVector() {
        DoublyListNode* node = front;
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
    /* ��ʼ��˫����� */
    LinkedListDeque* deque = new LinkedListDeque();
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
    cout << "Ԫ�� 4 ��β��Ӻ� deque =";
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

    // �ͷ��ڴ�
    delete deque;

    return 0;
}
