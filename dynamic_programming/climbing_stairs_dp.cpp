#include "../utils/common.hpp"

 /* ��¥�ݣ���̬�滮 */
int climbingStairsDP(int n) {
    if (n == 1 || n == 2)
        return n;
    // ��ʼ�� dp �����ڴ洢������Ľ�
    vector<int> dp(n + 1);
    // ��ʼ״̬��Ԥ����С������Ľ�
    dp[1] = 1;
    dp[2] = 2;
    // ״̬ת�ƣ��ӽ�С�����������ϴ�������
    for (int i = 3; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[n];
}

/* ��¥�ݣ��ռ��Ż���Ķ�̬�滮 */
int climbingStairsDPComp(int n) {
    if (n == 1 || n == 2)
        return n;
    int a = 1, b = 2;
    for (int i = 3; i <= n; i++) {
        int tmp = b;
        b = a + b;
        a = tmp;
    }
    return b;
}

/* Driver Code */
int main() {
    int n = 9;

    int res = climbingStairsDP(n);
    cout << "�� " << n << " ��¥�ݹ��� " << res << " �ַ���" << endl;

    res = climbingStairsDPComp(n);
    cout << "�� " << n << " ��¥�ݹ��� " << res << " �ַ���" << endl;

    return 0;
}
