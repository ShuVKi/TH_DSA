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

vector<int> NLR(NODE* pRoot)
{
	vector<int> listPreOrder;
	if (pRoot == nullptr) return listPreOrder;

	listPreOrder.push_back(pRoot->key);//Node

	vector<int> left = NLR(pRoot->p_left);//Left
	listPreOrder.insert(listPreOrder.end(), left.begin(), left.end());

	vector<int> right = NLR(pRoot->p_right);//Right
	listPreOrder.insert(listPreOrder.end(), right.begin(), right.end());

	return listPreOrder;
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

vector<int> LRN(NODE* pRoot)
{
	vector<int> PostOrder;
	if (pRoot == nullptr) return PostOrder;

	vector<int> left = LRN(pRoot->p_left);//Left
	PostOrder.insert(PostOrder.end(), left.begin(), left.end());

	vector<int> right = LRN(pRoot->p_right);//Right
	PostOrder.insert(PostOrder.end(), right.begin(), right.end());

	PostOrder.push_back(pRoot->key);//Node

	return PostOrder;
}

vector<vector<int>> LevelOrder(NODE* pRoot)
{
	vector<vector<int>> LvOrder;
	if (pRoot == nullptr) return LvOrder;

	queue<NODE*> NodeAtCurrLv;
	NodeAtCurrLv.push(pRoot);
	while (!NodeAtCurrLv.empty())
	{
		vector<int> currlevel;
		if (LvOrder.empty())//add Root Lv0
			currlevel.push_back(NodeAtCurrLv.front()->key);
		else
		{
			int size = (int)NodeAtCurrLv.size();
			for (int i = 0;i < size;i++)
			{
				NODE* temp = NodeAtCurrLv.front();

				if (temp->p_left)
				{
					NodeAtCurrLv.push(temp->p_left);//add node child left into queue
					currlevel.push_back(temp->p_left->key);//add key left
				}

				if (temp->p_right)
				{
					NodeAtCurrLv.push(temp->p_right);//add node child right into queue
					currlevel.push_back(temp->p_right->key);//add key right
				}

				NodeAtCurrLv.pop();//remove front from queue
			}
		}
		if (!currlevel.empty())	LvOrder.push_back(currlevel);//push currLevel into vector 2D
	}
	return LvOrder;
}

int countNode(NODE* pRoot)
{
	if (pRoot == nullptr) return 0;
	return 1 + countNode(pRoot->p_left) + countNode(pRoot->p_right);
}

int sumNode(NODE* pRoot)
{
	if (pRoot == nullptr) return 0;

	return pRoot->key + sumNode(pRoot->p_left) + sumNode(pRoot->p_right);
}

int getHeight(NODE* pRoot) {
	if (pRoot == nullptr) return -1;
	return 1 + max(getHeight(pRoot->p_left), getHeight(pRoot->p_right));
}
int heightNode(NODE* pRoot, int value)
{
	if (pRoot == nullptr) return -1;
	if (pRoot->key == value)
	{
		return getHeight(pRoot);
	}
	//find Left Child
	int left = heightNode(pRoot->p_left, value);
	if (left != -1) return left;
	//find Right Child
	return heightNode(pRoot->p_right, value);
}

int Level(NODE* pRoot, NODE* p)
{
	if (pRoot == nullptr || p == nullptr) return -1;

	vector<vector<int>> temp = LevelOrder(pRoot);
	for (int i = 0;i < (int)temp.size();i++)
	{
		for (int j = 0;j < (int)temp[i].size();j++)
		{
			if (temp[i][j] == p->key) return i;
		}
	}
	return -1;
}

int countLeaf(NODE* pRoot)
{
	if (pRoot == nullptr) return 0;

	int cnt = 0;
	if (pRoot->p_left == nullptr && pRoot->p_right == nullptr)
		cnt++;
	if (pRoot->p_left != nullptr) 
		cnt+=countLeaf(pRoot->p_left);
	if (pRoot->p_right != nullptr) 
		cnt+=countLeaf(pRoot->p_right);
	return cnt;
}
