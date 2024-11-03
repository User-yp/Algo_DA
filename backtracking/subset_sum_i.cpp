#include "../utils/common.hpp"

 /* �����㷨���Ӽ��� I */
void backtrack(vector<int>& state, int target, vector<int>& choices, int start, vector<vector<int>>& res) {
    // �Ӽ��͵��� target ʱ����¼��
    if (target == 0) {
        res.push_back(state);
        return;
    }
    // ��������ѡ��
    // ��֦������ start ��ʼ���������������ظ��Ӽ�
    for (int i = start; i < choices.size(); i++) {
        // ��֦һ�����Ӽ��ͳ��� target ����ֱ�ӽ���ѭ��
        // ������Ϊ���������򣬺��Ԫ�ظ����Ӽ���һ������ target
        if (target - choices[i] < 0) {
            break;
        }
        // ���ԣ�����ѡ�񣬸��� target, start
        state.push_back(choices[i]);
        // ������һ��ѡ��
        backtrack(state, target - choices[i], choices, i, res);
        // ���ˣ�����ѡ�񣬻ָ���֮ǰ��״̬
        state.pop_back();
    }
}

/* ����Ӽ��� I */
vector<vector<int>> subsetSumI(vector<int>& nums, int target) {
    vector<int> state;              // ״̬���Ӽ���
    sort(nums.begin(), nums.end()); // �� nums ��������
    int start = 0;                  // ������ʼ��
    vector<vector<int>> res;        // ����б����Ӽ��б���
    backtrack(state, target, nums, start, res);
    return res;
}

/* Driver Code */
int main() {
    vector<int> nums = { 3, 4, 5 };
    int target = 9;

    vector<vector<int>> res = subsetSumI(nums, target);

    cout << "�������� nums = ";
    printVector(nums);
    cout << "target = " << target << endl;
    cout << "���к͵��� " << target << " ���Ӽ� res = " << endl;
    printVectorMatrix(res);

    return 0;
}