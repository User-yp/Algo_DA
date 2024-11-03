#include "../utils/common.hpp"

 /* ��Լ����¥�ݣ���̬�滮 */
int climbingStairsConstraintDP(int n) {
    if (n == 1 || n == 2) {
        return 1;
    }
    // ��ʼ�� dp �����ڴ洢������Ľ�
    vector<vector<int>> dp(n + 1, vector<int>(3, 0));
    // ��ʼ״̬��Ԥ����С������Ľ�
    dp[1][1] = 1;
    dp[1][2] = 0;
    dp[2][1] = 0;
    dp[2][2] = 1;
    // ״̬ת�ƣ��ӽ�С�����������ϴ�������
    for (int i = 3; i <= n; i++) {
        dp[i][1] = dp[i - 1][2];
        dp[i][2] = dp[i - 2][1] + dp[i - 2][2];
    }
    return dp[n][1] + dp[n][2];
}

/* Driver Code */
int main() {
    int n = 9;

    int res = climbingStairsConstraintDP(n);
    cout << "�� " << n << " ��¥�ݹ��� " << res << " �ַ���" << endl;

    return 0;
}
