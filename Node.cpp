#include "Node.hpp"

int Node::nodeIdCounter = 0;

Node::Node() {
    this->id = nodeIdCounter;
    nodeIdCounter += 1;
}