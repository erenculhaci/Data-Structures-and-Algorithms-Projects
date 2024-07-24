#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>

#include "structs.h"

using namespace std;


//-------------Initialize Priority Queue-------------//
PriorityQueue::PriorityQueue(){
    //I initialized head as NULL.
    head = NULL;

};

//-------------Insert New Node To Priority Queue-------------//
void PriorityQueue::enque(Node* newnode){
    //At first if the queue's head is null, I assigned newnode to head.
    if (head == NULL){
        head = newnode;
    }
    //Then if the head's token value is bigger than the newnode's token value, I assigned newnode as head and the old head as newnode's next.
    else if(head->token.val > newnode->token.val){
            newnode->next = head;
            head = newnode;
    }
    //And if head is not null but head's next node is null, and also head's token value is equal or lower than newnode, I assigned head's next node to newnode.
    else if (head->next == NULL && head->token.val <= newnode->token.val){
        head->next = newnode;
    }
    //And else I created a temp pointer and made it equal to head. Then in the while loop I go to the node where newnode's token value is equal or bigger than temp's next value.
    else{
        Node* temp = head;
        
        while (temp->next != NULL && temp->next->token.val <= newnode->token.val){
            temp = temp->next;
        }
        //If I reach the end of queue, I assign newnode at the tail.
        if(temp->next == NULL){
            temp->next = newnode;
        }
        //If I dont reach to the end of queue, I assign newnode's next node as temp's next node and newnode as temp's new next node.
        else {
            newnode->next = temp->next;
            temp->next = newnode;
        }
    }
    
};

//-------------Remove Node From Priority Queue-------------//
Node* PriorityQueue::dequeue(){

    Node* delNode = head;
    //I created delNode equal to head and if the head node of queue is null, I return null.
    if(head == NULL){
        return NULL;
    }
    //If head is not NULL, first I assigned head as delNode's next node. So delNode became the old head. And I return the delNode which is the old head.
    else{
        head = delNode->next;
        return delNode;
    }
};

//-------------Initialize Tree-------------//
Tree::Tree(){
    //I initialized tree's root as NULL.
    root = NULL;
};

//-------------Delete Tree Nodes From Memory-------------//
Tree::~Tree(){
    //I called deleteTree method with parameter root.
    deleteTree(root);
};

//-------------Delete Tree From Memory-------------//
void Tree::deleteTree(Node* node){
    //-------------This Function Is Not Necessary-------------//
    //-----------------Use It At Your Own Will----------------//
    
    //If tree is empty I didnt do anything.    
    if (node == NULL){
        return;
    }
    //If tree is not empty I deleted all nodes with traversing recursively.
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

//-------------Merges Two Node Into One-------------//
Node* Tree::mergeNodes(Node* temp1, Node* temp2){
   //I craeted a merged node.
   Node* merged_node = new Node;
   // I assigned first given node to mergednode's left and second given node to mergednode's right.
   merged_node->left = temp1;
   merged_node->right = temp2;
   // I added first and second given node's vals and symbols and merged into merged_node's val and symbol.
   merged_node->token.val = temp1->token.val + temp2->token.val;
   merged_node->token.symbol = temp1->token.symbol + temp2->token.symbol;
   return merged_node; //returned to merged node.
};

void Tree::printTree(Node* traverse, int level){
    cout << level << "\t";
    for (int i = 0; i < level; i++)
        cout << "\t"; 

    cout << traverse->token.symbol << "(" << traverse->token.val << ")" << endl;

    if(traverse->left)
        printTree(traverse->left, level + 1);  
    if(traverse->right)
        printTree(traverse->right, level + 1);
};