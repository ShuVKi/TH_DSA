#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
using namespace std;

struct NODE {
	int key;
	NODE* p_next;
};
struct Stack {
	NODE* top;
};

NODE* createNode(int data)
{
	NODE* newNode = new NODE;
	if (!newNode) return nullptr;

	newNode->key = data;
	newNode->p_next = nullptr;
	return newNode;
}

bool isEmpty(Stack *s)
{
	return s->top == nullptr;
}
Stack *initializeStack()
{
	Stack* newS = new Stack;
	if (!newS) return nullptr;

	newS->top = nullptr;
	return newS;
}
void push(Stack* s, int key) //addhead
{
	NODE* newNode = createNode(key);
	if (!newNode) return;

	newNode->p_next = s->top;
	s->top = newNode;
}
int pop(Stack* s) 
{
	if (isEmpty(s)) return -1; //Notes -1 is error

	NODE* temp = s->top;
	int value = temp->key;

	s->top = temp->p_next;
	delete temp;
	return value;
}
int size(Stack* s)
{
	NODE* temp = s->top;
	int cnt = 0;
	while (temp)
	{
		cnt++;
		temp = temp->p_next;
	}
	return cnt;
}


string display(Stack* s)
{
	string str;
	if (!s->top) 
	{
		return "EMPTY";
	}
	NODE* temp = s->top;
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
	while (getline(iFile,line)) cnt++;
	return cnt;
}
bool readFile(const char* filename, string* input,int n)
{
	ifstream iFile(filename);
	if (!iFile) {
		cout << "Khong mo duoc file input!" << endl;
		return false;
	}

	for (int i = 0;i < n;i++)
	{
		getline(iFile,input[i]);
	}
	return true;
}
bool writeFile(const char* filename, Stack *s, string* output,int n)
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
	Stack* s = nullptr;
	int n = readline("input.txt");
	string* input=new string[n];
	string* output = new string[n];
	
	//readfile input
	if (!readFile("input.txt", input,n)) return 0;
	
	//process input
	for (int i = 0;i < n;i++)
	{
		//tach chuoi
		string command;
		stringstream ss(input[i]); //truyen chuoi dau vao
		ss >> command; //doc chuoi theo space

		if (command == "init") 
		{
			s = initializeStack();
			output[i] = display(s);
		}
		else if (command == "push") 
		{
			while (ss >> command)
			{
				int data = stoi(command);
				push(s, data);
			}
			output[i] = display(s);
		}
		else if (command == "pop")
		{
			pop(s);
			output[i] = display(s);
		}
		else output[i] = "Lenh khong hop le!";
	}

	//writefile output
	if (!writeFile("output.txt", s, output, n)) return 0;

	delete[] input, output;
	return 0;
}