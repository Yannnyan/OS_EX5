#include <string>
#include <iostream>
#include <stdio.h>
#include "Stack.hpp"
#include <mutex>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include<sys/mman.h>

using namespace ex4;
using namespace std;

pthread_mutex_t  lock1 = PTHREAD_MUTEX_INITIALIZER;

ex4::str_Node::str_Node()
{
    this->next = NULL;
}

ex4::str_Node::str_Node(const string & str)
{
    this->data = str;
    this->next = NULL;
}
str_Node * ex4::str_Node::getNext()
{
    // pthread_mutex_lock(&lock1);
    str_Node * ret = this->getNext1();
    // pthread_mutex_unlock(&lock1);
    return ret;
}
// set the next node.
void ex4::str_Node::setNext(string & next)
{
    if (this -> next != NULL)
    {
        
    }
    else
    {
        this -> next = new str_Node(next);
    }
}
void ex4::str_Node::setNext(str_Node * next)
{
    if (this -> next != NULL)
    {
        
    }
    else
    {
        this -> next = next;
    } 
}
string & ex4::str_Node::getData()
{
    return this->data;
}
void ex4::str_Node::setData(string data)
{
    this -> data = data;
}

ex4::Stack::Stack()
{
    this -> head = nullptr;
    this -> size = 0;
    if(ftruncate(this->fd, this-> page_size * 2) == -1)
    {
        perror("ERROR: trucate failed.");
        exit(1);
    }
}
ex4::Stack::~Stack()
{
    str_Node * current = this-> get_head();
    str_Node * prev = nullptr;
    while(current != nullptr) // iterate through the linked list and destroy each node untill we reach the end.
    {
        prev = current;
        current = current->getNext();
        free(prev);
    }

}   

string ex4::Stack::POP()
{
    if(this->head == nullptr)
    {
        perror("ERROR: Cannot pop from an empty stack.");
        exit(1);
    }
    str_Node * h = this->head;
    this->head = h->getNext();
    string str = h->getData();
    free(h);
    this->size -=1;
    return str;
}
void ex4::Stack::PUSH(string inp)
{
    if( inp.size() > 1024)
    {
        throw(invalid_argument("ERROR: string is larger than 1024 bytes."));
    }
    str_Node * node = (str_Node *) malloc(sizeof(str_Node));
    node-> setData(inp);
    node-> setNext(this->head);
    head = node;
    this->size+=1;
}

string ex4::Stack::TOP()
{
    string temp = this -> get_head()->getData();
    return temp;
}





