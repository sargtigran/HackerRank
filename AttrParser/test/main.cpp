
#include <fstream>
#include "attr_parser.hpp"


void RunTest(const std::string& input)
{
    std::ifstream ifile;
    std::ofstream ofile;
    ifile.open(input);
    ofile.open("out_" + input);
    if (ifile.good() && ofile.good()) {
        assert(ifile.good());
        HRML tree(ifile, ofile);
        tree.ParseInput();
        //tree.dump();
    } else {
        std::cout << "Error opening input file: " << input << std::endl;
    }
}

int main()
{
    RunTest("input.txt");
    RunTest("input1.txt");
    RunTest("input2.txt");
    RunTest("input3.txt");
    
    return 0;
}
