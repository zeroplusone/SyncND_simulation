#ifndef GROUP_H
#define GROUP_H

#include "Node.hpp"
#include <vector>
#include <iostream>
using namespace std;

class Node;
class Group {
public:
    Group(int);
    void process();
    static int groupIdCounter;
    int id;
private:
    vector<Node> nodeList;
    int numberOfNode;
};


#endif