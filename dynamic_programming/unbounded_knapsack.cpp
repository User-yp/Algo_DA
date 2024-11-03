#include "../utils/common.hpp"

 /* ��ȫ��������̬�滮 */
int unboundedKnapsackDP(vector<int>& wgt, vector<int>& val, int cap) {
    int n = wgt.size();
    // ��ʼ�� dp ��
    vector<vector<int>> dp(n + 1, vector<int>(cap + 1, 0));
    // ״̬ת��
    for (int i = 1; i <= n; i++) {
        for (int c = 1; c <= cap; c++) {
            if (wgt[i - 1] > c) {
                // ������������������ѡ��Ʒ i
                dp[i][c] = dp[i - 1][c];
            }
            else {
                // ��ѡ��ѡ��Ʒ i �����ַ����Ľϴ�ֵ
                dp[i][c] = max(dp[i - 1][c], dp[i][c - wgt[i - 1]] + val[i - 1]);
            }
        }
    }
    return dp[n][cap];
}

/* ��ȫ�������ռ��Ż���Ķ�̬�滮 */
int unboundedKnapsackDPComp(vector<int>& wgt, vector<int>& val, int cap) {
    int n = wgt.size();
    // ��ʼ�� dp ��
    vector<int> dp(cap + 1, 0);
    // ״̬ת��
    for (int i = 1; i <= n; i++) {
        for (int c = 1; c <= cap; c++) {
            if (wgt[i - 1] > c) {
                // ������������������ѡ��Ʒ i
                dp[c] = dp[c];
            }
            else {
                // ��ѡ��ѡ��Ʒ i �����ַ����Ľϴ�ֵ
                dp[c] = max(dp[c], dp[c - wgt[i - 1]] + val[i - 1]);
            }
        }
    }
    return dp[cap];
}

/* Driver code */
int main() {
    vector<int> wgt = { 1, 2, 3 };
    vector<int> val = { 5, 11, 15 };
    int cap = 4;

    // ��̬�滮
    int res = unboundedKnapsackDP(wgt, val, cap);
    cout << "���������������������Ʒ��ֵΪ " << res << endl;

    // �ռ��Ż���Ķ�̬�滮
    res = unboundedKnapsackDPComp(wgt, val, cap);
    cout << "���������������������Ʒ��ֵΪ " << res << endl;

    return 0;
}
