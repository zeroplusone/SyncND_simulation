# include "Group.hpp"

int Group::groupIdCounter = 0;

Group::Group(int numOfNode) {
    this->id = groupIdCounter;
    groupIdCounter += 1;

    // nodeList = new vector<Node>();
    this->numberOfNode = numOfNode;
    while (numOfNode--) {
        nodeList.push_back(*(new Node()));
    }
}

void Group::process() {
    cout << "--- Group_" << this->id << " process ---" << endl;
    for (int i = 0; i < this->numberOfNode; ++i) {
        cout << "Node_" << nodeList[i].id << endl;
    }
}