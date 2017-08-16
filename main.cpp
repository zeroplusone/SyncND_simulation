# include "Parameter.hpp"

void sync(double currentTime) {
    vector<Node>::iterator it;
    for (it = Parameter::syncNodes.begin(); it != Parameter::syncNodes.end(); ++it) {
        Parameter::eventList.push(*(new Event(it->belongedGroupId, it->id, ACTIVE_START, currentTime)));
    }
}

int main(int argc, char* argv[]) {

    // argument error handling
    if (argc != 5) {
        cerr << "Please enter 4 paramters: " << endl;
        cerr << "./SyncND.out simulation_time(in ms) duty_cycle(0~1) success_probability(0~1) update_frequency(in ms)" << endl;
        return 1;
    }
    // parameters setting
    Parameter para(strtod(argv[1], NULL), strtod(argv[2], NULL), strtod(argv[3], NULL), strtod(argv[4], NULL));
    para.settingDisplay();


    // initial events and group
    // -- global clock --
    Parameter::eventList.push(*(new Event(0, 0, ACTIVE_START, 0)));
    Parameter::groupList.push_back(*(new Group(1)));
    // -- devices --
    for (int i = 1; i <= Parameter::NUMBER_OF_GROUPS; ++i) {
        Parameter::groupList.push_back(*(new Group(2)));
    }

    //simulation start
    while (Parameter::GLOBAL_TIME < Parameter::SIM_TIME && !Parameter::eventList.empty()) {
        Event e = Parameter::eventList.top();
        Parameter::eventList.pop();

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