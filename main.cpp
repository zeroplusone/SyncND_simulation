# include "Parameter.hpp"

void sync(double currentTime) {
    for (int i = 0; i < Parameter::syncNodes.size(); ++i) {
        Parameter::eventList.push(*(new Event(1, Parameter::groupList[1].nodeList[Parameter::syncNodes[i]].idInGroup, ACTIVE_START, currentTime)));
    }
    Parameter::syncNodes.clear();
}

int main(int argc, char* argv[]) {

    // argument error handling
    if (argc != 4) {
        cerr << "Please enter 3 paramters: " << endl;
        cerr << "./SyncND.out simulation_time(in ms) duty_cycle(0~1) update_frequency(in ms)" << endl;
        return 1;
    }
    // parameters setting
    Parameter para(strtod(argv[1], NULL), strtod(argv[2], NULL), strtod(argv[3], NULL));
    para.settingDisplay();
    if(!para.checkSetting()){
        cerr<< "Input values are not acceptable."<<endl;
        return 1;
    }

    // initial events and group
    // -- global clock group --
    Parameter::groupList.push_back(*(new Group(1)));
    // -- devices groups--
    for (int i = 1; i <= Parameter::NUMBER_OF_GROUPS; ++i) {
        Parameter::groupList.push_back(*(new Group(2)));
    }

    //simulation start
    while (Parameter::GLOBAL_TIME <= Parameter::SIM_TIME && !Parameter::eventList.empty()) {
        Event e = Parameter::eventList.top();
        Parameter::eventList.pop();
        if (e.eventType == ACTIVE_START)
            cout << "# Event(START) [" << e.time << "] " << e.groupId << " " << e.nodeId << endl;
        else if (e.eventType == ACTIVE_END)
            cout << "# Event(END) [" << e.time << "] " << e.groupId << " " << e.nodeId << endl;

        if (e.groupId == 0) {
            switch (e.eventType) {
            case ACTIVE_START:
                sync(e.time);
                Parameter::GLOBAL_TIME += Parameter::ACTIVE_DURATION;
                Parameter::eventList.push(*(new Event(0, 0, ACTIVE_END, e.time + Parameter::ACTIVE_DURATION)));
                break;
            case ACTIVE_END:
                Parameter::GLOBAL_TIME += Parameter::SLEEP_DURATION;
                Parameter::eventList.push(*(new Event(0, 0, ACTIVE_START, e.time + Parameter::SLEEP_DURATION)));
                break;
            default:
                cerr << "Error eventType!!" << endl;
                break;
            }
        } else {
            Parameter::groupList[e.groupId].process(e);
        }
    }
    return 0;
}