#include "../utils/common.hpp"

 /* �����㷨��n �ʺ� */
void backtrack(int row, int n, vector<vector<string>>& state, vector<vector<vector<string>>>& res, vector<bool>& cols,
    vector<bool>& diags1, vector<bool>& diags2) {
    // ��������������ʱ����¼��
    if (row == n) {
        res.push_back(state);
        return;
    }
    // ����������
    for (int col = 0; col < n; col++) {
        // ����ø��Ӷ�Ӧ�����Խ��ߺʹζԽ���
        int diag1 = row - col + n - 1;
        int diag2 = row + col;
        // ��֦��������ø��������С����Խ��ߡ��ζԽ����ϴ��ڻʺ�
        if (!cols[col] && !diags1[diag1] && !diags2[diag2]) {
            // ���ԣ����ʺ�����ڸø���
            state[row][col] = "Q";
            cols[col] = diags1[diag1] = diags2[diag2] = true;
            // ������һ��
            backtrack(row + 1, n, state, res, cols, diags1, diags2);
            // ���ˣ����ø��ӻָ�Ϊ��λ
            state[row][col] = "#";
            cols[col] = diags1[diag1] = diags2[diag2] = false;
        }
    }
}

/* ��� n �ʺ� */
vector<vector<vector<string>>> nQueens(int n) {
    // ��ʼ�� n*n ��С�����̣����� 'Q' ����ʺ�'#' �����λ
    vector<vector<string>> state(n, vector<string>(n, "#"));
    vector<bool> cols(n, false);           // ��¼���Ƿ��лʺ�
    vector<bool> diags1(2 * n - 1, false); // ��¼���Խ������Ƿ��лʺ�
    vector<bool> diags2(2 * n - 1, false); // ��¼�ζԽ������Ƿ��лʺ�
    vector<vector<vector<string>>> res;

    backtrack(0, n, state, res, cols, diags1, diags2);

    return res;
}

/* Driver Code */
int main() {
    int n = 4;
    vector<vector<vector<string>>> res = nQueens(n);

    cout << "�������̳���Ϊ " << n << endl;
    cout << "�ʺ���÷������� " << res.size() << " ��" << endl;
    for (const vector<vector<string>>& state : res) {
        cout << "--------------------" << endl;
        for (const vector<string>& row : state) {
            printVector(row);
        }
    }

    return 0;
}
