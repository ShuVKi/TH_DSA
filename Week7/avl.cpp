#include <iostream>
#include <vector>
using namespace std;
struct NODE {
	int key;
	NODE* p_left;
	NODE* p_right;
	int height;
};

NODE* createNode(int data)
{
	NODE* newNode = new NODE;
	if (!newNode) return nullptr;
	newNode->key = data;
	newNode->p_left = nullptr;
	newNode->p_right = nullptr;
	newNode->height = 0;
	return newNode;
}

int getHeight(NODE* node)
{
	if (node == nullptr) return -1;// -1 cho NULL
	return node->height;
}
void updateHeight(NODE* node) 
{
	if (node != NULL)
		node->height = max(getHeight(node->p_left), getHeight(node->p_right)) + 1;
}
void rotateRight(NODE*& pRoot)
{
	NODE* leftChild = pRoot->p_left;
	pRoot->p_left = leftChild->p_right;
	leftChild->p_right = pRoot;
	pRoot = leftChild;

	updateHeight(pRoot->p_right);
	updateHeight(pRoot);
}
void rotateLeft(NODE*& pRoot)
{
	NODE* rightChild = pRoot->p_right;
	pRoot->p_right = rightChild->p_left;
	rightChild->p_left = pRoot;
	pRoot = rightChild;

	updateHeight(pRoot->p_left);
	updateHeight(pRoot);
}
void leftBalance(NODE*& pRoot)
{
	NODE* leftChild = pRoot->p_left;
	int balFactorLeftChild = getHeight(leftChild->p_left) - getHeight(leftChild->p_right);
	if (balFactorLeftChild == 1) //imbalance Left-Left
		rotateRight(pRoot);
	else //imbalancce Left-Right
	{
		rotateLeft(leftChild);
		rotateRight(pRoot);
	}
}
void rightBalance(NODE*& pRoot)
{
	NODE* rightChild = pRoot->p_right;
	int balFactorRightChild = getHeight(rightChild->p_left) - getHeight(rightChild->p_right);
	if (balFactorRightChild == -1) //imbalance Right-Right
		rotateLeft(pRoot);
	else //imbalancce Right-Left
	{
		rotateRight(rightChild);
		rotateLeft(pRoot);
	}
}

void Insert(NODE*& pRoot, int x)
{
	if (pRoot == nullptr) {
		pRoot = createNode(x);
		return;
	}
	if (x < pRoot->key)
	{
		if (pRoot->p_left == nullptr)
			pRoot->p_left = createNode(x);
		else
			Insert(pRoot->p_left, x);
	}
	else if (x > pRoot->key)
	{
		if (pRoot->p_right == nullptr)
			pRoot->p_right = createNode(x);
		else
			Insert(pRoot->p_right, x);
	}
	else return; //next if value x existed

	// Recursive updateHeight after Insert
	updateHeight(pRoot);

	// Recursive Check balance-> Fix exactly the LOWEST violation
	int balFactorRoot = getHeight(pRoot->p_left) - getHeight(pRoot->p_right);
	if (balFactorRoot == -2)
		rightBalance(pRoot);
	else if (balFactorRoot == 2)
		leftBalance(pRoot);
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

	// Recursive updateHeight after Insert
	if (pRoot == nullptr) return;
	updateHeight(pRoot);

	// Recursive Check balance-> Fix exactly the LOWEST violation
	int balFactorRoot = getHeight(pRoot->p_left) - getHeight(pRoot->p_right);
	if (balFactorRoot == -2)
		rightBalance(pRoot);
	else if (balFactorRoot == 2)
		leftBalance(pRoot);
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
	if (pRoot == nullptr) return true;

	vector<int> temp = LNR(pRoot);
	for (int i = 1;i < (int)temp.size();i++)
	{
		if (temp[i] <= temp[i - 1]) return false;//day giam
	}
	return true;
}
bool isBalanced(NODE* pRoot)
{
	if (pRoot == nullptr) return true;

	int balFactor = getHeight(pRoot->p_left) - getHeight(pRoot->p_right);
	if (balFactor < -1 || balFactor > 1)
		return false;

	return isBalanced(pRoot->p_left) && isBalanced(pRoot->p_right);
}
bool isAVL(NODE* pRoot)
{
	if (pRoot == nullptr) return true;

	return isBST(pRoot) && isBalanced(pRoot);
}