#include "../utils/common.hpp"

 /* ��¥����С���ۣ���̬�滮 */
int minCostClimbingStairsDP(vector<int>& cost) {
    int n = cost.size() - 1;
    if (n == 1 || n == 2)
        return cost[n];
    // ��ʼ�� dp �����ڴ洢������Ľ�
    vector<int> dp(n + 1);
    // ��ʼ״̬��Ԥ����С������Ľ�
    dp[1] = cost[1];
    dp[2] = cost[2];
    // ״̬ת�ƣ��ӽ�С�����������ϴ�������
    for (int i = 3; i <= n; i++) {
        dp[i] = min(dp[i - 1], dp[i - 2]) + cost[i];
    }
    return dp[n];
}

/* ��¥����С���ۣ��ռ��Ż���Ķ�̬�滮 */
int minCostClimbingStairsDPComp(vector<int>& cost) {
    int n = cost.size() - 1;
    if (n == 1 || n == 2)
        return cost[n];
    int a = cost[1], b = cost[2];
    for (int i = 3; i <= n; i++) {
        int tmp = b;
        b = min(a, tmp) + cost[i];
        a = tmp;
    }
    return b;
}

/* Driver Code */
int main() {
    vector<int> cost = { 0, 1, 10, 1, 1, 1, 10, 1, 1, 10, 1 };
    cout << "����¥�ݵĴ����б�Ϊ ";
    printVector(cost);

    int res = minCostClimbingStairsDP(cost);
    cout << "����¥�ݵ���ʹ���Ϊ " << res << endl;

    res = minCostClimbingStairsDPComp(cost);
    cout << "����¥�ݵ���ʹ���Ϊ " << res << endl;

    return 0;
}
