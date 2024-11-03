#include "../utils/common.hpp"

 /* ��Ǯ�һ�����̬�滮 */
int coinChangeDP(vector<int>& coins, int amt) {
    int n = coins.size();
    int MAX = amt + 1;
    // ��ʼ�� dp ��
    vector<vector<int>> dp(n + 1, vector<int>(amt + 1, 0));
    // ״̬ת�ƣ���������
    for (int a = 1; a <= amt; a++) {
        dp[0][a] = MAX;
    }
    // ״̬ת�ƣ������к���
    for (int i = 1; i <= n; i++) {
        for (int a = 1; a <= amt; a++) {
            if (coins[i - 1] > a) {
                // ������Ŀ�����ѡӲ�� i
                dp[i][a] = dp[i - 1][a];
            }
            else {
                // ��ѡ��ѡӲ�� i �����ַ����Ľ�Сֵ
                dp[i][a] = min(dp[i - 1][a], dp[i][a - coins[i - 1]] + 1);
            }
        }
    }
    return dp[n][amt] != MAX ? dp[n][amt] : -1;
}

/* ��Ǯ�һ����ռ��Ż���Ķ�̬�滮 */
int coinChangeDPComp(vector<int>& coins, int amt) {
    int n = coins.size();
    int MAX = amt + 1;
    // ��ʼ�� dp ��
    vector<int> dp(amt + 1, MAX);
    dp[0] = 0;
    // ״̬ת��
    for (int i = 1; i <= n; i++) {
        for (int a = 1; a <= amt; a++) {
            if (coins[i - 1] > a) {
                // ������Ŀ�����ѡӲ�� i
                dp[a] = dp[a];
            }
            else {
                // ��ѡ��ѡӲ�� i �����ַ����Ľ�Сֵ
                dp[a] = min(dp[a], dp[a - coins[i - 1]] + 1);
            }
        }
    }
    return dp[amt] != MAX ? dp[amt] : -1;
}

/* Driver code */
int main() {
    vector<int> coins = { 1, 2, 5 };
    int amt = 4;

    // ��̬�滮
    int res = coinChangeDP(coins, amt);
    cout << "�յ�Ŀ�������������Ӳ������Ϊ " << res << endl;

    // �ռ��Ż���Ķ�̬�滮
    res = coinChangeDPComp(coins, amt);
    cout << "�յ�Ŀ�������������Ӳ������Ϊ " << res << endl;

    return 0;
}
