#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <map>
using namespace std;

class Table {
public:
	vector<string> attrName;
	vector<vector<string> > data;

	vector<vector<string> > attrValueList;
	void extractAttrValue();
};

class Node {
public:
	int criteriaAttrIndex;
	string attrValue;

	int treeIndex;
	bool isLeaf;
	string label;

	vector<int > children;

	Node();
};

class DecisionTree {
public:
	Table initialTable;
	vector<Node> tree;

	DecisionTree(Table table);

	string guess(vector<string> row);
	int dfs(vector<string>& row, int here);
	void run(Table table, int nodeIndex);
	double getEstimatedError(double f, int N);
	pair<string, int> getMajorityLabel(Table table);
	bool isLeafNode(Table table);
	int getSelectedAttribute(Table table);
	double getGainRatio(Table table, int attrIndex);
	double getInfoD(Table table);
	double getInfoAttrD(Table table, int attrIndex);
	double getGain(Table table, int attrIndex);
	double getSplitInfoAttrD(Table table, int attrIndex);
	void printTree(int nodeIndex, string branch);
};

class InputReader {
private:
	ifstream fin;
	Table table;
public:
	InputReader(string filename);
	void parse();
	Table getTable();

};

class OutputPrinter {
private:
	ofstream fout;
public:
	OutputPrinter(string filename);

	string joinByTab(vector<string> row);
	void addLine(string str);
};