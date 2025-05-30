#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

vector<vector<int>> convertMatrixToList(const string& filename)
{
	ifstream iFile(filename);
	if (!iFile)
	{
		cout << "Can not open file " << filename << endl;
		return vector<vector<int>>();
	}

	int n;
	iFile >> n;//type of matrix nxn

	vector<vector<int>> adjMatrix(n,vector<int>(n));
	vector<vector<int>> adjList(n);

	for (int i = 0;i < n;i++)//read adjmatrix
	{
		for (int j = 0;j < n;j++)
		{
			iFile >> adjMatrix[i][j];
		}
	}
	for (int i = 0;i < n;i++)//convert to adjList
	{
		for (int j = 0;j < n;j++)
		{
			if (adjMatrix[i][j] == 1)
				adjList[i].push_back(j);
		}
	}

	return adjList;
}

vector<vector<int>> convertListToMatrix(const string& filename)
{
	ifstream iFile(filename);
	if (!iFile)
	{
		cout << "Can not open file " << filename << endl;
		return vector<vector<int>>();
	}

	int n;
	iFile >> n;//type of matrix nxn
	vector<vector<int>> adjMatrix(n, vector<int>(n, 0));
	for (int i = 0;i < n;i++)
	{
		int size;
		iFile >> size;//size of each row
		for (int j = 0;j < size;j++)
		{
			int adjvertices;
			iFile >> adjvertices;
			adjMatrix[i][adjvertices] = 1;
		}
	}

	return adjMatrix;
}

bool isDirected(const vector<vector<int>>& adjMatrix)
{
	int n = adjMatrix.size();
	for (int i = 0;i < n;i++)
	{
		for (int j = 0;j < n;j++)
		{
			if (adjMatrix[i][j] != adjMatrix[j][i])//->Directed 
				return true;
		}
	}
	return false;//->Undirected
}

int countVertices(const vector<vector<int>>& adjMatrix)
{
	return (int)adjMatrix.size();
}

int countEdges(const vector<vector<int>>& adjMatrix)
{
	int cnt = 0;
	int n = adjMatrix.size();
	for (int i = 0;i < n;i++)
	{
		for (int j = 0;j < n;j++)
		{
			if (adjMatrix[i][j] == 1)
			{
				cnt++;
			}
		}
	}
	if (!isDirected(adjMatrix)) cnt /= 2;

	return cnt;
}

vector<int> getIsolatedVertices(const vector<vector<int>>& adjMatrix)
{
	int n = adjMatrix.size();
	vector<int> ListIsolateVer;
	for (int i = 0;i < n;i++)
	{
		bool isIsolate = true;
		for (int j = 0;j < n;j++)
		{
			if (adjMatrix[i][j] == 1 || adjMatrix[j][i] == 1)
			{
				isIsolate = false;
				break;
			}
		}
		if (isIsolate) ListIsolateVer.push_back(i);
	}

	return ListIsolateVer;
}

bool isCompleteGraph(const vector<vector<int>>& adjMatrix)
{
	if (isDirected(adjMatrix)) return false;

	int n = adjMatrix.size();
	for (int i = 0;i < n;i++)
	{
		for (int j = 0;j < n;j++)
		{
			if (i != j && adjMatrix[i][j] == 0)
				return false;
		}
	}
	return true;
}

bool isBipartite(const std::vector<std::vector<int>>& adjMatrix)
{
	if (isDirected(adjMatrix)) return false;

	int n = adjMatrix.size();
	vector<int> color(n, -1);
	for (int ver = 0;ver < n;ver++)
	{
		if (color[ver] == -1)
			color[ver] = 0;
		queue<int> q;
		q.push(ver);

		while (!q.empty())
		{
			int i = q.front();
			q.pop();

			for (int j = 0;j < n;j++)
			{
				if (adjMatrix[i][j] == 1)//adjMatrix[i][j] is adjVertices
				{
					if (color[j] == -1)
					{
						color[j] = 1 - color[i];//different color
						q.push(j); //add into queue so that continue while
					}
					else if (color[i] == color[j]) return false;//has connect in same group-> isn't a Bipartile
				}
			}
		}
	}

	return true;
}

