#include "../utils/common.hpp"

void testPush(priority_queue<int>& heap, int val) {
    heap.push(val); // Ԫ�����
    cout << "\nԪ�� " << val << " ��Ѻ�" << endl;
    printHeap(heap);
}

void testPop(priority_queue<int>& heap) {
    int val = heap.top();
    heap.pop();
    cout << "\n�Ѷ�Ԫ�� " << val << " ���Ѻ�" << endl;
    printHeap(heap);
}

/* Driver Code */
int main() {
    /* ��ʼ���� */
    // ��ʼ��С����
    // priority_queue<int, vector<int>, greater<int>> minHeap;
    // ��ʼ���󶥶�
    priority_queue<int, vector<int>, less<int>> maxHeap;

    cout << "\n���²�������Ϊ�󶥶�" << endl;

    /* Ԫ����� */
    testPush(maxHeap, 1);
    testPush(maxHeap, 3);
    testPush(maxHeap, 2);
    testPush(maxHeap, 5);
    testPush(maxHeap, 4);

    /* ��ȡ�Ѷ�Ԫ�� */
    int peek = maxHeap.top();
    cout << "\n�Ѷ�Ԫ��Ϊ " << peek << endl;

    /* �Ѷ�Ԫ�س��� */
    testPop(maxHeap);
    testPop(maxHeap);
    testPop(maxHeap);
    testPop(maxHeap);
    testPop(maxHeap);

    /* ��ȡ�Ѵ�С */
    int size = maxHeap.size();
    cout << "\n��Ԫ������Ϊ " << size << endl;

    /* �ж϶��Ƿ�Ϊ�� */
    bool isEmpty = maxHeap.empty();
    cout << "\n���Ƿ�Ϊ�� " << isEmpty << endl;

    /* �����б����� */
    // ʱ�临�Ӷ�Ϊ O(n) ������ O(nlogn)
    vector<int> input{ 1, 3, 2, 5, 4 };
    priority_queue<int, vector<int>, greater<int>> minHeap(input.begin(), input.end());
    cout << "�����б�����С���Ѻ�" << endl;
    printHeap(minHeap);

    return 0;
}
