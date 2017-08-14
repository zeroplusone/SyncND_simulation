# include "Parameter.hpp"
# include "Group.hpp"


int main(int argc, char* argv[]) {

    if (argc != 4) {
        cerr << "Please enter 3 paramters: " << endl;
        cerr << "./SyncND.out duty_cycle success_probability update_frequency" << endl;
        return 1;
    }
    Parameter para(strtod(argv[1], NULL), strtod(argv[2], NULL), atoi(argv[3]));
    para.settingDisplay();

    Group group(2);
    group.process(para);

    return 0;
}