bool isCompleteBipartite(const vector<vector<int>>& adjMatrix)
{
	if (isDirected(adjMatrix)) return false;

	//make color and check Bipartile
	int n = adjMatrix.size();
	vector<int> color(n, -1);
	for (int ver = 0;ver < n;ver++)
	{
		if (color[ver] == -1)
			color[ver] = 0;
		queue<int> q;
		q.push(ver);

		while (!q.empty())
		{
			int i = q.front();
			q.pop();

			for (int j = 0;j < n;j++)
			{
				if (adjMatrix[i][j] == 1)//adjMatrix[i][j] is adjVertices
				{
					if (color[j] == -1)
					{
						color[j] = 1 - color[i];//different color
						q.push(j); //add into queue so that continue while
					}
					else if (color[i] == color[j]) return false;//has connect in same group-> isn't a Bipartile
				}
			}
		}
	}

	// check Complete
	for (int i = 0;i < n;i++)
	{
		for (int j = 0;j < n;j++)
		{
			if (i != j)
			{
				if (color[i] == color[j] && adjMatrix[i][j] == 1) return false;//has connect in same group
				if (color[i] != color[j] && adjMatrix[i][j] != 1) return false;//hasn't connect in different group
			}
		}
	}

	return true;
}

vector<vector<int>> convertToUndirectedGraph(const vector<vector<int>>& adjMatrix)
{
	int n = (int)adjMatrix.size();
	vector<vector<int>> Undirected(n, vector<int>(n, 0));

	for (int i = 0;i < n;i++)
	{
		for (int j = 0;j < n;j++)
		{
			if (adjMatrix[i][j] == 1 || adjMatrix[j][i] == 1)
			{
				Undirected[i][j] = Undirected[j][i] = 1;		
			}
		}
	}
	return Undirected;
}

vector<vector<int>> getComplementGraph(const vector<vector<int>>& adjMatrix)
{
	if (isDirected(adjMatrix)) return {};

	int n = (int)adjMatrix.size();
	vector<vector<int>> ComplementG(n, vector<int>(n, 0));
	for (int i = 0;i < n;i++)
	{
		for (int j = 0;j < n;j++)
		{
			if (i!=j && adjMatrix[i][j] == 0)
			{
				ComplementG[i][j] = ComplementG[j][i] = 1;
			}
		}
	}

	return ComplementG;
}

bool HasEulerCycle(vector<vector<int>> adjMatrix)
{
	int n = adjMatrix.size();
	if (isDirected(adjMatrix))//Directed Graph
	{
		//Check inDeg = outDeg
		vector<int> inDeg(n, 0), outDeg(n, 0);
		for (int u = 0; u < n; ++u) 
		{
			for (int v = 0; v < n; ++v) 
			{
				if (adjMatrix[u][v] > 0)//Weight/unWeight
				{
					outDeg[u]++;
					inDeg[v]++;
				}
			}
		}
		for (int i = 0;i < n;i++)
		{
			if (inDeg[i] != outDeg[i]) return false;
		}
		return true;
	}
	else//unDirected Graph
	{
		//Check Edge has even degree
		int n = adjMatrix.size();
		for (int i = 0;i < n;i++)
		{
			int degree = 0;
			for (int j = 0;j < n;j++)
			{
				if (adjMatrix[i][j] > 0) //Weight/unWeight
					degree++;
			}
			if (degree % 2 != 0) return false;//odd degree
		}
		return true;
	}
}
vector<int> findEulerCycle(const vector<vector<int>>& adjMatrix)
{
	if (!HasEulerCycle(adjMatrix)) return {};

	int n = adjMatrix.size();
	vector<vector<int>> tempG = adjMatrix;//copy Matrix
	vector<int> result;
	stack<int> stk;//save path

	//find firt vertice has edge
	int start = -1;
	for (int i = 0;i < n && start == -1;i++)
	{
		for (int j = 0;j < n;j++)
		{
			if (tempG[i][j] == 1)
			{
				start = i;
				break;
			}
		}
	}
	if (start == -1) return {};//hasn't edge
	stk.push(start);//first ver

	//Hierholzer’s Algorithm.
	while (!stk.empty())
	{
		int i = stk.top();
		bool hasEdge = false;
		for (int j = 0;j < n;j++)
		{
			if (tempG[i][j] == 1)
			{
				hasEdge = true;	
				tempG[i][j] = 0;//delete edge
				if (!isDirected(adjMatrix)) tempG[j][i] = 0;//if unDirected delete both 
				stk.push(j);// add into stack
				break;
			}
		}
		if (!hasEdge) {
			result.push_back(i);
			stk.pop();
		}
	}

	//check if have edges after alg
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			if (tempG[i][j])
				return {};
	reverse(result.begin(), result.end());
	return result;
}

