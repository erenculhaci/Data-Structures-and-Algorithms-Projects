#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <bits/stdc++.h>

#include "huffman.h"
#include "structs.h"

using namespace std;

void Huffman::readKey(const char* argv){
    ifstream readKeyFile;
    readKeyFile.open(argv);

    if(readKeyFile.is_open()){
        while(!readKeyFile.eof()){
            readKeyFile >> key;
        }
    }
    readKeyFile.close();
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//---------Sorts the key in an alpabetic order---------//
void Huffman::sortKey(){
    sortedKey = key;
    sort(sortedKey.begin(), sortedKey.end());
};
//-----------------------------------------------------//


//-----------------------------------------------------//
//-------Finds the frequency of the characters---------//
//-----------------------------------------------------//
void Huffman::findFrequency(){
    //DO NOT CHANGE THIS
    sortKey();
    //DO NOT CHANGE THIS
    
    //I created a temporary node and started its val from 1.
    Node* temporary = new Node;
    temporary->token.val = 1;
    
    //I made a for loop that loops in the sorted key. And if the sortedkey's i'th character is equal to (i+1)th character then it adds 1 to temporary's token.val
    for (int i=0; i<(int)sortedKey.size(); i++){
        
        if(sortedKey[i] == sortedKey[i+1]){
            temporary->token.val++;
            continue;
        }
        // I queued temporary node to Priority queue and this temporary node has the i'th character of sortedKey as token.symbol
            temporary->token.symbol.append(1, sortedKey[i]);
            queue.enque(temporary);
        //I created a new ndoe with same name as temporary. And then changed its token.val to 1.     
        temporary = new Node;
        temporary->token.val = 1;
    }
    //So this method found the frequency of the characters in sortedkey and queued all nodes in PriorityQueue.
    free(temporary);
};
//-----------------------------------------------------//


//-----------------------------------------------------//
//----------------Creates Huffman Tree-----------------//
//-----------------------------------------------------//
void Huffman::createHuffmanTree(){
    //first I queued all characters into priority queue with their frequency.
    findFrequency();
    
    while(queue.head->next != NULL){
    //Then while until there is only one node in the queue, I take the first two nodes of the queue and merge them and I make this merged node as huffmantree's root.
    huffmanTree.root = huffmanTree.mergeNodes(queue.head,queue.head->next);
    //Then I make queue's first and second node as huffman tree's root's left and right nodes by dequeing them at the same time.
    huffmanTree.root->left = queue.dequeue();
    huffmanTree.root->right = queue.dequeue();
    //Then I enque the new root of the huffmantree to the PriorityQueue.
    queue.enque(huffmanTree.root);
    }
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//---------------Prints the Huffman Tree---------------//
void Huffman::printHuffmanTree(){
    huffmanTree.printTree(huffmanTree.root, 0);
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//-------------Finds and returns the binary------------//
//----------------value to given character-------------//
//-----------------------------------------------------//
string Huffman::getTokenBinary(char tokenChar, Node* traverse, string tokenBinary){
    //If the symbol of traverse has only 1 element and is equal to given character then I return to tokenBinary.
        if ((int)(traverse->token.symbol).size() == 1 && traverse->token.symbol[0] == tokenChar ){
        return tokenBinary;
    }

    //I created a bool flag starting with false. Then I created a string symb that takes the traverse's left node's symbol. And lastly I created integer size that takes the number of elements in traverse's symbol string.
       bool flag = false;
       string symb = traverse->left->token.symbol;
       int size = symb.size();
    
    //I go from start to finish along the traverse left node's symbol string. Then if a character in this string is equal to given character then I turn flag to true.
       for(int i = 0; i < size; i++){
            if(symb[i] == tokenChar){
                flag = true;
                break;
            }
       }
        //If the flag is true I go to the left node of the traverse and add 0 into tokenbinary. 
       if(flag == true){
        return getTokenBinary(tokenChar,traverse->left,tokenBinary + "0");
       }
       //If the flag is false I go to the right node of the traverse and add 1 into tokenbinary.
       else {
        return getTokenBinary(tokenChar,traverse->right,tokenBinary + "1");
       }
    
    
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//--------------Encodes the given password-------------//
//-----------------------------------------------------//
void Huffman::encodePassword(string password){
    //------FOR ENCODED BINARY PASSWORD------//
    //I created an empty string named binarypassword.
    string binarypassword = "";

    // For each character in given password, I get the tokenbinary of that character and put it into encodedbinarypassword. In the end I have a encodedBinaryPassword filled with tokenbinaries.
    for (int i = 0; i<(int)password.size();i++){
        encodedBinaryPassword += getTokenBinary(password[i],huffmanTree.root,binarypassword);
    }
    //---------------------------------------//
    //-----FOR ENCODED VAL PASSWORD------//
    //I created an integer tokenvalue, and an empty string named valpassword.
    int tokenvalue;
    string valpassword = "";
    
    //For each character in given password, I find the length of binary represenation of that character. Then I put that integer value into tokenvalue. And I turn that integer value to string and add it to encodedValPassword.
    // In the end I have encodedValPassword filled with depth of characters.
    for (int i = 0; i<(int)password.size();i++){
        tokenvalue = getTokenBinary(password[i],huffmanTree.root,valpassword).size();
        encodedValPassword += to_string(tokenvalue);
    }
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//-------------Prints the encoded password-------------//
//-----------------------------------------------------//
void Huffman::printEncodedPassword(){
    cout << "Encoded Password Binary: " << encodedBinaryPassword << endl;
    cout << "Encoded Password Value: " << encodedValPassword << endl;
};

//-----------------------------------------------------//
//--------------Decodes the given password-------------//
//-----------------------------------------------------//
void Huffman::decodePassword(string encodedBinaryPassword, string encodedValPassword){
    //I created two empty strings named tempStr and passwordDec and one integer named value.
    string tempStr = "";
    string passwordDec = "";
    int value;

    
    for (int i = 0; i<(int)encodedValPassword.size();i++){               //encodedvalpassword's size gives us the number of characters.
        value = encodedValPassword[i] - '0';                             //I find how many bits that i'th character uses and assign it to the value.  
        tempStr = "";                                                    //I emptied the tempStr.
        for(int l = 0; l<value; l++){                                    // In tempStr, I added the binary string of i'th character.
            tempStr += encodedBinaryPassword[l];
        }
        decodeToken(tempStr);                                            // I decoded tempStr(i'th character's bitstring).
        passwordDec += decodedPassword;                                  // Here decodedPassword is what we get from decodeToken. I store all decoded tokens in passwordDec string.   
        encodedBinaryPassword = encodedBinaryPassword.substr(value,encodedBinaryPassword.size()); //I removed the binary string of i'th character from encodedBinaryPassword.
    }
    decodedPassword = passwordDec;              // Lastly decodedPassword is equal to the last passwordDec we get from for loop.
};

//-----------------------------------------------------//

//-----------------------------------------------------//
//---------------Decodes the given binary--------------//
//-----------------------------------------------------//
void Huffman::decodeToken(string encodedToken){
    //I created a decodingNode and made it equal to huffmanTree's root.
    Node* decodingNode;
    decodingNode = huffmanTree.root;

    //In the given encoded binary string, from start to finish in this for loop, if the character in given encodedToken string is 1, I go right in tree, if the character is 0, I go left in tree.
    for (int i = 0; i<(int)encodedToken.size(); i++){
        if(encodedToken[i] == '1'){
            decodingNode = decodingNode->right;
        }
        else if(encodedToken[i] == '0'){
            decodingNode = decodingNode->left;
        }
    }
    //And then I assign the decodingNode's token.symbol -decoded binary- to decodedPassword string in order to use it in decodePassword method.
     decodedPassword = decodingNode->token.symbol;
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//-------------Prints the decoded password-------------//
//-----------------------------------------------------//
void Huffman::printDecodedPassword(){
    cout << "Decoded Password: " << decodedPassword << endl;
};