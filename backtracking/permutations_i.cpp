#include "../utils/common.hpp"

 /* �����㷨��ȫ���� I */
void backtrack(vector<int>& state, const vector<int>& choices, vector<bool>& selected, vector<vector<int>>& res) {
    // ��״̬���ȵ���Ԫ������ʱ����¼��
    if (state.size() == choices.size()) {
        res.push_back(state);
        return;
    }
    // ��������ѡ��
    for (int i = 0; i < choices.size(); i++) {
        int choice = choices[i];
        // ��֦���������ظ�ѡ��Ԫ��
        if (!selected[i]) {
            // ���ԣ�����ѡ�񣬸���״̬
            selected[i] = true;
            state.push_back(choice);
            // ������һ��ѡ��
            backtrack(state, choices, selected, res);
            // ���ˣ�����ѡ�񣬻ָ���֮ǰ��״̬
            selected[i] = false;
            state.pop_back();
        }
    }
}

/* ȫ���� I */
vector<vector<int>> permutationsI(vector<int> nums) {
    vector<int> state;
    vector<bool> selected(nums.size(), false);
    vector<vector<int>> res;
    backtrack(state, nums, selected, res);
    return res;
}

/* Driver Code */
int main() {
    vector<int> nums = { 1, 2, 3 };

    vector<vector<int>> res = permutationsI(nums);

    cout << "�������� nums = ";
    printVector(nums);
    cout << "�������� res = ";
    printVectorMatrix(res);

    return 0;
}
