#include "../utils/common.hpp"

 /* ���� */
int dfs(int i) {
    // ��֪ dp[1] �� dp[2] ������֮
    if (i == 1 || i == 2)
        return i;
    // dp[i] = dp[i-1] + dp[i-2]
    int count = dfs(i - 1) + dfs(i - 2);
    return count;
}

/* ��¥�ݣ����� */
int climbingStairsDFS(int n) {
    return dfs(n);
}

/* Driver Code */
int main() {
    int n = 9;

    int res = climbingStairsDFS(n);
    cout << "�� " << n << " ��¥�ݹ��� " << res << " �ַ���" << endl;

    return 0;
}
