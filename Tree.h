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