void dfs(int start, const vector<vector<int>>& adjMatrix, vector<bool>& visited, vector<vector<int>>& SpanTree)
{
	visited[start] = true;
	int n = adjMatrix.size();
	for (int j = 0;j < n;j++)
	{
		if (adjMatrix[start][j] == 1 && !visited[j])
		{
			SpanTree[start][j] = SpanTree[j][start] = 1;//add into SpanTree
			dfs(j, adjMatrix, visited, SpanTree);
		}
	}
}
vector<vector<int>> dfsSpanningTree(const vector<vector<int>>& adjMatrix, int start)
{
	if (isDirected(adjMatrix)) return {};

	int n = adjMatrix.size();
	vector<vector<int>> SpanTree(n, vector<int>(n, 0));
	vector<bool> visited(n, false);

	dfs(start, adjMatrix, visited, SpanTree);

	return SpanTree;
}

vector<vector<int>> bfsSpanningTree(const vector<vector<int>>& adjMatrix, int start)
{
	if (isDirected(adjMatrix)) return {};

	int n = adjMatrix.size();
	vector<vector<int>> SpanTree(n, vector<int>(n, 0));
	vector<bool> visited(n, false);
	queue<int> q;

	q.push(start);
	visited[start] = true;

	while (!q.empty())
	{
		int i = q.front();
		q.pop();

		for (int j = 0;j < n;j++)
		{
			if (adjMatrix[i][j] == 1 && !visited[j])
			{
				q.push(j);
				visited[j] = true;
				SpanTree[i][j] = SpanTree[j][i] = 1;//add into SpanTree
			}
		}
	}
	
	return SpanTree;
}

bool isConnected(int u, int v, const vector<vector<int>>& adjMatrix)
{
	int n = adjMatrix.size();
	vector<bool> visited(n, false);
	queue<int> q;

	q.push(u);
	visited[u] = true;

	while (!q.empty())
	{
		int i = q.front();
		q.pop();

		if (i == v) return true;//has Conected

		for (int j = 0;j < n;j++)
		{
			if (adjMatrix[i][j] == 1 && !visited[j])
			{
				q.push(j);
				visited[j] = true;
			}
		}
	}

	return false;
}

vector<int> dijkstra(int start, int end, const vector<vector<int>>& adjMatrix)
{
	int n = adjMatrix.size();
	vector<bool> visited(n, false);
	vector<int> parent(n, -1);
	vector<int> dist(n, INT_MAX);

	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;//pair{distance(vertex),vertex}
	dist[start] = 0;
	pq.push({ dist[start], start });
	while (!pq.empty())
	{
		int i = pq.top().second;
		pq.pop();
		
		if (visited[i]) continue;
		visited[i] = true;

		for (int j = 0;j < n;j++)
		{
			if (adjMatrix[i][j] > 0)//have weighted
			{
				int weight = adjMatrix[i][j];
				if (dist[i] + weight < dist[j])
				{
					dist[j] = dist[i] + weight;
					parent[j] = i;
					pq.push({ dist[j],j });
				}
			}
		}
	}

	if (dist[end] == INT_MAX) return {};//hasn't path

	vector<int> path;
	for (int i = end;i != -1;i = parent[i])
		path.push_back(i);
	reverse(path.begin(), path.end());

	return path;
}

vector<int> bellmanFord(int start, int end, const vector<vector<int>>& adjMatrix)
{
	int n = adjMatrix.size();
	vector<int> parent(n, -1);
	vector<int> dist(n, INT_MAX);

	dist[start] = 0;
	for (int k = 0;k < n - 1;k++)//n-1 times
	{
		for (int i = 0;i < n;i++)
		{
			for (int j = 0;j < n;j++)
			{
				if (adjMatrix[i][j] != 0 && dist[i] != INT_MAX)//ensure only begin update at adjMatrix[start][j]
				{
					int weight = adjMatrix[i][j];
					if (dist[i] + weight < dist[j])
					{
						dist[j] = dist[i] + weight;
						parent[j] = i;
					}
				}
			}
		}
	}

	//check negative cycle
	for (int i = 0;i < n;i++)
	{
		for (int j = 0;j < n;j++)
		{
			if (adjMatrix[i][j] != 0 && dist[i] != INT_MAX)
			{
				int weight = adjMatrix[i][j];
				if (weight + dist[i] < dist[j]) return {};
			}
		}
	}

	vector<int> path;
	for (int i = end;i != -1;i = parent[i])
		path.push_back(i);
	reverse(path.begin(), path.end());

	return path;
}
