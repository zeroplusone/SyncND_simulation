# include "Parameter.hpp"

void sync(double currentTime) {
    for (int i = 0; i < Parameter::syncNodes.size(); ++i) {
        Parameter::eventList.insert(*(new Event(1, Parameter::groupList[1].nodeList[Parameter::syncNodes[i]].idInGroup, ACTIVE_START, currentTime)));
    }
    Parameter::syncNodes.clear();
}

int main(int argc, char* argv[]) {

    // argument error handling
    if (argc != 5) {
        cerr << "Please enter 4 paramters: " << endl;
        cerr << "./SyncND.out simulation_time(in ms) duty_cycle(0~1) update_frequency(in ms) slot_duration(in ms)" << endl;
        return 1;
    }
    // parameters setting
    Parameter para(strtod(argv[1], NULL), strtod(argv[2], NULL), strtod(argv[3], NULL), strtod(argv[4], NULL));
    para.settingDisplay();
    if (!para.checkSetting()) {
        cerr << "Input values are not acceptable." << endl;
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
    Parameter::GLOBAL_TIME = 0;
    while (Parameter::GLOBAL_TIME <= Parameter::SIM_TIME && !Parameter::eventList.empty()) {
        Event e = *(Parameter::eventList.begin());
        Parameter::eventList.erase(Parameter::eventList.begin());
        // if (e.eventType == ACTIVE_START)
        //     cout << "# Event(START) [" << e.time << "] " << e.groupId << " " << e.nodeId << endl;
        // else if (e.eventType == ACTIVE_END)
        //     cout << "# Event(END) [" << e.time << "] " << e.groupId << " " << e.nodeId << endl;
        // else if (e.eventType == CALIBRATION)
        //     cout << "# Event(CALIBRATION) [" << e.time << "] " << e.groupId << " " << e.nodeId << endl;

        // for(set<Event>::iterator it=Parameter::eventList.begin(); it!= Parameter::eventList.end();++it){
        //     cout<<"!"<<it->groupId<<" "<<it->nodeId<<" "<<it->eventType<<" "<<it->time<<endl;
        // }

        // for(int i=0;i<Parameter::groupList.size();++i){
            Parameter::groupList[e.groupId].process(e);
        // }
        Parameter::GLOBAL_TIME = Parameter::eventList.begin()->time;
    }

    // show result
    for (int i = 1; i < Parameter::groupList.size(); ++i) {
        cout << "Group " << i << ": " << endl;
        Parameter::groupList[i].totalStat();
    }
    return 0;
}