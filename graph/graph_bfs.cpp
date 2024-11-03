#include "../utils/common.hpp"
#include "./graph_adjacency_list.cpp"

 /* ������ȱ��� */
 // ʹ���ڽӱ�����ʾͼ���Ա��ȡָ������������ڽӶ���
vector<Vertex*> graphBFS(GraphAdjList& graph, Vertex* startVet) {
    // �����������
    vector<Vertex*> res;
    // ��ϣ���ϣ����ڼ�¼�ѱ����ʹ��Ķ���
    unordered_set<Vertex*> visited = { startVet };
    // ��������ʵ�� BFS
    queue<Vertex*> que;
    que.push(startVet);
    // �Զ��� vet Ϊ��㣬ѭ��ֱ�����������ж���
    while (!que.empty()) {
        Vertex* vet = que.front();
        que.pop();          // ���׶������
        res.push_back(vet); // ��¼���ʶ���
        // �����ö���������ڽӶ���
        for (auto adjVet : graph.adjList[vet]) {
            if (visited.count(adjVet))
                continue;            // �����ѱ����ʵĶ���
            que.push(adjVet);        // ֻ���δ���ʵĶ���
            visited.emplace(adjVet); // ��Ǹö����ѱ�����
        }
    }
    // ���ض����������
    return res;
}

/* Driver Code */
int main() {
    /* ��ʼ������ͼ */
    vector<Vertex*> v = valsToVets({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    vector<vector<Vertex*>> edges = { {v[0], v[1]}, {v[0], v[3]}, {v[1], v[2]}, {v[1], v[4]},
                                      {v[2], v[5]}, {v[3], v[4]}, {v[3], v[6]}, {v[4], v[5]},
                                      {v[4], v[7]}, {v[5], v[8]}, {v[6], v[7]}, {v[7], v[8]} };
    GraphAdjList graph(edges);
    cout << "\n��ʼ����ͼΪ\\n";
    graph.print();

    /* ������ȱ��� */
    vector<Vertex*> res = graphBFS(graph, v[0]);
    cout << "\n������ȱ�����BFS����������Ϊ" << endl;
    printVector(vetsToVals(res));

    // �ͷ��ڴ�
    for (Vertex* vet : v) {
        delete vet;
    }

    return 0;
}
