/* 
+++
    Copyright (C) 2012 Carlos Nasillo / me@carlosnasillo.com.
    
    Permission is hereby granted, free of charge, to any person obtaining a copy of 
    this software and associated documentation files (the "Software"), to deal in the 
    Software without restriction, including without limitation the rights to use, copy,
    modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
    and to permit persons to whom the Software is furnished to do so, subject to the 
    following conditions:
    
    The above copyright notice and this permission notice shall be included in all copies
    or substantial portions of the Software.
    
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
    INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR 
    PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
    FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR 
    OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
---
*/

#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <Tree.h>

using namespace std;


void Tree::create(){
    root = NULL;
}


bool Tree::isEmpty(){
    if(root != NULL)
        return false;
    else
        return true;
}


TreeNode* Tree::getRoot(void){
    if(!Tree::isEmpty())
        return root;
    else
        return NULL;
}


string Tree::readTop(){
    if(!isEmpty())
        return root->name;
    else
        return NULL;
}


int Tree::Height(TreeNode *node){
    int left, right;
    
    if(node==NULL)
        return 0;
    left = Height(node->left);
    right = Height(node->right);
    if(left > right)
        return left+1;
    else
        return right+1;
}


TreeNode* Tree::add(string cityName, float lat, float lon){
    counter = counter + 2;
    if(isEmpty()){
        return (root = new TreeNode(cityName, lat, lon));
    }
    else
        return add(root, cityName, lat, lon);
}


TreeNode* Tree::add(TreeNode*& node, string cityName, float lat, float lon){
    if(node == NULL)
        node = new TreeNode(cityName, lat, lon);
    else if(cityName < node->name){
        add(node->left, cityName, lat, lon);
        if(Height(node->left) - Height(node->right) == 2){
            if(cityName < node->left->name)
                rotateLeftOnce(node);
            else
                rotateLeftTwice(node);
        }
    }
    else if(cityName > node->name){
        add(node->right, cityName, lat, lon);
        if(Height(node->right) - Height(node->left) == 2){
            if(cityName > node->right->name)
                rotateRightOnce(node);
            else
                rotateRightTwice(node);
        }
    }
    return node;
}


void Tree::rotateLeftOnce(TreeNode*& node){
    TreeNode *otherNode;
    
    otherNode = node->left;
    node->left = otherNode->right;
    otherNode->right = node;
    node = otherNode;
}


void Tree::rotateLeftTwice(TreeNode*& node){
    rotateRightOnce(node->left);
    rotateLeftOnce(node);
}


void Tree::rotateRightOnce(TreeNode*& node){
    TreeNode *otherNode;
    
    otherNode = node->right;
    node->right = otherNode->left;
    otherNode->left = node;
    node = otherNode;
}


void Tree::rotateRightTwice(TreeNode*& node){
    rotateLeftOnce(node->right);
    rotateRightOnce(node);
}


TreeNode* Tree::get(string cityName, bool deleteCity){
    if(!isEmpty())
        get(root, cityName, deleteCity);
    else
        cout << "There is nothing to search. Database is empty" << endl;
}


TreeNode* Tree::get(TreeNode*& node, string cityName, bool deleteCity){
    if(node == NULL){
        cout << "\nERROR: City was not found. Search is case-sensitive." << endl;
    }
    else
        if(cityName == node->name){
            if(deleteCity)
                node->visible = false;
            else
                modify(node);
        }
        else if(cityName < node->name)
            get(node->left, cityName, deleteCity);
        else if(cityName > node->name)
            get(node->right, cityName, deleteCity);
}


TreeNode* Tree::obtainCoordinates(string cityA, string cityB) {
    if(!isEmpty()){
        cityA_Found = false;
        obtainCoordinates(root, cityA, cityB, cityA_Found);
    }
    else
        cout << "There is nothing to search. Database is empty" << endl;
}


TreeNode* Tree::obtainCoordinates(TreeNode*& node, string cityA, string cityB, bool cityA_Found) {
    if(node == NULL){
        cout << "\nERROR: City was not found. Search is case-sensitive." << endl;
        proceed = false;
    }
    else if (!cityA_Found) {
        if(cityA == node->name){
            latA = node->latitude;
            lonA = node->longitude;
            cityA_Found = true;
            obtainCoordinates(root, cityA, cityB, cityA_Found);
        }
        else if(cityA < node->name)
            obtainCoordinates(node->left, cityA, cityB, cityA_Found);
        else if(cityA > node->name)
            obtainCoordinates(node->right, cityA, cityB, cityA_Found);
    }
    else
        if(cityB == node->name){
            latB = node->latitude;
            lonB = node->longitude;
            proceed = true;
        }
        else if(cityB < node->name)
            obtainCoordinates(node->left, cityA, cityB, cityA_Found);
        else if(cityB > node->name)
            obtainCoordinates(node->right, cityA, cityB, cityA_Found);
}



void Tree::modify(TreeNode*& node){
    cout << "\nEnter new Latitude: ";
    cin >> node->latitude;
    cout << "Enter new Longitude: ";
    cin >> node->longitude;
    cout << "Changes have been successful!\n\n";
}


void Tree::display(TreeNode* root, ostream &out){
    if (root!=NULL) {
        display(root->left, out);
        if(root->visible == true)
            out << "\t" << root->name << "\t\t" << root->latitude << "\t\t" << root->longitude << endl;
        display(root->right, out);
    }
}


void Tree::save(TreeNode* root){
    if(!isOpen){
        city.open("city.txt", ios::out);
        latitude.open("lat.txt", ios::out);
        longitude.open("lon.txt", ios::out);
        isOpen = true;
    }
    if (root!=NULL) {
        save(root->left);
        if(root->visible == true){
            city << root->name << endl;
            latitude << root->latitude << endl;
            longitude << root->longitude << endl;
        }
        save(root->right);
    }
    counter--;
    if(counter == 1){
        city.close();
        latitude.close();
        longitude.close();
    }
}
