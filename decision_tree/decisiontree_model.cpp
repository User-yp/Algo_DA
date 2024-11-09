#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <map>
#include <sstream>std::stringstream ss;
using namespace std;

class Table {
public:
	vector<string> attrName;
	vector<vector<string> > data;

	vector<vector<string> > attrValueList;
	void extractAttrValue() {
		attrValueList.resize(attrName.size());
		for (int j = 0; j < attrName.size(); j++) {
			map<string, int> value;
			for (int i = 0; i < data.size(); i++) {
				value[data[i][j]] = 1;
			}

			for (auto iter = value.begin(); iter != value.end(); iter++) {
				attrValueList[j].push_back(iter->first);
			}
		}
	}
};

class Node {
public:
	int criteriaAttrIndex;
	string attrValue;

	int treeIndex;
	bool isLeaf;
	string label;

	vector<int > children;

	Node() {
		isLeaf = false;
	}
	// ���л�����  
	string serialize() const {
		stringstream ss;
		ss << criteriaAttrIndex << ","    // ���Ե�����  
			<< attrValue << ","             // ����ֵ  
			<< treeIndex << ","             // �ڵ�����  
			<< isLeaf << ","                // �Ƿ�ΪҶ�ӽڵ�  
			<< label << ",";                // ��ǩ  

		// �����л��ӽڵ���������ӽڵ�����  
		ss << children.size();
		for (const int& child : children) {
			ss << "," << child; // �������ӽڵ�����  
		}

		return ss.str();
	}

	// �����л�����  
	static Node deserialize(const string& data) {
		stringstream ss(data);
		Node node;
		string temp;

		// ��ȡ�����ֶ�  
		getline(ss, temp, ',');
		node.criteriaAttrIndex = stoi(temp);  // ��ȡ��������  

		getline(ss, node.attrValue, ',');      // ��ȡ����ֵ  
		getline(ss, temp, ',');
		node.treeIndex = stoi(temp);           // ��ȡ�ڵ�����  

		getline(ss, temp, ',');
		node.isLeaf = (temp == "1" || temp == "true"); // ��ȡ�Ƿ�ΪҶ�ӽڵ�  

		getline(ss, node.label, ',');           // ��ȡ��ǩ  

		// ��ȡ�ӽڵ����Ϣ  
		int childrenCount;
		getline(ss, temp, ',');
		childrenCount = stoi(temp);             // ��ȡ�ӽڵ�����  

		node.children.resize(childrenCount);    // ��ʼ���ӽڵ�������С  
		for (int i = 0; i < childrenCount; ++i) {
			getline(ss, temp, ',');
			node.children[i] = stoi(temp);     // �����ȡ�ӽڵ�����  
		}

		return node;
	}
};

class DecisionTree {
public:
	Table initialTable;
	vector<Node> tree;

	DecisionTree() {
		// ������Գ�ʼ����Ҫ�ı��������û�п�������  
		tree.clear();
		// �����������������Ҫ�ĳ�ʼ������  
	}
	DecisionTree(Table table) {
		initialTable = table;
		initialTable.extractAttrValue();

		Node root;
		root.treeIndex = 0;
		tree.push_back(root);
		run(initialTable, 0);
		printTree(0, "");

		cout << "<-- finish generating decision tree -->" << endl << endl;
	}

	string guess(vector<string> row) {
		string label = "";
		int leafNode = dfs(row, 0);
		if (leafNode == -1) {
			return "dfs failed";
		}
		label = tree[leafNode].label;
		return label;
	}

	int dfs(vector<string>& row, int here) {
		if (tree[here].isLeaf) {
			return here;
		}

		int criteriaAttrIndex = tree[here].criteriaAttrIndex;

		for (int i = 0; i < tree[here].children.size(); i++) {
			int next = tree[here].children[i];

			if (row[criteriaAttrIndex] == tree[next].attrValue) {
				return dfs(row, next);
			}
		}
		return -1;
	}

