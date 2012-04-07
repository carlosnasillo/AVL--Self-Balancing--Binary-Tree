#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <Tree.h>

using namespace std;


class TreeNode 
{
    
public:
    string name;
    float latitude;
    float longitude;
    bool visible;
    
    TreeNode *left;
    TreeNode *right;
    
    TreeNode() {  };
    
    TreeNode(string cityName, float lat, float lon) 
    {
        name = cityName;
        latitude = lat;
        longitude = lon;
        visible = true;
        left = NULL;
        right = NULL;
    }
};