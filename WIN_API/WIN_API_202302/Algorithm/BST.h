#pragma once

struct Node
{
	Node() {}
	Node(int key) : key(key) {}

	Node* left = nullptr;
	Node* right = nullptr;
	Node* parent = nullptr;

	int key = -1;
	int data = 0;
};

class BinarySearchTree
{
public:
	BinarySearchTree();
	~BinarySearchTree();

	void Insert(int key);
	void PrintTree(Node* root);

	Node* Search(Node* root, int key);
	Node* Min(Node* root);
	Node* Max(Node* root);

	Node* Previous(Node* root);
	Node* Next(Node* root);

	void Replace(Node* node1, Node* node2); // node1�� ��ü�� ���� ����
	void Delete(Node* Node); // �ش��� ����

public:
	Node* _root = nullptr;
};