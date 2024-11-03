#include "../utils/common.hpp"

 /* ���仯���� */
int dfs(int i, vector<int>& mem) {
    // ��֪ dp[1] �� dp[2] ������֮
    if (i == 1 || i == 2)
        return i;
    // �����ڼ�¼ dp[i] ����ֱ�ӷ���֮
    if (mem[i] != -1)
        return mem[i];
    // dp[i] = dp[i-1] + dp[i-2]
    int count = dfs(i - 1, mem) + dfs(i - 2, mem);
    // ��¼ dp[i]
    mem[i] = count;
    return count;
}

/* ��¥�ݣ����仯���� */
int climbingStairsDFSMem(int n) {
    // mem[i] ��¼������ i �׵ķ���������-1 �����޼�¼
    vector<int> mem(n + 1, -1);
    return dfs(n, mem);
}

/* Driver Code */
int main() {
    int n = 9;

    int res = climbingStairsDFSMem(n);
    cout << "�� " << n << " ��¥�ݹ��� " << res << " �ַ���" << endl;

    return 0;
}
