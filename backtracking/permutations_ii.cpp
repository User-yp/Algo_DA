#include "../utils/common.hpp"

 /* �����㷨��ȫ���� II */
void backtrack(vector<int>& state, const vector<int>& choices, vector<bool>& selected, vector<vector<int>>& res) {
    // ��״̬���ȵ���Ԫ������ʱ����¼��
    if (state.size() == choices.size()) {
        res.push_back(state);
        return;
    }
    // ��������ѡ��
    unordered_set<int> duplicated;
    for (int i = 0; i < choices.size(); i++) {
        int choice = choices[i];
        // ��֦���������ظ�ѡ��Ԫ�� �� �������ظ�ѡ�����Ԫ��
        if (!selected[i] && duplicated.find(choice) == duplicated.end()) {
            // ���ԣ�����ѡ�񣬸���״̬
            duplicated.emplace(choice); // ��¼ѡ�����Ԫ��ֵ
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

/* ȫ���� II */
vector<vector<int>> permutationsII(vector<int> nums) {
    vector<int> state;
    vector<bool> selected(nums.size(), false);
    vector<vector<int>> res;
    backtrack(state, nums, selected, res);
    return res;
}

/* Driver Code */
int main() {
    vector<int> nums = { 1, 1, 2 };

    vector<vector<int>> res = permutationsII(nums);

    cout << "�������� nums = ";
    printVector(nums);
    cout << "�������� res = ";
    printVectorMatrix(res);

    return 0;
}
