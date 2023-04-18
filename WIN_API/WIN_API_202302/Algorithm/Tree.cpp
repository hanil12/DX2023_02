#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;

struct Node
{
	Node() {}
	Node(string data) : data(data) {}
	~Node() {}

	Node* parent = nullptr;
	vector<Node*> children;

	string data;
};

Node* CreateTree()
{
	Node* root = new Node("������");
	{
		Node* node = new Node("���α׷�����");
		root->children.push_back(node);
		{
			Node* leaf1 = new Node("Ŭ���̾�Ʈ");
			node->children.push_back(leaf1);

			Node* leaf2 = new Node("����");
			node->children.push_back(leaf2);

			Node* leaf3 = new Node("����");
			node->children.push_back(leaf3);
		}
	}

	{
		Node* node = new Node("��ȹ��");
		root->children.push_back(node);
		{
			Node* leaf1 = new Node("����������");
			node->children.push_back(leaf1);

			Node* leaf2 = new Node("���丮");
			node->children.push_back(leaf2);

			Node* leaf3 = new Node("�뷱��");
			node->children.push_back(leaf3);
		}
	}

	{
		Node* node = new Node("��Ʈ��");
		root->children.push_back(node);
		{
			Node* leaf1 = new Node("���");
			node->children.push_back(leaf1);

			Node* leaf2 = new Node("�𵨸�");
			node->children.push_back(leaf2);

			Node* leaf3 = new Node("UI");
			node->children.push_back(leaf3);
		}
	}

	return root;
}

void PrintTree(Node* node)
{
	cout << node->data << endl;

	for(auto child : node->children)
		PrintTree(child);
}

int main()
{
	Node* root = CreateTree();
	PrintTree(root->children[0]);

	return 0;
}