	void run(Table table, int nodeIndex) {
		if (isLeafNode(table) == true) {
			tree[nodeIndex].isLeaf = true;
			tree[nodeIndex].label = table.data.back().back();
			return;
		}

		int selectedAttrIndex = getSelectedAttribute(table);

		map<string, vector<int> > attrValueMap;
		for (int i = 0; i < table.data.size(); i++) {
			attrValueMap[table.data[i][selectedAttrIndex]].push_back(i);
		}

		tree[nodeIndex].criteriaAttrIndex = selectedAttrIndex;

		pair<string, int> majority = getMajorityLabel(table);
		if ((double)majority.second / table.data.size() > 0.8) {
			tree[nodeIndex].isLeaf = true;
			tree[nodeIndex].label = majority.first;
			return;
		}

		for (int i = 0; i < initialTable.attrValueList[selectedAttrIndex].size(); i++) {
			string attrValue = initialTable.attrValueList[selectedAttrIndex][i];

			Table nextTable;
			vector<int> candi = attrValueMap[attrValue];
			for (int i = 0; i < candi.size(); i++) {
				nextTable.data.push_back(table.data[candi[i]]);
			}

			Node nextNode;
			nextNode.attrValue = attrValue;
			nextNode.treeIndex = (int)tree.size();
			tree[nodeIndex].children.push_back(nextNode.treeIndex);
			tree.push_back(nextNode);

			// for empty table
			if (nextTable.data.size() == 0) {
				nextNode.isLeaf = true;
				nextNode.label = getMajorityLabel(table).first;
				tree[nextNode.treeIndex] = nextNode;
			}
			else {
				run(nextTable, nextNode.treeIndex);
			}
		}
	}

	double getEstimatedError(double f, int N) {
		double z = 0.69;
		if (N == 0) {
			cout << ":: getEstimatedError :: N is zero" << endl;
			exit(0);
		}
		return (f + z * z / (2 * N) + z * sqrt(f / N - f * f / N + z * z / (4 * N * N))) / (1 + z * z / N);
	}

	pair<string, int> getMajorityLabel(Table table) {
		string majorLabel = "";
		int majorCount = 0;

		map<string, int> labelCount;
		for (int i = 0; i < table.data.size(); i++) {
			labelCount[table.data[i].back()]++;

			if (labelCount[table.data[i].back()] > majorCount) {
				majorCount = labelCount[table.data[i].back()];
				majorLabel = table.data[i].back();
			}
		}

		return { majorLabel, majorCount };
	}


	bool isLeafNode(Table table) {
		for (int i = 1; i < table.data.size(); i++) {
			if (table.data[0].back() != table.data[i].back()) {
				return false;
			}
		}
		return true;
	}

	int getSelectedAttribute(Table table) {
		int maxAttrIndex = -1;
		double maxAttrValue = 0.0;

		// except label
		for (int i = 0; i < initialTable.attrName.size() - 1; i++) {
			if (maxAttrValue < getGainRatio(table, i)) {
				maxAttrValue = getGainRatio(table, i);
				maxAttrIndex = i;
			}
		}

		return maxAttrIndex;
	}

	double getGainRatio(Table table, int attrIndex) {
		if (attrIndex < 0 || attrIndex >= table.attrName.size()) {
			throw std::out_of_range("Attribute index is out of range");
		}
		return getGain(table, attrIndex) / getSplitInfoAttrD(table, attrIndex);
	}

	double getInfoD(Table table) {
		double ret = 0.0;

		int itemCount = (int)table.data.size();
		map<string, int> labelCount;

		for (int i = 0; i < table.data.size(); i++) {
			labelCount[table.data[i].back()]++;
		}

		for (auto iter = labelCount.begin(); iter != labelCount.end(); iter++) {
			double p = (double)iter->second / itemCount;

			ret += -1.0 * p * log(p) / log(2);
		}

		return ret;
	}

