//
// Created by jimmy on 9/25/2023.
//
#include "tree.h"
#include <iostream>
#include <string>
#include <queue>
#include <stack>
using namespace std;

Node::Node() {
    name = "null";
    ID = "00000000";
    right = nullptr;
    left = nullptr;
}

// Creates nodes for inserting into tree, called in insert()
Node::Node(string ID, string name, int height) {
    this->ID = ID;
    this->name = name;
    right = nullptr;
    left = nullptr;
    this->height = height;
}
// Initializes tree, called at start of main()
Tree::Tree(){
    root = nullptr;
};

Tree::Tree(Node* root) {
    this->root = root;
}

// Inserts new node into tree, calls on rotSelect() if tree balancing is needed
string Tree::insert(string ID, string name) {
    if(ID.length() != 8){
        return "unsuccessful";
    }
    for(int t = 0; t < int(ID.length()); t++){
        if(!isdigit(ID[t])){
            return "unsuccessful";
        }
    }
    for(int j = 0; j < int(name.length());j++){
        if(isalpha(name[j]) or name[j] == ' '){
            continue;
        }
        else{
            return "unsuccessful";
        }
    }
    if(root == nullptr){
        root = new Node(ID,name,1);
        return "successful";
    }
    bool success = false;
    Node* curr = root;
    Node* grandparent = root;
    Node* greatGrandparent = root;
    vector<string> path;
    while(1==1){
        if(curr->ID == ID){
            return "unsuccessful";
        }
        if(curr->ID < ID){
            path.push_back("right");
            if(curr->right == nullptr){
                break;
            }
            curr = curr->right;
        }
        else if(curr->ID > ID){
            path.push_back("left");
            if(curr->left == nullptr){
                break;
            }
            curr = curr->left;
        }
    }
    if(curr != root) {
        for (int i = 0; i < int(path.size()) - 2; i++) {
            if (path[i] == "right") {
                grandparent = grandparent->right;
            }
            else if (path[i] == "left") {
                grandparent = grandparent->left;
            }
        }
    }
    if(grandparent != root){
        for(int i = 0; i < int(path.size())-3;i++){
            if (path[i] == "right") {
                greatGrandparent = greatGrandparent->right;
            }
            else if (path[i] == "left") {
                greatGrandparent = greatGrandparent->left;
            }
        }
    }
    if(curr->ID > ID){
        curr->left = new Node(ID,name,curr->height+1);
        success = true;
    }
    else if(curr->ID < ID){
        curr->right = new Node(ID,name,curr->height+1);
        success = true;
    }
    if(grandparent->left == nullptr and grandparent->right != nullptr and
    (grandparent->right->left != nullptr or grandparent->right->right != nullptr)){
        rotSelect(grandparent,greatGrandparent);
    }
    else if(grandparent->right == nullptr and grandparent->left != nullptr and
    (grandparent->left->right != nullptr or grandparent->left->left != nullptr)){
        rotSelect(grandparent,greatGrandparent);
    }
    if(success){
        return "successful";
    }
    else {
        return "unsuccessful";
    }
}

// Removes node from tree by iteratively searching for ID
string Tree::remove(string ID) {
    if(ID.length() != 8){
        return "unsuccessful";
    }
    for(int t = 0; t < int(ID.length()); t++){
        if(!isdigit(ID[t])){
            return "unsuccessful";
        }
    }
    if(root == nullptr){
        return "unsuccessful";
    }
    Node* curr = root;
    if(root->ID == ID){
        if(root->right == nullptr and root->left == nullptr){
            root = nullptr;
            return "successful";
        }
        Node* successor = root->right;
        Node* succParent;
        while(successor->left != nullptr){
            succParent = successor;
            successor = successor->left;
        }
        if(root->right == successor){
            successor->left = root->left;
            root = successor;
        }
        else{
            if(successor->right != nullptr){
                succParent->left = successor->right;
                succParent->left->height = successor->height;
                successor->height = root->height;
                root = successor;
            }
            else {
                succParent->left = nullptr;
                successor->left = root->left;
                successor->height = root->height;
                root = successor;
            }
        }
        return "successful";
    }
    bool left;
    Node* parent;
    while(curr->ID != ID){
        if(curr->ID > ID){
            left = true;
            parent = curr;
            curr = curr->left;
        }
        else if(curr->ID < ID){
            left = false;
            parent = curr;
            curr = curr->right;
        }
        if(curr == nullptr){
            return "unsuccessful";
        }
    }
    Node* toDelete = curr;
    if(curr->right == nullptr and curr->left == nullptr){
        if(left){
            parent->left = nullptr;
        }
        else{
            parent->right = nullptr;
        }
        return "successful";
    }
    else if(curr->right != nullptr and curr->left == nullptr){
        if(left){
            parent->left = curr->right;
            curr->right->height--;
        }
        else{
            parent->right = curr->right;
            curr->right->height--;
        }
        return "successful";
    }
    else if(curr->right == nullptr and curr->left != nullptr){
        if(left){
            parent->left = curr->left;
            curr->left->height--;
        }
        else{
            parent->right = curr->left;
            curr->left->height--;
        }
        return "successful";
    }
    else {
        Node* newParent = curr;
        newParent = curr;
        curr = curr->right;
        while (curr->left != nullptr) {
            newParent = curr;
            curr = curr->left;
        }
        newParent->left = nullptr;
        if (left) {
            parent->left = curr;
        } else {
            parent->right = curr;
        }
        if(curr != toDelete->left) {
            curr->left = toDelete->left;
        }
        else{
            curr->left = nullptr;
        }
        if(curr != toDelete->right) {
            curr->right = toDelete->right;
        }
        else{
            curr->right = nullptr;
        }
        curr->height = toDelete->height;
        return "successful";
    }
}

