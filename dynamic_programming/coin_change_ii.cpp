#include "../utils/common.hpp"

 /* ��Ǯ�һ� II����̬�滮 */
int coinChangeIIDP(vector<int>& coins, int amt) {
    int n = coins.size();
    // ��ʼ�� dp ��
    vector<vector<int>> dp(n + 1, vector<int>(amt + 1, 0));
    // ��ʼ������
    for (int i = 0; i <= n; i++) {
        dp[i][0] = 1;
    }
    // ״̬ת��
    for (int i = 1; i <= n; i++) {
        for (int a = 1; a <= amt; a++) {
            if (coins[i - 1] > a) {
                // ������Ŀ�����ѡӲ�� i
                dp[i][a] = dp[i - 1][a];
            }
            else {
                // ��ѡ��ѡӲ�� i �����ַ���֮��
                dp[i][a] = dp[i - 1][a] + dp[i][a - coins[i - 1]];
            }
        }
    }
    return dp[n][amt];
}

/* ��Ǯ�һ� II���ռ��Ż���Ķ�̬�滮 */
int coinChangeIIDPComp(vector<int>& coins, int amt) {
    int n = coins.size();
    // ��ʼ�� dp ��
    vector<int> dp(amt + 1, 0);
    dp[0] = 1;
    // ״̬ת��
    for (int i = 1; i <= n; i++) {
        for (int a = 1; a <= amt; a++) {
            if (coins[i - 1] > a) {
                // ������Ŀ�����ѡӲ�� i
                dp[a] = dp[a];
            }
            else {
                // ��ѡ��ѡӲ�� i �����ַ���֮��
                dp[a] = dp[a] + dp[a - coins[i - 1]];
            }
        }
    }
    return dp[amt];
}

/* Driver code */
int main() {
    vector<int> coins = { 1, 2, 5 };
    int amt = 5;

    // ��̬�滮
    int res = coinChangeIIDP(coins, amt);
    cout << "�ճ�Ŀ�����Ӳ���������Ϊ " << res << endl;

    // �ռ��Ż���Ķ�̬�滮
    res = coinChangeIIDPComp(coins, amt);
    cout << "�ճ�Ŀ�����Ӳ���������Ϊ " << res << endl;

    return 0;
}
