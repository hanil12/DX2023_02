#include "BST.h"
#include <iostream>

BinarySearchTree::BinarySearchTree()
{
}

BinarySearchTree::~BinarySearchTree()
{
}

void BinarySearchTree::Insert(int key)
{
	Node* newNode = new Node(key);

	if (_root == nullptr)
	{
		_root = newNode;
		return;
	}

	Node* node = _root;
	Node* parent = nullptr;

	while (true)
	{
		if(node == nullptr)
			break;

		parent = node;
		if (key < node->key)
		{
			node = node->left;
		}
		else
		{
			node = node->right;
		}
	}

	newNode->parent = parent;
	if(key < parent->key)
		parent->left = newNode;
	else
		parent->right = newNode;
}

void BinarySearchTree::PrintTree(Node* root)
{
	// 전위 순회 : 루트 ~ 왼쪽 ~ 오른쪽
	// 중위 순회 : 왼쪽 ~ 루트 ~ 오른쪽
	// 후위 순회 : 왼쪽 ~ 오른쪽 ~ 루트

	if(root == nullptr)
		return;
	std::cout << root->key << std::endl;
	PrintTree(root->left);
	PrintTree(root->right);
}

Node* BinarySearchTree::Search(Node* root, int key)
{
	// 1. 기저사항 처리
	if(root == nullptr)
		return root;

	// 2. 구하기
	if(root->key == key)
		return root;

	if(key < root->key)
		return Search(root->left, key);
	else
		return Search(root->right, key);

	return nullptr;
}

Node* BinarySearchTree::Min(Node* root)
{
	// 반복 버전
	//Node* minNode = root;

	//while (true)
	//{
	//	if(minNode->left == nullptr)
	//		break;
	//	minNode = minNode->left;
	//}

	//return minNode;

	// 재귀버전

	// 1 기저사항
	if(root == nullptr)
		return nullptr;

	if(root->left != nullptr)
		return Min(root->left);

	return root;
}

Node* BinarySearchTree::Max(Node* root)
{
	if (root == nullptr)
		return nullptr;

	if (root->right != nullptr)
		return Max(root->right);

	return root;
}

Node* BinarySearchTree::Previous(Node* root)
{
	return nullptr;
}

Node* BinarySearchTree::Next(Node* root)
{
	return nullptr;
}

void BinarySearchTree::Replace(Node* node1, Node* node2)
{
	// node1이 루트노드였다.
	if(node1->parent == nullptr)
		_root = node2;

	// node1이 부모쪽에서 왼쪽에 있는 노드일 때
	else if (node1 == node1->parent->left)
	{
		node1->parent->left = node2;
	}
	// node1이 부쪽에서 오른쪽에 있는 노드일 때
	else
	{
		node1->parent->right = node2;
	}

	if (node2 != nullptr)
	{
		node2->parent = node1->parent;
	}

	delete node1;
}

void BinarySearchTree::Delete(Node* Node)
{
}