// Searches ID iteratively in tree and returns name
string Tree::searchID(string ID) {
    if(ID.length() != 8){
        return "unsuccessful";
    }
    for(int t = 0; t < int(ID.length()); t++){
        if(!isdigit(ID[t])){
            return "unsuccessful";
        }
    }
    if(root == nullptr){
        return "unsuccessful";
    }
    queue<Node*> q;
    q.push(root);
    while(!q.empty()){
        if(q.front()->ID == ID){
            return q.front()->name;
        }
        Node* curr = q.front();
        q.pop();
        if(curr->left != nullptr){
            q.push(curr->left);
        }
        if(curr->right != nullptr){
            q.push(curr->right);
        }
    }
    return "unsuccessful";
}

// Searches names iteratively in tree and returns ID, can return more than one ID
string Tree::searchName(string name) {
    for(int j = 0; j < int(name.length());j++){
        if(isalpha(name[j]) or name[j] == ' '){
            continue;
        }
        else{
            return "unsuccessful";
        }
    }
    if(root == nullptr){
        return "unsuccessful\n";
    }
    queue<Node*> q;
    bool found = false;
    q.push(root);
    while(!q.empty()){
        if(q.front()->name == name){
            found = true;
            cout << q.front()->ID << endl;
        }
        Node* curr = q.front();
        q.pop();
        if(curr->left != nullptr){
            q.push(curr->left);
        }
        if(curr->right != nullptr){
            q.push(curr->right);
        }
    }
    if(found){
        return "";
    }
    return "unsuccessful\n";
}

// Prints inorder tree traversal recursively
Node *Tree::printInorder(Node* node) {
    if(node->left != nullptr){
        printInorder(node->left);
    }
    if(firstPrint) {
        testVector.push_back(node->ID);
        cout << node->name;
        firstPrint = false;
    }
    else{
        testVector.push_back(node->ID);
        cout << ", " << node->name;
    }
    if(node->right != nullptr){
        printInorder(node->right);
    }
    return nullptr;
}

// Prints preorder tree traversal recursively
Node *Tree::printPreorder(Node* node) {
    if(node == this->root){
        cout << node->name;
    }
    else {
        cout << ", " << node->name;
    }
    if(node->left != nullptr){
        printPreorder(node->left);
    }
    if(node->right != nullptr){
        printPreorder(node->right);
    }
    return nullptr;
}

// Prints postorder tree traversal recursively
Node *Tree::printPostorder(Node *node) {
    if(node->left != nullptr){
        printPostorder(node->left);
    }
    if(node->right != nullptr){
        printPostorder(node->right);
    }
    if(node == this->root){
        cout << node->name;
    }
    else {
        cout << node->name << ", ";
    }
    return nullptr;
}

// Prints level count of tree by iterating through tree and saving max height
int Tree::printLevelCount() {
    queue<Node*> q;
    int max = 0;
    if(root == nullptr){
        return max;
    }
    q.push(root);
    while(!q.empty()){
        if(q.front()->height > max){
            max = q.front()->height;
        }
        Node* curr = q.front();
        q.pop();
        if(curr->left != nullptr){
            q.push(curr->left);
        }
        if(curr->right != nullptr){
            q.push(curr->right);
        }
    }
    return max;
}

