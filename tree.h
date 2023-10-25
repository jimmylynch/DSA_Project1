//
// Created by jimmy on 9/25/2023.
//
#pragma once
#include <string>
#include <vector>
#include <iostream>

using namespace std;


class Node{
public:
    Node();
    Node(string ID,string name,int height);
    string name;
    string ID;
    Node* right;
    Node* left;
    int height;
};

class Tree{
public:
    Tree();
    Tree(Node* root);
    string insert(string ID, string name);
    string remove(string ID);
    string searchID(string ID);
    string searchName(string name);
    Node* printInorder(Node* node);
    Node* printPreorder(Node* node);
    Node* printPostorder(Node* root);
    int printLevelCount();
    string removeInorder(int N);
    void rotSelect(Node* grandparent, Node* greatGrandparent);
    void leftRot(Node* grandparent, Node* greatGrandparent);
    void rightRot(Node* grandparent, Node* greatGrandparent);
    bool firstPrint = true;
    Node* root;
    vector<string> testVector;
};


void runner();