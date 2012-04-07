#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <Tree.h>
#include <TreeNode.h>

using namespace std;


Tree t;
void loadFiles();
void mainMenu();
void switchCases(char selection);
void viewData();
void addNewByUser();
void editCurrentData();
void removeEntry();


string cityName, cityToRemove;
float lat, lon;
char menuSelection;


int main() {
    loadFiles();
    mainMenu();
}


void loadFiles() {
    fstream city;
    city.open("city.txt", ios::in);
    fstream latitude;
    latitude.open("lat.txt", ios::in);
    fstream longitude;
    longitude.open("lon.txt", ios::in);
    while(!city.eof()){
        city >> cityName;
        latitude >> lat;
        longitude >> lon;
        t.add(cityName, lat, lon);
    }
    city.close();
    latitude.close();
    longitude.close();
}


void viewData(){
    cout << "\tCity\t" << "  || " << "  Latitude\t" << "  || " << "  Longitude\n";
    cout << "\t----------------------------------------\n";
    t.display(t.getRoot(), cout);
    cout << endl << endl;
    mainMenu();
}


void addNewByUser() {
    cout << "\nEnter the name of new city : ";
    cin >> cityName;
    cout << "Enter location's Latitude: ";
    cin >> lat;
    cout << "Enter Location's Longitude: ";
    cin >> lon;
    t.add(cityName, lat, lon);
    cout << endl << endl;
    mainMenu();
}


void editCurrentData(){
    cout << "\nEnter the name of city you wish to update : ";
    cin >> cityName;
    t.get(cityName, false);
    cout << endl << endl;
    mainMenu();
}


void removeEntry() {
    cout << "\nEnter the name of the city to remove: ";
    cin >> cityToRemove;
    t.get(cityToRemove, true);
    cout << endl << endl;
    mainMenu();
}

void calculateDistance() {
    string start, end;
    float totalDistance;
    
    t.display(t.getRoot(), cout);
    cout << "\nEnter the start location : ";
    cin >> start;
    cout << "Enter the end location : ";
    cin >> end;
    t.obtainCoordinates(start, end);
    if(t.proceed) {
        float lat1 = (t.latA * (M_PI/180)),
        lon1 = (t.lonA * (M_PI/180));
        float lat2 = (t.latB * (M_PI/180)),
        lon2 = (t.lonB * (M_PI/180));
        float tempResult = (sin (lat1)* sin (lat2)) + (cos (lat1) * cos(lat2)) * (cos(lon1 - lon2));
        tempResult = acos(tempResult);
        tempResult = tempResult * (180/M_PI);
        totalDistance = (6371 * M_PI * (tempResult))/180;
        cout << "The calculated distance is: " << totalDistance << endl << endl << endl;
        mainMenu();
    }
    else{
        cout << endl << endl;
        mainMenu();
    }
}



//*********************************   MENU   ***********************************
void mainMenu() {
    cout << "::::::::: WELCOME TO THE WORLD DISTANCE CALCULATOR :::::::::" << endl << endl;
    cout << "Please select one of the following from the menu" << endl;
    cout << "| C |" << " Calculate distances" << endl;
    cout << "| E |" << " Edit database" << endl;
    cout << "| Q |" << " Quit" << endl << endl;
    cout << "Your choise: ";
    cin >> menuSelection;
    switchCases(menuSelection);
}

void editMenu() {
    cout << endl << endl << "::::::::: EDIT DATABASE :::::::::" << endl << endl;
    cout << "Please select one of the following from the menu" << endl;
    cout << "| A |" << " Add data" << endl;
    cout << "| M |" << " Modify current values" << endl;
    cout << "| R |" << " Remove data" << endl;
    cout << "| V |" << " View data" << endl;
    cout << "| B |" << " Back to main menu" << endl << endl;
    cout << "Your choise: ";
    cin >> menuSelection;
    switchCases(menuSelection);
}

void switchCases(char menuSelection){
    switch (menuSelection){
        case 'C':
        case 'c':{
            calculateDistance();
            break;}
        case 'E':
        case 'e':{
            editMenu();
            break;}
        case 'A':
        case 'a':{
            addNewByUser();
            break;}
        case 'V':
        case 'v':{
            viewData();
            break;}
        case 'M':
        case 'm':{
            editCurrentData();
            break;}
        case 'R':
        case 'r':{
            removeEntry();
            break;}
        case 'Q':
        case 'q':{
            t.save(t.getRoot());
            break;}
        default:
        case 'b':
        case 'B':{
            cout << "Invalid Input!!!" << endl << endl << endl;
            mainMenu();}
    }
}