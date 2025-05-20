#include <iostream>
#include <vector>
#include <queue>
using namespace std;
struct NODE {
	int key;
	NODE* p_left;
	NODE* p_right;
};

NODE* createNode(int data)
{
	NODE* newNode = new NODE;
	if (!newNode) return nullptr;
	newNode->key = data;
	newNode->p_left = nullptr;
	newNode->p_right = nullptr;
	return newNode;
}

NODE* Search(NODE* pRoot, int x)
{
	NODE* temp = pRoot;
	while (temp)
	{
		if (x > temp->key)
			temp = temp->p_right;
		else if (x < temp->key)
			temp = temp->p_left;
		else
			break;
	}
	return temp;
}

void Insert(NODE*& pRoot, int x)
{
	if (pRoot == nullptr) pRoot = createNode(x);
	else
	{
		NODE* temp = pRoot;
		while (temp)
		{
			if (x >= temp->key)
			{
				if (temp->p_right == nullptr)
				{
					temp->p_right = createNode(x);
					break;
				}
				temp = temp->p_right;
			}
			else
			{
				if (temp->p_left == nullptr)
				{
					temp->p_left = createNode(x);
					break;
				}
				temp = temp->p_left;
			}
		}

	}
}

void Remove(NODE*& pRoot, int x)
{
	if (pRoot == nullptr) return;

	if (x < pRoot->key)
		Remove(pRoot->p_left, x);
	else if (x > pRoot->key)
		Remove(pRoot->p_right, x);
	else //x == pRoot->key
	{
		if (pRoot->p_left != nullptr)//maxNODE of LeftChild
		{
			NODE* maxNodeL = pRoot->p_left;
			while (maxNodeL->p_right)
			{
				maxNodeL = maxNodeL->p_right;
			}
			pRoot->key = maxNodeL->key;
			Remove(pRoot->p_left, maxNodeL->key);
		}
		else if (pRoot->p_right != nullptr)//minNODE of RightChild
		{
			NODE* minNodeR = pRoot->p_right;
			while (minNodeR->p_left)
			{
				minNodeR = minNodeR->p_left;
			}
			pRoot->key = minNodeR->key;
			Remove(pRoot->p_right, minNodeR->key);
		}
		else// pRoot->p_left == pRoot->p_right == nullptr
		{
			NODE* temp = pRoot;
			pRoot = nullptr;
			delete temp;
		}
	}
}

NODE* createTree(int a[], int n)
{
	NODE* Tree = nullptr;
	for (int i = 0;i < n;i++)
	{
		if (Tree == nullptr) Tree = createNode(a[i]);//Haven't Root -> create Root
		else //Had Root
		{
			NODE* temp = Tree;
			while (temp)
			{
				if (a[i] >= temp->key)
				{
					if (temp->p_right)
						temp = temp->p_right;
					else
					{
						temp->p_right = createNode(a[i]);
						break;
					}
				}
				else
				{
					if (temp->p_left)
						temp = temp->p_left;
					else
					{
						temp->p_left = createNode(a[i]);
						break;
					}
				}
			}
		}
	}
	return Tree;
}

void removeTree(NODE*& pRoot)
{
	if (pRoot == nullptr) return;

	removeTree(pRoot->p_left);
	removeTree(pRoot->p_right);
	delete pRoot;
	pRoot = nullptr;
}

int Height(NODE* pRoot)
{
	if (pRoot == nullptr) return -1;
	
	int leftHeight = Height(pRoot->p_left);
	int rightHeight = Height(pRoot->p_right);
	
	if (leftHeight > rightHeight) return 1 + leftHeight;
	else return 1 + rightHeight;
}

int countLess(NODE* pRoot, int x)
{
	if (pRoot == nullptr) return 0;

	int cnt = 0;
	if (pRoot->key < x) 
		cnt = 1;
	int cntLeft = countLess(pRoot->p_left, x);
	int cntRight = countLess(pRoot->p_right, x);

	return cnt + cntLeft + cntRight;
}

int countGreater(NODE* pRoot, int x)
{
	if (pRoot == nullptr) return 0;

	int cnt = 0;
	if (pRoot->key > x)
		cnt = 1;
	int cntLeft = countGreater(pRoot->p_left, x);
	int cntRight = countGreater(pRoot->p_right, x);

	return cnt + cntLeft + cntRight;
}

vector<int> LNR(NODE* pRoot)
{
	vector<int> InOrder;
	if (pRoot == nullptr) return InOrder;

	vector<int> left = LNR(pRoot->p_left);//Left
	InOrder.insert(InOrder.end(), left.begin(), left.end());

	InOrder.push_back(pRoot->key);//Node

	vector<int> right = LNR(pRoot->p_right);//Right
	InOrder.insert(InOrder.end(), right.begin(), right.end());

	return InOrder;
}
bool isBST(NODE* pRoot)
{
	if (pRoot == nullptr) return false;

	vector<int> temp = LNR(pRoot);
	for (int i = 1;i < (int)temp.size();i++)
	{
		if (temp[i] < temp[i - 1]) return false;//day giam
	}
	return true;
}

bool isFull(NODE* pRoot)
{
	if (pRoot == nullptr) return true;

	if (pRoot->p_left == nullptr && pRoot->p_right == nullptr) 
		return true;

	if (pRoot->p_left && pRoot->p_right)
		return isFull(pRoot->p_left) && isFull(pRoot->p_right);

	return false;
}
bool isFullBST(NODE* pRoot)
{
	return isBST(pRoot) && isFull(pRoot);
}
