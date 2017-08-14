# include "Event.hpp"

Event::Event(int nodeId, int eventType, double time) {
    this->nodeId = nodeId;
    this->eventType = eventType;
    this-> time = time;
}