	double getInfoAttrD(Table table, int attrIndex) {
		double ret = 0.0;
		int itemCount = (int)table.data.size();

		map<string, vector<int> > attrValueMap;
		for (int i = 0; i < table.data.size(); i++) {
			attrValueMap[table.data[i][attrIndex]].push_back(i);
		}

		for (auto iter = attrValueMap.begin(); iter != attrValueMap.end(); iter++) {
			Table nextTable;
			for (int i = 0; i < iter->second.size(); i++) {
				nextTable.data.push_back(table.data[iter->second[i]]);
			}
			int nextItemCount = (int)nextTable.data.size();

			ret += (double)nextItemCount / itemCount * getInfoD(nextTable);
		}

		return ret;
	}

	double getGain(Table table, int attrIndex) {
		return getInfoD(table) - getInfoAttrD(table, attrIndex);
	}

	double getSplitInfoAttrD(Table table, int attrIndex) {
		double ret = 0.0;

		int itemCount = (int)table.data.size();

		map<string, vector<int> > attrValueMap;
		for (int i = 0; i < table.data.size(); i++) {
			attrValueMap[table.data[i][attrIndex]].push_back(i);
		}

		for (auto iter = attrValueMap.begin(); iter != attrValueMap.end(); iter++) {
			Table nextTable;
			for (int i = 0; i < iter->second.size(); i++) {
				nextTable.data.push_back(table.data[iter->second[i]]);
			}
			int nextItemCount = (int)nextTable.data.size();

			double d = (double)nextItemCount / itemCount;
			ret += -1.0 * d * log(d) / log(2);
		}

		return ret;
	}
	void saveModel(const string& filename) {
		ofstream fout(filename);
		if (!fout) {
			cout << filename << " file could not be opened\n";
			exit(0);
		}
		// Serialize the tree  
		for (const auto& node : tree) {
			// Assuming Node class has a method to serialize itself to output stream  
			fout << node.serialize() << endl; // ��Ҫʵ�� serialize() ����  
		}
		fout.close();
	}
	void loadModel(const string& filename) {
		ifstream fin(filename);
		if (!fin) {
			cout << filename << " file could not be opened\n";
			exit(0);
		}
		string line;
		while (getline(fin, line)) {
			Node node = Node::deserialize(line); // ��Ҫʵ�� deserialize ����  
			tree.push_back(node);
		}
		fin.close();
	}
	/*
	 * Enumerates through all the nodes of the tree and prints all the branches
	 */
	void printTree(int nodeIndex, string branch) {
		if (tree[nodeIndex].isLeaf == true)
			cout << branch << "Label: " << tree[nodeIndex].label << "\n";

		for (int i = 0; i < tree[nodeIndex].children.size(); i++) {
			int childIndex = tree[nodeIndex].children[i];

			string attributeName = initialTable.attrName[tree[nodeIndex].criteriaAttrIndex];
			string attributeValue = tree[childIndex].attrValue;

			printTree(childIndex, branch + attributeName + " = " + attributeValue + ", ");
		}
	}
	void DecisionTree::train(const Table& newData) {
		// �������ݺϲ�����ʼ���ݼ���  
		for (const auto& row : newData.data) {
			initialTable.data.push_back(row);
		}

		// ��յ�ǰ������ѡ��  
		tree.clear();

		// ���³�ʼ����������ѵ��  
		Node root;
		root.treeIndex = 0;
		tree.push_back(root);
		initialTable.extractAttrValue(); // ������ȡ����ֵ����Ӧ�µ�����  
		run(initialTable, 0); // ѵ���µľ�����  
		printTree(0, ""); // ��ӡ�����ɵ���  

		cout << "<-- finish re-training decision tree -->" << endl << endl;
	}
	bool fileExists(const std::string& filename) {
		std::ifstream file(filename);
		return file.good(); // ����ļ��ɶ����򷵻� true  
	}
};


