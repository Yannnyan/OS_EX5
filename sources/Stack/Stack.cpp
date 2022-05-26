#include "Stack.hpp"
#include "../Heap/heap_funcs.hpp"
#include <iostream>
#include <fcntl.h>
#include <string.h>

using namespace ex4;
using namespace std;


ex4::str_Node::str_Node()
{
    this->next = nullptr;
}

ex4::str_Node::str_Node(char * str)
{
    char c = str[0];
    int i = 0;
    for(i=0; c != '\0' &&  i < 1023; i++)
    {
        c = str[i];
        this->data[i] = str[i];
    }
    if(c != '\0')
    {
        perror("ERROR: char * size is too long! ");
        return;
    }
    this->data[i] = '\0';
    this->next = nullptr;
}
str_Node * ex4::str_Node::getNext()
{
    // pthread_mutex_lock(&lock1);
    str_Node * ret = this->next;
    // pthread_mutex_unlock(&lock1);
    return ret;
}
// set the next node.
void ex4::str_Node::setNext(char * next)
{
    this -> next = (str_Node *)_malloc(sizeof(str_Node));
    strncpy(this->next->data, next, sizeof(this->next));
}
void ex4::str_Node::setNext(str_Node * next)
{
    this -> next = next;
}
char *  ex4::str_Node::getData()
{
    return this->data;
}
void ex4::str_Node::setData(char * data)
{
    char c = data[0];
    int i = 0;
    for(i=0; c != '\0' &&  i < 1023; i++)
    {
        c = data[i];
        this->data[i] = data[i];
    }
    if(c != '\0')
    {
        perror("ERROR: char * size is too long! ");
    }
    puts("ended setData.");
    this->data[i] = '\0';
}
void ex4::Stack::add_node(char *  data)
{
    str_Node * to_add = (str_Node *) _malloc(sizeof(str_Node));
    to_add->setData(data);
    to_add->setNext((str_Node *)nullptr);
    str_Node * current = this->head;
    puts("loop\n");
    while(current->getNext() != nullptr)
    {
        puts("loop\n");
        current = current->getNext();
    }
    puts("loop\n");
    current->setNext(to_add);
    
}
ex4::Stack::Stack()
{
    this -> head = (str_Node *)_malloc(sizeof(str_Node));
    this -> head->setNext((str_Node *)nullptr);
    this ->head->setData((char *)"`\0");
    this -> size = 0;
    this -> fd = -1;
}
void ex4::Stack::_Stack()
{
    this -> head = (str_Node *)_malloc(sizeof(str_Node));
    this -> head->setNext((str_Node *)nullptr);
    this ->head->setData((char *)"`\0");
    this -> size = 0;
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
char * ex4::Stack::POP()
{
    lock_block_in_mappedmem((void *)this);
    char * ret = POP_SRC();
    unlock_block_in_mappedmem((void *)this);
    return ret;
}

char * ex4::Stack::TOP()
{
    lock_block_in_mappedmem((void *)this);
    char * ret = TOP_SRC();
    unlock_block_in_mappedmem((void *)this);
    return ret;
}
void ex4::Stack::PUSH(char * inp)
{
    lock_block_in_mappedmem((void *)this);
    PUSH_SRC(inp);
    unlock_block_in_mappedmem((void *)this);
}


char * ex4::Stack::POP_SRC()
{
    if(this->head == nullptr)
    {
        perror("ERROR: Cannot pop from an empty stack.");
        return (char *)"";
    }
    str_Node * current = this->head;
    str_Node * prev = this->head;
    while(current->getNext() != nullptr)
    {
        prev = current;
        current = current->getNext();
    }
    if(!strcmp(current->getData(), "`"))
    {
        // stack only contains the head and the head can't be extracted.
        printf("head\n");
        return (char *)"";
    }
    prev->setNext((str_Node *)nullptr);
    char * str = current->getData();
    // printf("%ld\n", strlen(str));
    char * ret = (char *) malloc(strlen(str)+1);
    strncpy(ret, str, strlen(str) + 1);
    // puts(ret);
    _free(current);
    this->size -=1;
    return ret;
}
void ex4::Stack::PUSH_SRC(char * inp)
{
    if( strlen(inp) > 1024)
    {
        perror("ERROR: char * is larger than 1024 bytes.");
        return;
    }
    add_node(inp);
    // printf("%p\n", this->head);
    this->size+=1;
}

char * ex4::Stack::TOP_SRC()
{
    str_Node * current = this -> get_head();
    while(current->getNext() != nullptr)
    {
        current= current->getNext();
    }
    return current->getData();
}

void ex4::Stack::set_fd(int fd)
{
    this->fd = fd;
}




