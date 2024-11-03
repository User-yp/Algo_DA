#include "../utils/common.hpp"

 /* �����㷨���Ӽ��� I */
void backtrack(vector<int>& state, int target, int total, vector<int>& choices, vector<vector<int>>& res) {
    // �Ӽ��͵��� target ʱ����¼��
    if (total == target) {
        res.push_back(state);
        return;
    }
    // ��������ѡ��
    for (size_t i = 0; i < choices.size(); i++) {
        // ��֦�����Ӽ��ͳ��� target ����������ѡ��
        if (total + choices[i] > target) {
            continue;
        }
        // ���ԣ�����ѡ�񣬸���Ԫ�غ� total
        state.push_back(choices[i]);
        // ������һ��ѡ��
        backtrack(state, target, total + choices[i], choices, res);
        // ���ˣ�����ѡ�񣬻ָ���֮ǰ��״̬
        state.pop_back();
    }
}

/* ����Ӽ��� I�������ظ��Ӽ��� */
vector<vector<int>> subsetSumINaive(vector<int>& nums, int target) {
    vector<int> state;       // ״̬���Ӽ���
    int total = 0;           // �Ӽ���
    vector<vector<int>> res; // ����б��Ӽ��б�
    backtrack(state, target, total, nums, res);
    return res;
}

/* Driver Code */
int main() {
    vector<int> nums = { 3, 4, 5 };
    int target = 9;

    vector<vector<int>> res = subsetSumINaive(nums, target);

    cout << "�������� nums = ";
    printVector(nums);
    cout << "target = " << target << endl;
    cout << "���к͵��� " << target << " ���Ӽ� res = " << endl;
    printVectorMatrix(res);

    return 0;
}
