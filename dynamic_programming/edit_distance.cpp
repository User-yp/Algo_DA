#include "../utils/common.hpp"

 /* �༭���룺�������� */
int editDistanceDFS(string s, string t, int i, int j) {
    // �� s �� t ��Ϊ�գ��򷵻� 0
    if (i == 0 && j == 0)
        return 0;
    // �� s Ϊ�գ��򷵻� t ����
    if (i == 0)
        return j;
    // �� t Ϊ�գ��򷵻� s ����
    if (j == 0)
        return i;
    // �����ַ���ȣ���ֱ�����������ַ�
    if (s[i - 1] == t[j - 1])
        return editDistanceDFS(s, t, i - 1, j - 1);
    // ���ٱ༭���� = ���롢ɾ�����滻�����ֲ��������ٱ༭���� + 1
    int insert = editDistanceDFS(s, t, i, j - 1);
    int del = editDistanceDFS(s, t, i - 1, j);
    int replace = editDistanceDFS(s, t, i - 1, j - 1);
    // �������ٱ༭����
    return min(min(insert, del), replace) + 1;
}

/* �༭���룺���仯���� */
int editDistanceDFSMem(string s, string t, vector<vector<int>>& mem, int i, int j) {
    // �� s �� t ��Ϊ�գ��򷵻� 0
    if (i == 0 && j == 0)
        return 0;
    // �� s Ϊ�գ��򷵻� t ����
    if (i == 0)
        return j;
    // �� t Ϊ�գ��򷵻� s ����
    if (j == 0)
        return i;
    // �����м�¼����ֱ�ӷ���֮
    if (mem[i][j] != -1)
        return mem[i][j];
    // �����ַ���ȣ���ֱ�����������ַ�
    if (s[i - 1] == t[j - 1])
        return editDistanceDFSMem(s, t, mem, i - 1, j - 1);
    // ���ٱ༭���� = ���롢ɾ�����滻�����ֲ��������ٱ༭���� + 1
    int insert = editDistanceDFSMem(s, t, mem, i, j - 1);
    int del = editDistanceDFSMem(s, t, mem, i - 1, j);
    int replace = editDistanceDFSMem(s, t, mem, i - 1, j - 1);
    // ��¼���������ٱ༭����
    mem[i][j] = min(min(insert, del), replace) + 1;
    return mem[i][j];
}

/* �༭���룺��̬�滮 */
int editDistanceDP(string s, string t) {
    int n = s.length(), m = t.length();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    // ״̬ת�ƣ���������
    for (int i = 1; i <= n; i++) {
        dp[i][0] = i;
    }
    for (int j = 1; j <= m; j++) {
        dp[0][j] = j;
    }
    // ״̬ת�ƣ������к���
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s[i - 1] == t[j - 1]) {
                // �����ַ���ȣ���ֱ�����������ַ�
                dp[i][j] = dp[i - 1][j - 1];
            }
            else {
                // ���ٱ༭���� = ���롢ɾ�����滻�����ֲ��������ٱ༭���� + 1
                dp[i][j] = min(min(dp[i][j - 1], dp[i - 1][j]), dp[i - 1][j - 1]) + 1;
            }
        }
    }
    return dp[n][m];
}

/* �༭���룺�ռ��Ż���Ķ�̬�滮 */
int editDistanceDPComp(string s, string t) {
    int n = s.length(), m = t.length();
    vector<int> dp(m + 1, 0);
    // ״̬ת�ƣ�����
    for (int j = 1; j <= m; j++) {
        dp[j] = j;
    }
    // ״̬ת�ƣ�������
    for (int i = 1; i <= n; i++) {
        // ״̬ת�ƣ�����
        int leftup = dp[0]; // �ݴ� dp[i-1, j-1]
        dp[0] = i;
        // ״̬ת�ƣ�������
        for (int j = 1; j <= m; j++) {
            int temp = dp[j];
            if (s[i - 1] == t[j - 1]) {
                // �����ַ���ȣ���ֱ�����������ַ�
                dp[j] = leftup;
            }
            else {
                // ���ٱ༭���� = ���롢ɾ�����滻�����ֲ��������ٱ༭���� + 1
                dp[j] = min(min(dp[j - 1], dp[j]), leftup) + 1;
            }
            leftup = temp; // ����Ϊ��һ�ֵ� dp[i-1, j-1]
        }
    }
    return dp[m];
}

/* Driver Code */
int main() {
    string s = "bag";
    string t = "pack";
    int n = s.length(), m = t.length();

    // ��������
    int res = editDistanceDFS(s, t, n, m);
    cout << "�� " << s << " ����Ϊ " << t << " ������Ҫ�༭ " << res << " ��\n";

    // ���仯����
    vector<vector<int>> mem(n + 1, vector<int>(m + 1, -1));
    res = editDistanceDFSMem(s, t, mem, n, m);
    cout << "�� " << s << " ����Ϊ " << t << " ������Ҫ�༭ " << res << " ��\n";

    // ��̬�滮
    res = editDistanceDP(s, t);
    cout << "�� " << s << " ����Ϊ " << t << " ������Ҫ�༭ " << res << " ��\n";

    // �ռ��Ż���Ķ�̬�滮
    res = editDistanceDPComp(s, t);
    cout << "�� " << s << " ����Ϊ " << t << " ������Ҫ�༭ " << res << " ��\n";

    return 0;
}