// Removes Nth node from tree using in order traversal
string Tree::removeInorder(int N) {
    stack<Node*> stack;
    stack.push(root);
    Node* curr = root;
    int counter = 0;
    while(!stack.empty()){
        if(curr->left != nullptr){
            stack.push(curr->left);
            curr = curr->left;
            continue;
        }
        curr = stack.top();
        stack.pop();
        counter++;
        if(counter > N){
            remove(curr->ID);
            return "successful";
        }
        if(curr->right != nullptr) {
            stack.push(curr->right);
            curr = curr->right;
        }
    }
    return "unsuccessful";
}

// Executes left rotation, called on by rotSelect()
void Tree::leftRot(Node *grandparent, Node* greatGrandparent) {
    Node *parent = grandparent->right;
    parent->left = grandparent;
    parent->height = parent->height-1;
    grandparent->height = grandparent->height + 1;
    parent->right->height = parent->right->height - 1;
    grandparent->right = nullptr;
    parent->right->height = parent->right->height - 1;
    if(grandparent != root) {
        if (greatGrandparent->right == grandparent) {
            greatGrandparent->right = parent;
        } else {
            greatGrandparent->left = parent;
        }
    }
    else{
        root = parent;
    }
}

//Executes right rotation, called on by rotSelect()
void Tree::rightRot(Node *grandparent, Node* greatGrandparent) {
    Node *parent = grandparent->left;
    parent->right = grandparent;
    parent->height = parent->height-1;
    grandparent->height = grandparent->height + 1;
    parent->left->height = parent->left->height - 1;
    grandparent->left = nullptr;
    if(grandparent != root) {
        if (greatGrandparent->right == grandparent) {
            greatGrandparent->right = parent;
        } else {
            greatGrandparent->left = parent;
        }
    }
    else{
        root = parent;
    }
}

// Decides what type of rotation is needed, called on by insert()
void Tree::rotSelect(Node *grandparent, Node *greatGrandparent) {
    if(grandparent->left == nullptr and grandparent->right != nullptr and grandparent->right->right != nullptr){
        leftRot(grandparent,greatGrandparent);
    }
    else if(grandparent->right == nullptr and grandparent->left != nullptr and grandparent->left->left != nullptr){
        rightRot(grandparent,greatGrandparent);
    }
    else if(grandparent->left == nullptr and grandparent->right != nullptr and grandparent->right->left != nullptr){
        Node* parent = grandparent->right;
        int parentH = parent->height;
        grandparent->right = parent->left;
        int childH = parent->left->height;
        parent->left->height = parentH;
        parent->left = nullptr;
        parent->height = childH;
        grandparent->right->right = parent;
        leftRot(grandparent,greatGrandparent);
    }
    else if(grandparent->right == nullptr and grandparent->left != nullptr and grandparent->left->right != nullptr){
        Node* parent = grandparent->left;
        int parentH = parent->height;
        grandparent->left = parent->right;
        int childH = parent->right->height;
        parent->right->height = parentH;
        parent->right = nullptr;
        parent->height = childH;
        grandparent->left->left = parent;
        rightRot(grandparent,greatGrandparent);
    }
}

void runner(){
    // Creates tree
    Tree tree;
    // Takes in input for how many commands to expect
    string numInstructions;
    getline(cin,numInstructions);
    for(int i = 0; i < stoi(numInstructions); i++){
        // Finds command
        string command;
        cin >> command;
        // If statements check for each command, or print unsuccessful if invalid command
        if(command == "insert"){
            string name;
            string ID;
            // Formats input for entrance into insert function
            char delim = '"';
            getline(cin,name, delim);
            getline(cin,name, delim);
            getline(cin,ID);
            ID.erase(0,1);
            cout << tree.insert(ID,name);
        }
        else if(command == "search"){
            string input;
            getline(cin,input);
            if(isdigit(input[1])){
                input.erase(0,1);
                string ID = input;
                cout << tree.searchID(ID);
            }
            else{
                input.pop_back();
                input.erase(0,2);
                cout << tree.searchName(input);
                continue;
            }
        }
        else if(command == "remove"){
            string ID;
            getline(cin,ID);
            ID.erase(0,1);
            cout << tree.remove(ID);
        }
        else if(command == "printInorder"){
            tree.firstPrint = true;
            tree.printInorder(tree.root);
        }
        else if(command == "printPreorder"){
            tree.printPreorder(tree.root);
        }
        else if(command == "printPostorder"){
            tree.printPostorder(tree.root);
        }
        else if(command == "printLevelCount"){
            cout << tree.printLevelCount();
        }
        else if(command == "removeInorder"){
            string N;
            getline(cin,N);
            cout << tree.removeInorder(stoi(N));
        }
        else{
            cout << "unsuccessful";
        }
        cout << endl;
    }
}