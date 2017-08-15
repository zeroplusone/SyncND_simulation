# include "Parameter.hpp"
# include "Group.hpp"


int main(int argc, char* argv[]) {

    if (argc != 5) {
        cerr << "Please enter 4 paramters: " << endl;
        cerr << "./SyncND.out simulation_time(in ms) duty_cycle(0~1) success_probability(0~1) update_frequency(in ms)" << endl;
        return 1;
    }
    Parameter para(strtod(argv[1], NULL), strtod(argv[2], NULL), strtod(argv[3], NULL), strtod(argv[4], NULL));
    para.settingDisplay();

    Group group(2);
    group.process(para);

    return 0;
}