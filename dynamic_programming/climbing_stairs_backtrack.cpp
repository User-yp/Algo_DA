#include "../utils/common.hpp"

 /* ���� */
void backtrack(vector<int>& choices, int state, int n, vector<int>& res) {
    // �������� n ��ʱ������������ 1
    if (state == n)
        res[0]++;
    // ��������ѡ��
    for (auto& choice : choices) {
        // ��֦��������Խ���� n ��
        if (state + choice > n)
            continue;
        // ���ԣ�����ѡ�񣬸���״̬
        backtrack(choices, state + choice, n, res);
        // ����
    }
}

/* ��¥�ݣ����� */
int climbingStairsBacktrack(int n) {
    vector<int> choices = { 1, 2 }; // ��ѡ�������� 1 �׻� 2 ��
    int state = 0;                // �ӵ� 0 �׿�ʼ��
    vector<int> res = { 0 };        // ʹ�� res[0] ��¼��������
    backtrack(choices, state, n, res);
    return res[0];
}

/* Driver Code */
int main() {
    int n = 9;

    int res = climbingStairsBacktrack(n);
    cout << "�� " << n << " ��¥�ݹ��� " << res << " �ַ���" << endl;

    return 0;
}
