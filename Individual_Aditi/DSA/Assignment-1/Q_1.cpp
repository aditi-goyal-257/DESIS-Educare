#include <iostream>

using namespace std;

class Node{
    public:
    int val;
    Node*next;
    Node(){
        this->val = -1;
        this->next = NULL;
    }
    Node(int val){
        this->val = val;
        this->next = NULL;
    }
};

class LinkedList{

    Node*head;
    public:
    LinkedList(){
        head = NULL;
    }

    void insert_at_start(int num){
        Node*curr = new Node(num);
        curr->next = this->head;
        this->head = curr;
    }

    void remove_from_start(){

        if(this->head != NULL){
            this->head = (this->head)->next;
        }

    }

    void insert_at_end(int num){

        Node*curr = this->head;
        if(curr != NULL){

            while(curr->next!=NULL){
                curr = curr->next;
            }
            Node*node = new Node(num);
            curr->next = node;
        }
        else{
            Node*node = new Node(num);
            this->head = node;
        }

    }

    void remove_from_end(){

        Node*curr = this->head;
        Node*temp;

        if(curr != NULL){
            if(curr->next == NULL){
                this->head = NULL;
                return;
            }
            while(curr->next!=NULL){
                temp = curr;
                curr = curr->next;
            }
            temp->next = NULL;

        }



    }

    int front(){

        Node*curr = this->head;
        if(curr == NULL){
            return -1;
        }
        return curr->val;

    }

    int last(){

        Node*curr = this->head;
        
        int ans = -1;
        while(curr!=NULL){
            ans = curr->val;
            curr = curr->next;
        }

        return ans;

    }

    void traverse(){

        Node*curr = this->head;
        while(curr!=NULL){
            cout<<curr->val<<" ";
            curr = curr->next;
        }
        cout<<"\n";

    }


};

class Stack{

    public:
    LinkedList list;
    Stack(){}
    void push(int num){
        this->list.insert_at_start(num);
    }
    void pop(){
        this->list.remove_from_start();
    }
    int top(){
        return this->list.front();
    }

};

class Queue{
    public:
    LinkedList list;
    Queue(){}
    void push(int num){
        this->list.insert_at_end(num);
    }
    void pop(){
        this->list.remove_from_start();
    }
    int front(){
        return this->list.front();
    }
};

int main(){
    Stack s;
    s.push(1);
    cout<<s.top()<<"\n";
    s.push(2);
    cout<<s.top()<<"\n";
    s.push(3);
    cout<<s.top()<<"\n";
    s.pop();
    cout<<s.top()<<"\n";
    s.pop();
    cout<<s.top()<<"\n";
}