class InputReader {
private:
	ifstream fin;
	Table table;
public:
	InputReader(string filename) {
		fin.open(filename);
		if (!fin) {
			cout << filename << " file could not be opened\n";
			exit(0);
		}
		parse();
	}
	void parse() {
		string str;
		bool isAttrName = true;
		while (!getline(fin, str).eof()) {
			vector<string> row;
			int pre = 0;
			for (int i = 0; i < str.size(); i++) {
				if (str[i] == '\t') {
					string col = str.substr(pre, i - pre);

					row.push_back(col);
					pre = i + 1;
				}
			}
			string col = str.substr(pre, str.size() - pre - 1);
			row.push_back(col);

			if (isAttrName) {
				table.attrName = row;
				isAttrName = false;
			}
			else {
				table.data.push_back(row);
			}
		}
	}
	Table getTable() {
		return table;
	}

};

class OutputPrinter {
private:
	ofstream fout;
public:
	OutputPrinter(string filename) {
		fout.open(filename);
		if (!fout) {
			cout << filename << " file could not be opened\n";
			exit(0);
		}
	}

	string joinByTab(vector<string> row) {
		string ret = "";
		for (int i = 0; i < row.size(); i++) {
			ret += row[i];
			if (i != row.size() - 1) {
				ret += '\t';
			}
		}
		return ret;
	}

	void addLine(string str) {
		fout << str << endl;
	}
};
int main() {
	const char* modelFile = "C:/Users/25069/source/repos/Algo_DA/source/dt_model.txt"; // ģ�ͱ���·��  ../source/dt_model.txt
	string modelFileName = modelFile;

	DecisionTree decisionTree;

	//if (DecisionTree::fileExists(modelFileName)) { // ������Ҫʵ�� fileExists ����  
	//	decisionTree.loadModel(modelFileName);
	//}

	// ���ڶ���ѵ���ļ�  
	const char* trainFile = "C:/Users/25069/source/repos/Algo_DA/source/dt_train.txt";
	InputReader trainInputReader(trainFile);

	// ׷��ѵ������������е�������˴��ɺϲ�  
	// ������Ҫ�߼����� trainInputReader.getTable().data �ϲ��� decisionTree �������У�������ѵ��  
	decisionTree.train(trainInputReader.getTable());

	// ����ѵ�����ģ��  
	decisionTree.saveModel(modelFileName);

	// ��ȡ�������ݺ�������  
	const char* testFile = "C:/Users/25069/source/repos/Algo_DA/source/dt_test.txt";
	InputReader testInputReader(testFile);
	Table test = testInputReader.getTable();

	const char* resultFile = "C:/Users/25069/source/repos/Algo_DA/source/dt_result.txt";
	OutputPrinter outputPrinter(resultFile);
	outputPrinter.addLine(outputPrinter.joinByTab(test.attrName));

	for (int i = 0; i < test.data.size(); i++) {
		vector<string> result = test.data[i];
		result.push_back(decisionTree.guess(test.data[i]));
		outputPrinter.addLine(outputPrinter.joinByTab(result));
	}

	return 0;
}
//int main() {
//	//�޸�Ϊ�����ʵ��·��
//	const char* trainFile = "../source/dt_train.txt";
//	const char* testFile = "../source/dt_test.txt";
//	const char* resultFile = "../source/dt_result";
//
//	string trainFileName = trainFile;
//	InputReader trainInputReader(trainFileName);
//	DecisionTree decisionTree(trainInputReader.getTable());
//
//	string testFileName = testFile;
//	InputReader testInputReader(testFileName);
//	Table test = testInputReader.getTable();
//
//	string resultFileName = resultFile;
//	OutputPrinter outputPrinter(resultFileName);
//	outputPrinter.addLine(outputPrinter.joinByTab(test.attrName));
//	for (int i = 0; i < test.data.size(); i++) {
//		vector<string> result = test.data[i];
//		result.push_back(decisionTree.guess(test.data[i]));
//		outputPrinter.addLine(outputPrinter.joinByTab(result));
//	}
//	return 0;
//}