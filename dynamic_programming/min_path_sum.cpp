#include "../utils/common.hpp"

 /* ��С·���ͣ��������� */
int minPathSumDFS(vector<vector<int>>& grid, int i, int j) {
    // ��Ϊ���Ͻǵ�Ԫ������ֹ����
    if (i == 0 && j == 0) {
        return grid[0][0];
    }
    // ����������Խ�磬�򷵻� +�� ����
    if (i < 0 || j < 0) {
        return INT_MAX;
    }
    // ��������Ͻǵ� (i-1, j) �� (i, j-1) ����С·������
    int up = minPathSumDFS(grid, i - 1, j);
    int left = minPathSumDFS(grid, i, j - 1);
    // ���ش����Ͻǵ� (i, j) ����С·������
    return min(left, up) != INT_MAX ? min(left, up) + grid[i][j] : INT_MAX;
}

/* ��С·���ͣ����仯���� */
int minPathSumDFSMem(vector<vector<int>>& grid, vector<vector<int>>& mem, int i, int j) {
    // ��Ϊ���Ͻǵ�Ԫ������ֹ����
    if (i == 0 && j == 0) {
        return grid[0][0];
    }
    // ����������Խ�磬�򷵻� +�� ����
    if (i < 0 || j < 0) {
        return INT_MAX;
    }
    // �����м�¼����ֱ�ӷ���
    if (mem[i][j] != -1) {
        return mem[i][j];
    }
    // ��ߺ��ϱߵ�Ԫ�����С·������
    int up = minPathSumDFSMem(grid, mem, i - 1, j);
    int left = minPathSumDFSMem(grid, mem, i, j - 1);
    // ��¼���������Ͻǵ� (i, j) ����С·������
    mem[i][j] = min(left, up) != INT_MAX ? min(left, up) + grid[i][j] : INT_MAX;
    return mem[i][j];
}

/* ��С·���ͣ���̬�滮 */
int minPathSumDP(vector<vector<int>>& grid) {
    int n = grid.size(), m = grid[0].size();
    // ��ʼ�� dp ��
    vector<vector<int>> dp(n, vector<int>(m));
    dp[0][0] = grid[0][0];
    // ״̬ת�ƣ�����
    for (int j = 1; j < m; j++) {
        dp[0][j] = dp[0][j - 1] + grid[0][j];
    }
    // ״̬ת�ƣ�����
    for (int i = 1; i < n; i++) {
        dp[i][0] = dp[i - 1][0] + grid[i][0];
    }
    // ״̬ת�ƣ������к���
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            dp[i][j] = min(dp[i][j - 1], dp[i - 1][j]) + grid[i][j];
        }
    }
    return dp[n - 1][m - 1];
}

/* ��С·���ͣ��ռ��Ż���Ķ�̬�滮 */
int minPathSumDPComp(vector<vector<int>>& grid) {
    int n = grid.size(), m = grid[0].size();
    // ��ʼ�� dp ��
    vector<int> dp(m);
    // ״̬ת�ƣ�����
    dp[0] = grid[0][0];
    for (int j = 1; j < m; j++) {
        dp[j] = dp[j - 1] + grid[0][j];
    }
    // ״̬ת�ƣ�������
    for (int i = 1; i < n; i++) {
        // ״̬ת�ƣ�����
        dp[0] = dp[0] + grid[i][0];
        // ״̬ת�ƣ�������
        for (int j = 1; j < m; j++) {
            dp[j] = min(dp[j - 1], dp[j]) + grid[i][j];
        }
    }
    return dp[m - 1];
}

/* Driver Code */
int main() {
    vector<vector<int>> grid = { {1, 3, 1, 5}, {2, 2, 4, 2}, {5, 3, 2, 1}, {4, 3, 5, 2} };
    int n = grid.size(), m = grid[0].size();

    // ��������
    int res = minPathSumDFS(grid, n - 1, m - 1);
    cout << "�����Ͻǵ����½ǵ���С·����Ϊ " << res << endl;

    // ���仯����
    vector<vector<int>> mem(n, vector<int>(m, -1));
    res = minPathSumDFSMem(grid, mem, n - 1, m - 1);
    cout << "�����Ͻǵ����½ǵ���С·����Ϊ " << res << endl;

    // ��̬�滮
    res = minPathSumDP(grid);
    cout << "�����Ͻǵ����½ǵ���С·����Ϊ " << res << endl;

    // �ռ��Ż���Ķ�̬�滮
    res = minPathSumDPComp(grid);
    cout << "�����Ͻǵ����½ǵ���С·����Ϊ " << res << endl;

    return 0;
}
