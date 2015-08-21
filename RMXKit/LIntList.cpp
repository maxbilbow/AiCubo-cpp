//
//  LIntList.cpp
//  JustForFun
//
//  Created by Max Bilbow on 09/07/2015.
//  Copyright © 2015 Rattle Media. All rights reserved.
//
//#include "LinkedList.hpp"
#include "LIntList.hpp"
#include <iostream>

LIntList::LIntList() {
    //    this->node = new Node();
    //    this->node.value = NULL;
};


 Node * _last(Node * head) {
    Node * last = head;//->value;
    while (last->next != NULL) {
        last = last->next;
    }
    return last;
};

 int LIntList::append(int value) {
    Node * last = _head;//this is -1 (holds no value)
    
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = new Node();
    last->next->value = &value;
    ++_count;
    return value;
};

 int LIntList::pop(Node ** head) {
    int retval = -1;
    Node * next_node = NULL;
    
    if (*head == NULL) {
        return -1;
    }
    
    next_node = (*head)->next;
    int * retptr = (int*) (*head)->value;
//    free(*head);
    *head = next_node;
     retval = *retptr;
    return retval;
};

 int LIntList::remove_by_value(int val) {
    /* TODO: fill in your code here */
    
    return -1;
};

 void LIntList::print(void) {
    Node * current = this->_head;
    
    while (current != NULL) {
        std::cout << current->value << std::endl;
        current = current->next;
    }
};


void LIntListTest(void) {
    
    LIntList * list = new LIntList();
    list->append(1);
    list->append(2);
    list->append(3);
    list->append(4);
    
    
    list->remove_by_value( 3);
    
    list->print();
};
