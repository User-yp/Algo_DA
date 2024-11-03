#include "../utils/common.hpp"

 /* �����ڽӱ�ʵ�ֵ�����ͼ�� */
class GraphAdjList {
public:
    // �ڽӱ�key�����㣬value���ö���������ڽӶ���
    unordered_map<Vertex*, vector<Vertex*>> adjList;

    /* �� vector ��ɾ��ָ���ڵ� */
    void remove(vector<Vertex*>& vec, Vertex* vet) {
        for (int i = 0; i < vec.size(); i++) {
            if (vec[i] == vet) {
                vec.erase(vec.begin() + i);
                break;
            }
        }
    }

    /* ���췽�� */
    GraphAdjList(const vector<vector<Vertex*>>& edges) {
        // ������ж���ͱ�
        for (const vector<Vertex*>& edge : edges) {
            addVertex(edge[0]);
            addVertex(edge[1]);
            addEdge(edge[0], edge[1]);
        }
    }

    /* ��ȡ�������� */
    int size() {
        return adjList.size();
    }

    /* ��ӱ� */
    void addEdge(Vertex* vet1, Vertex* vet2) {
        if (!adjList.count(vet1) || !adjList.count(vet2) || vet1 == vet2)
            throw invalid_argument("�����ڶ���");
        // ��ӱ� vet1 - vet2
        adjList[vet1].push_back(vet2);
        adjList[vet2].push_back(vet1);
    }

    /* ɾ���� */
    void removeEdge(Vertex* vet1, Vertex* vet2) {
        if (!adjList.count(vet1) || !adjList.count(vet2) || vet1 == vet2)
            throw invalid_argument("�����ڶ���");
        // ɾ���� vet1 - vet2
        remove(adjList[vet1], vet2);
        remove(adjList[vet2], vet1);
    }

    /* ��Ӷ��� */
    void addVertex(Vertex* vet) {
        if (adjList.count(vet))
            return;
        // ���ڽӱ������һ��������
        adjList[vet] = vector<Vertex*>();
    }

    /* ɾ������ */
    void removeVertex(Vertex* vet) {
        if (!adjList.count(vet))
            throw invalid_argument("�����ڶ���");
        // ���ڽӱ���ɾ������ vet ��Ӧ������
        adjList.erase(vet);
        // �����������������ɾ�����а��� vet �ı�
        for (auto& adj : adjList) {
            remove(adj.second, vet);
        }
    }

    /* ��ӡ�ڽӱ� */
    void print() {
        cout << "�ڽӱ� =" << endl;
        for (auto& adj : adjList) {
            const auto& key = adj.first;
            const auto& vec = adj.second;
            cout << key->val << ": ";
            printVector(vetsToVals(vec));
        }
    }
};

// ����������� graph_adjacency_list_test.cpp
