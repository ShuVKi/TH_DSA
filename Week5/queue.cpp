#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
using namespace std;

struct NODE {
	int key;
	NODE* p_next;
};
struct Queue {
	NODE* head;
	NODE* tail;
};

NODE* createNode(int data)
{
	NODE* newNode = new NODE;
	if (!newNode) return nullptr;

	newNode->key = data;
	newNode->p_next = nullptr;
	return newNode;
}

bool isEmpty(Queue* q)
{
	return q->head == nullptr;
}
Queue* initializeQueue()
{
	Queue* newQ = new Queue;
	if (!newQ) return nullptr;

	newQ->head = nullptr;
	newQ->tail = nullptr;
}
void enqueue(Queue* q, int key)
{
	NODE* newNode = createNode(key);
	if (!newNode) return;

	if (!q->head)
		q->head = q->tail = newNode;
	else
	{
		if (q->tail)
		{
			q->tail->p_next = newNode;
			q->tail = newNode;
		}
	}
}
int dequeue(Queue* q)
{
	if (isEmpty(q)) return -1; //Notes -1 is error

	NODE* temp = q->head;
	int value = q->head->key;

	q->head = temp->p_next;
	delete temp;
	return value;
}
int size(Queue *q)
{
	int cnt = 0;
	NODE* temp = q->head;
	while (temp)
	{
		cnt++;
		temp = temp->p_next;
	}
	return cnt;
}


string display(Queue* q)
{
	string str;
	if (isEmpty(q)) return "EMPTY";

	NODE* temp = q->head;
	while (temp)
	{
		string data = to_string(temp->key);
		str += data + " ";
		temp = temp->p_next;
	}
	return str;
}
int readline(const char* filename)
{
	ifstream iFile(filename);
	if (!iFile) return 0;

	int cnt = 0;
	string line;
	while (getline(iFile, line)) cnt++;
	return cnt;
}
bool readFile(const char* filename, string* input, int n)
{
	ifstream iFile(filename);
	if (!iFile) {
		cout << "Khong mo duoc file input!" << endl;
		return false;
	}

	for (int i = 0;i < n;i++)
	{
		getline(iFile, input[i]);
	}
	return true;
}
bool writeFile(const char* filename,string* output, int n)
{
	ofstream oFile(filename);
	if (!oFile) {
		cout << "Khong mo duoc file output!" << endl;
		return false;
	}

	for (int i = 0;i < n;i++)
	{
		oFile << output[i] << endl;
	}
	cout << "Write file success!" << endl;
	return true;
}

int main()
{
	Queue* q = nullptr;
	int n = readline("input.txt");
	string* input = new string[n];
	string* output = new string[n];

	//readfile input
	if (!readFile("input.txt", input, n)) return 0;
	
	//process input
	for (int i = 0;i < n;i++)
	{
		//tach chuoi
		string command;
		stringstream ss(input[i]); //truyen chuoi dau vao
		ss >> command; //doc chuoi theo space

		if (command == "init")
		{
			q = initializeQueue();
			output[i] = display(q);
		}
		else if (command == "enqueue")
		{
			while (ss >> command)
			{
				int data = stoi(command);
				enqueue(q, data);
			}
			output[i] = display(q);
		}
		else if (command == "dequeue")
		{
			dequeue(q);
			output[i] = display(q);
		}
		else output[i] = "Lenh khong hop le!";
	}

	//writefile output
	if (!writeFile("output.txt", output, n)) return 0;

	delete[] input, output;
	return 0;
}