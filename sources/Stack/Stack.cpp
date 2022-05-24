#include "Stack.hpp"
#include "../Heap/heap_funcs.hpp"
#include <string>
#include <iostream>
#include <fcntl.h>

using namespace ex4;
using namespace std;


ex4::str_Node::str_Node()
{
    this->next = nullptr;
}

ex4::str_Node::str_Node(const string & str)
{
    this->data = str;
    this->next = nullptr;
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
    this -> next = new str_Node(next);
}
void ex4::str_Node::setNext(str_Node * next)
{
    this -> next = next;
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
    this -> fd = -1;
}
ex4::Stack::~Stack()
{
    str_Node * current = this-> get_head();
    str_Node * prev = nullptr;
    while(current != nullptr) // iterate through the linked list and destroy each node untill we reach the end.
    {
        prev = current;
        current = current->getNext();
        _free(prev);
    }

}   
string ex4::Stack::POP()
{
    lock_block_in_mappedmem((void *)this);
    string ret = POP_SRC();
    unlock_block_in_mappedmem((void *)this);
    return ret;
}

string ex4::Stack::TOP()
{
    lock_block_in_mappedmem((void *)this);
    string ret = TOP_SRC();
    unlock_block_in_mappedmem((void *)this);
    return ret;
}
void ex4::Stack::PUSH(string inp)
{
    lock_block_in_mappedmem((void *)this);
    PUSH_SRC(inp);
    unlock_block_in_mappedmem((void *)this);
}


string ex4::Stack::POP_SRC()
{
    if(this->head == nullptr)
    {
        perror("ERROR: Cannot pop from an empty stack.");
        exit(1);
    }
    str_Node * h = this->head;
    this->head = h->getNext();
    string str = h->getData();
    _free(h);
    this->size -=1;
    return str;
}
void ex4::Stack::PUSH_SRC(string inp)
{
    if( inp.size() > 1024)
    {
        throw(invalid_argument("ERROR: string is larger than 1024 bytes."));
    }
    str_Node * node = (str_Node *) _malloc(sizeof(str_Node));
    node-> setData(inp);
    node-> setNext(this->head);
    printf("%p\n", this->head);
    head = node;
    this->size+=1;
}

string ex4::Stack::TOP_SRC()
{
    string temp = this -> get_head()->getData();
    return temp;
}

void ex4::Stack::set_fd(int fd)
{
    this->fd = fd;
}




