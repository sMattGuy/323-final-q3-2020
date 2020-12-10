#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class LLNode{
	public:
	string data;
	LLNode* next;
	LLNode(string data){
		this->data = data;
		this->next = nullptr;
	}
	void printNode(ofstream& output){
		output<<data<<"->";
	}
};

class OrderedLL{
	public:
	LLNode* dummy;
	
	OrderedLL(){
		dummy = new LLNode("dummy");
	}
	//inlist tobeinserted
	bool checkAlphabet(string data1, string data2){
		if(data1[0] > 64 && data1[0] < 91){
			data1[0] = data1[0] + 32;
		}
		if(data2[0] > 64 && data2[0] < 91){
			data2[0] = data2[0] + 32;
		}
		
		if(data1[0] < data2[0])
			return false;
		else if(data1[0] == data2[0]){
			int read = 1;
			while(read != data1.size() || read != data2.size()){
				if(data1[read] < data2[read])
					return false;
				else
					return true;
				read++;
			}
			return false;
		}
		return true;
	}
	void insertNode(string data, ofstream& debug, LLNode** dummy){
		LLNode* insert = new LLNode(data);
		debug<<"Inserting data:"<<data<<endl;
		LLNode* head = *dummy;
		if(head->next == nullptr){
			head->next = insert;
		}
		else{
			while(head->next != nullptr){
				string info = head->next->data;
				if(this->checkAlphabet(head->next->data, data)){
					break;
				}
				head = head->next;
			}
			if(head->next == nullptr){
				head->next = insert;
			}
			else{
				insert->next = head->next;
				head->next = insert;
			}
		}
		debug<<"Printing list:\n";
		this->printList(debug, dummy);
	}
	void printList(ofstream& output, LLNode** dummy){
		LLNode* reader = *dummy;
		while(reader!=nullptr){
			reader->printNode(output);
			reader = reader->next;
		}
		output<<"NULL\n~~~~~~~~~~~~~\n";
	}
	string findMiddleNode(LLNode** dummy){
		LLNode* fast = *dummy;
		LLNode* slow = *dummy;
		while(fast->next != nullptr){
			fast = fast->next->next;
			slow = slow->next;
		}
		return slow->data;
	}
};

int main(int argc, char* argv[]){
	ifstream inFile(argv[1]);
	ofstream outFile(argv[2]);
	ofstream debug(argv[3]);
	OrderedLL list;
	string data = "";
	while(inFile >> data){
		list.insertNode(data, debug, &list.dummy);
	}
	outFile<<"Printing Linked List\n";
	list.printList(outFile, &list.dummy);
	string middle = list.findMiddleNode(&list.dummy);
	outFile<<"Printing Middle\n"<<middle<<endl;
}
