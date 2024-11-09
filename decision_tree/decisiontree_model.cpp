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
	// 序列化方法  
	string serialize() const {
		stringstream ss;
		ss << criteriaAttrIndex << ","    // 属性的索引  
			<< attrValue << ","             // 属性值  
			<< treeIndex << ","             // 节点索引  
			<< isLeaf << ","                // 是否为叶子节点  
			<< label << ",";                // 标签  

		// 先序列化子节点的数量和子节点索引  
		ss << children.size();
		for (const int& child : children) {
			ss << "," << child; // 逐个添加子节点索引  
		}

		return ss.str();
	}

	// 反序列化方法  
	static Node deserialize(const string& data) {
		stringstream ss(data);
		Node node;
		string temp;

		// 读取各个字段  
		getline(ss, temp, ',');
		node.criteriaAttrIndex = stoi(temp);  // 读取属性索引  

		getline(ss, node.attrValue, ',');      // 读取属性值  
		getline(ss, temp, ',');
		node.treeIndex = stoi(temp);           // 读取节点索引  

		getline(ss, temp, ',');
		node.isLeaf = (temp == "1" || temp == "true"); // 读取是否为叶子节点  

		getline(ss, node.label, ',');           // 读取标签  

		// 读取子节点的信息  
		int childrenCount;
		getline(ss, temp, ',');
		childrenCount = stoi(temp);             // 读取子节点数量  

		node.children.resize(childrenCount);    // 初始化子节点容器大小  
		for (int i = 0; i < childrenCount; ++i) {
			getline(ss, temp, ',');
			node.children[i] = stoi(temp);     // 逐个读取子节点索引  
		}

		return node;
	}
};

class DecisionTree {
public:
	Table initialTable;
	vector<Node> tree;

	DecisionTree() {
		// 这里可以初始化需要的变量，如果没有可以留空  
		tree.clear();
		// 这里可以设置其他必要的初始化操作  
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
			fout << node.serialize() << endl; // 需要实现 serialize() 方法  
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
			Node node = Node::deserialize(line); // 需要实现 deserialize 方法  
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
		// 将新数据合并到初始数据集中  
		for (const auto& row : newData.data) {
			initialTable.data.push_back(row);
		}

		// 清空当前树（可选）  
		tree.clear();

		// 重新初始化树并进行训练  
		Node root;
		root.treeIndex = 0;
		tree.push_back(root);
		initialTable.extractAttrValue(); // 重新提取属性值以适应新的数据  
		run(initialTable, 0); // 训练新的决策树  
		printTree(0, ""); // 打印新生成的树  

		cout << "<-- finish re-training decision tree -->" << endl << endl;
	}
	bool fileExists(const std::string& filename) {
		std::ifstream file(filename);
		return file.good(); // 如果文件可读，则返回 true  
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
	const char* modelFile = "C:/Users/25069/source/repos/Algo_DA/source/dt_model.txt"; // 模型保存路径  ../source/dt_model.txt
	string modelFileName = modelFile;

	DecisionTree decisionTree;

	//if (DecisionTree::fileExists(modelFileName)) { // 不再需要实现 fileExists 方法  
	//	decisionTree.loadModel(modelFileName);
	//}

	// 现在读入训练文件  
	const char* trainFile = "C:/Users/25069/source/repos/Algo_DA/source/dt_train.txt";
	InputReader trainInputReader(trainFile);

	// 追加训练，如果有已有的数据则此处可合并  
	// 这里需要逻辑来将 trainInputReader.getTable().data 合并到 decisionTree 的数据中，并进行训练  
	decisionTree.train(trainInputReader.getTable());

	// 保存训练后的模型  
	decisionTree.saveModel(modelFileName);

	// 读取测试数据和输出结果  
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
//	//修改为计算机实际路径
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