#include "./graph_adjacency_list.cpp"

 /* Driver Code */
int main() {
    /* ��ʼ������ͼ */
    vector<Vertex*> v = valsToVets(vector<int>{1, 3, 2, 5, 4});
    vector<vector<Vertex*>> edges = { {v[0], v[1]}, {v[0], v[3]}, {v[1], v[2]},
                                      {v[2], v[3]}, {v[2], v[4]}, {v[3], v[4]} };
    GraphAdjList graph(edges);
    cout << "\n��ʼ����ͼΪ" << endl;
    graph.print();

    /* ��ӱ� */
    // ���� 1, 2 �� v[0], v[2]
    graph.addEdge(v[0], v[2]);
    cout << "\n��ӱ� 1-2 ��ͼΪ" << endl;
    graph.print();

    /* ɾ���� */
    // ���� 1, 3 �� v[0], v[1]
    graph.removeEdge(v[0], v[1]);
    cout << "\nɾ���� 1-3 ��ͼΪ" << endl;
    graph.print();

    /* ��Ӷ��� */
    Vertex* v5 = new Vertex(6);
    graph.addVertex(v5);
    cout << "\n��Ӷ��� 6 ��ͼΪ" << endl;
    graph.print();

    /* ɾ������ */
    // ���� 3 �� v[1]
    graph.removeVertex(v[1]);
    cout << "\nɾ������ 3 ��ͼΪ" << endl;
    graph.print();

    // �ͷ��ڴ�
    for (Vertex* vet : v) {
        delete vet;
    }

    return 0;
}
