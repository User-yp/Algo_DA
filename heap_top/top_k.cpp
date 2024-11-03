#include "../utils/common.hpp"

 /* ���ڶѲ������������� k ��Ԫ�� */
priority_queue<int, vector<int>, greater<int>> topKHeap(vector<int>& nums, int k) {
    // ��ʼ��С����
    priority_queue<int, vector<int>, greater<int>> heap;
    // �������ǰ k ��Ԫ�����
    for (int i = 0; i < k; i++) {
        heap.push(nums[i]);
    }
    // �ӵ� k+1 ��Ԫ�ؿ�ʼ�����ֶѵĳ���Ϊ k
    for (int i = k; i < nums.size(); i++) {
        // ����ǰԪ�ش��ڶѶ�Ԫ�أ��򽫶Ѷ�Ԫ�س��ѡ���ǰԪ�����
        if (nums[i] > heap.top()) {
            heap.pop();
            heap.push(nums[i]);
        }
    }
    return heap;
}

// Driver Code
int main() {
    vector<int> nums = { 1, 7, 6, 3, 2 };
    int k = 3;

    priority_queue<int, vector<int>, greater<int>> res = topKHeap(nums, k);
    cout << "���� " << k << " ��Ԫ��Ϊ: ";
    printHeap(res);

    return 0;
}
