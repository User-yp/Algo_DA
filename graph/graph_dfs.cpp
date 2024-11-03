#include "../utils/common.hpp"
#include "./graph_adjacency_list.cpp"

 /* ������ȱ����������� */
void dfs(GraphAdjList& graph, unordered_set<Vertex*>& visited, vector<Vertex*>& res, Vertex* vet) {
    res.push_back(vet);   // ��¼���ʶ���
    visited.emplace(vet); // ��Ǹö����ѱ�����
    // �����ö���������ڽӶ���
    for (Vertex* adjVet : graph.adjList[vet]) {
        if (visited.count(adjVet))
            continue; // �����ѱ����ʵĶ���
        // �ݹ�����ڽӶ���
        dfs(graph, visited, res, adjVet);
    }
}

/* ������ȱ��� */
// ʹ���ڽӱ�����ʾͼ���Ա��ȡָ������������ڽӶ���
vector<Vertex*> graphDFS(GraphAdjList& graph, Vertex* startVet) {
    // �����������
    vector<Vertex*> res;
    // ��ϣ���ϣ����ڼ�¼�ѱ����ʹ��Ķ���
    unordered_set<Vertex*> visited;
    dfs(graph, visited, res, startVet);
    return res;
}

/* Driver Code */
int main() {
    /* ��ʼ������ͼ */
    vector<Vertex*> v = valsToVets(vector<int>{0, 1, 2, 3, 4, 5, 6});
    vector<vector<Vertex*>> edges = { {v[0], v[1]}, {v[0], v[3]}, {v[1], v[2]},
                                      {v[2], v[5]}, {v[4], v[5]}, {v[5], v[6]} };
    GraphAdjList graph(edges);
    cout << "\n��ʼ����ͼΪ" << endl;
    graph.print();

    /* ������ȱ��� */
    vector<Vertex*> res = graphDFS(graph, v[0]);
    cout << "\n������ȱ�����DFS����������Ϊ" << endl;
    printVector(vetsToVals(res));

    // �ͷ��ڴ�
    for (Vertex* vet : v) {
        delete vet;
    }

    return 0;
}
