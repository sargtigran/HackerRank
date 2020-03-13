
#include <fstream>
#include "attr_parser.hpp"

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    
    std::ifstream ifile;
    ifile.open("../input.txt");
    assert(ifile.good());
    HRML tree(ifile);
    tree.ParseInput();
    tree.dump();
    //ParseInputHRML(tree);
    //ReadAndRunCommands();

    return 0;
}
