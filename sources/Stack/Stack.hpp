#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>

using namespace std;


namespace ex4
{
    // This class is a node inside a linked list of char *s
    class str_Node
    {
        private:
            char data[1024];
            str_Node * next;
            // functions
            str_Node * getNext1()
            {
                return this->next;
            }
            
            
        public:
            // construct an empty node and set the next to null
            str_Node();
            
            // construct a node and set its data to str
            // set next to null.
            str_Node(char * str);
            
            // get the next node.
            str_Node * getNext(); 
            // set the next node.
            void setNext(char * next); 
            
            void setNext(str_Node * next);
            // get the data of the node
            char *  getData();
            // set the data of the node
            void setData(char * ata);
    };
    class Stack
    {
        private:
            str_Node * head;
            size_t size;
            int fd;

            void PUSH_SRC(char * ext); 
            char * POP_SRC();
            char * TOP_SRC();

        public:
            // constructor initializes stack size to 10
            Stack();
            // if using _malloc uuse this as a constructor.
            void _Stack();
            // destructor, destroys the array
            ~Stack();
            // push text into the stack
            void PUSH(char * ext); 
            // pop text from the stack
            char * POP(); 
            // return the first char * rom the stack 
            // - The only command that generates "OUTPUT: " 
            char * TOP();

            // operators
            // outputs the Stack to ostream for printing purposes.
            friend ostream & operator<<(ostream & os, Stack stack);
            // getters and setters
            void set_fd(int fd);
            // get the size of the stack
            size_t get_size(){return this->size;}
            // get pointer to the head of the stack
            str_Node * get_head(){return this->head;}
            void add_node(char * data);
            
    };
}

#endif
