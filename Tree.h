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
#include <TreeNode.h>

using namespace std;


class Tree 
{
    
public:
    float latA, lonA, latB, lonB;
    bool proceed;
    
    
    Tree()
    {
        create();
    }
    
    
    string readTop();
    bool isEmpty();
    int Height(TreeNode *node);

    void create();
    void rotateLeftOnce(TreeNode *&node);
    void rotateLeftTwice(TreeNode *&node);
    void rotateRightOnce(TreeNode *&node);
    void rotateRightTwice(TreeNode *&node);
    void modify(TreeNode *&node);
    void display(TreeNode *root, ostream &out);
    void save(TreeNode* root);
    
    TreeNode* root;
    TreeNode* getRoot();
    TreeNode* add(string cityName, float lat, float lon);
    TreeNode* add(TreeNode *&node, string cityName, float lat, float lon);
    TreeNode* get(string cityName, bool deleteCity);
    TreeNode* get(TreeNode *&node, string cityName, bool deleteCity);
    TreeNode* obtainCoordinates(string cityA, string cityB);
    TreeNode* obtainCoordinates(TreeNode *&node, string cityA, string cityB, bool cityA_Found);

    
private:
    int counter;
    bool isOpen, cityA_Found;
    
    fstream city;
    fstream latitude;
    fstream longitude;
    
};