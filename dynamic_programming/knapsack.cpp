#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/* 0-1 �������������� */
int knapsackDFS(vector<int>& wgt, vector<int>& val, int i, int c) {
    // ����ѡ��������Ʒ�򱳰���ʣ���������򷵻ؼ�ֵ 0
    if (i == 0 || c == 0) {
        return 0;
    }
    // ������������������ֻ��ѡ�񲻷��뱳��
    if (wgt[i - 1] > c) {
        return knapsackDFS(wgt, val, i - 1, c);
    }
    // ���㲻����ͷ�����Ʒ i ������ֵ
    int no = knapsackDFS(wgt, val, i - 1, c);
    int yes = knapsackDFS(wgt, val, i - 1, c - wgt[i - 1]) + val[i - 1];
    // �������ַ����м�ֵ�������һ��
    return max(no, yes);
}

/* 0-1 ���������仯���� */
int knapsackDFSMem(vector<int>& wgt, vector<int>& val, vector<vector<int>>& mem, int i, int c) {
    // ����ѡ��������Ʒ�򱳰���ʣ���������򷵻ؼ�ֵ 0
    if (i == 0 || c == 0) {
        return 0;
    }
    // �����м�¼����ֱ�ӷ���
    if (mem[i][c] != -1) {
        return mem[i][c];
    }
    // ������������������ֻ��ѡ�񲻷��뱳��
    if (wgt[i - 1] > c) {
        return knapsackDFSMem(wgt, val, mem, i - 1, c);
    }
    // ���㲻����ͷ�����Ʒ i ������ֵ
    int no = knapsackDFSMem(wgt, val, mem, i - 1, c);
    int yes = knapsackDFSMem(wgt, val, mem, i - 1, c - wgt[i - 1]) + val[i - 1];
    // ��¼���������ַ����м�ֵ�������һ��
    mem[i][c] = max(no, yes);
    return mem[i][c];
}

/* 0-1 ��������̬�滮 */
int knapsackDP(vector<int>& wgt, vector<int>& val, int cap) {
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
                dp[i][c] = max(dp[i - 1][c], dp[i - 1][c - wgt[i - 1]] + val[i - 1]);
            }
        }
    }
    return dp[n][cap];
}

/* 0-1 �������ռ��Ż���Ķ�̬�滮 */
int knapsackDPComp(vector<int>& wgt, vector<int>& val, int cap) {
    int n = wgt.size();
    // ��ʼ�� dp ��
    vector<int> dp(cap + 1, 0);
    // ״̬ת��
    for (int i = 1; i <= n; i++) {
        // �������
        for (int c = cap; c >= 1; c--) {
            if (wgt[i - 1] <= c) {
                // ��ѡ��ѡ��Ʒ i �����ַ����Ľϴ�ֵ
                dp[c] = max(dp[c], dp[c - wgt[i - 1]] + val[i - 1]);
            }
        }
    }
    return dp[cap];
}

/* Driver Code */
int main() {
    vector<int> wgt = { 10, 20, 30, 40, 50 };
    vector<int> val = { 50, 120, 150, 210, 240 };
    int cap = 50;
    int n = wgt.size();

    // ��������
    int res = knapsackDFS(wgt, val, n, cap);
    cout << "���������������������Ʒ��ֵΪ " << res << endl;

    // ���仯����
    vector<vector<int>> mem(n + 1, vector<int>(cap + 1, -1));
    res = knapsackDFSMem(wgt, val, mem, n, cap);
    cout << "���������������������Ʒ��ֵΪ " << res << endl;

    // ��̬�滮
    res = knapsackDP(wgt, val, cap);
    cout << "���������������������Ʒ��ֵΪ " << res << endl;

    // �ռ��Ż���Ķ�̬�滮
    res = knapsackDPComp(wgt, val, cap);
    cout << "���������������������Ʒ��ֵΪ " << res << endl;

    return 0;
}
