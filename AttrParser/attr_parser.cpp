#include <cctype>
#include <cmath>
#include <cstdio>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>

class Tag 
{
public:
    using  AttrType = std::unordered_map<std::string, std::string>;

private:
    AttrType m_attributes;
    std::string m_name;

public:
    void setName(const std::string& s)
    {
        m_name = s;
    }

    std::string getName()
    {
        return m_name;
    }
    void addAttribute(const std::string& key, const std::string& value) {
        m_attributes[key] = value;
    }

    AttrType& getAttributes() {
        return m_attributes;
    }

};

class HRML 
{
private:
    std::unordered_map<std::string, Tag*> m_tags;

public:
    void ParseInput() 
    {
        std::string l = "<tag1 attr1 = val1>";
        //while (std::getline(std::cin, l)) {
            ParseTags(l);
            //ParseCommands();
        //}
        
    } 

    void dump() {
        for (auto t : m_tags) {
            std::cout << t.first << "\n\t";
            for (auto att : t.second->getAttributes()) {
                std::cout << att.first << " : " << att.second << "\n\t";
            }  
        }
    }      

private:
    void ParseTags(const std::string& line) 
    {
        std::stringstream ss(line);

        char c = 0;

        Tag* t  = new Tag;
        while (ss >> c)  {
            if (c == '<') {
                std::string name;
                ss >> name;
                if (ss.fail()) { return ; } // error case
                t->setName(name);
            
            } else if (c == '>') {

            } else if (c == '/') {
            
            } else if (c == '=') {

            } else if (std::isalnum(c)) {
                ss.putback(c);
                std::string attr_name;
                std::string attr_value;
                ss >> attr_name;
                ss >> attr_value;
                t->addAttribute(attr_name, attr_value);
            }
        }
        m_tags.insert({t->getName(), t});
     }
};

//void ParseInputHRML(HRML tree)
//{
//    HRML 
//}

void ReadAndRunCommands() {

}


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    
    HRML tree;
    tree.ParseInput();
    tree.dump();
    //ParseInputHRML(tree);
    ReadAndRunCommands();

    return 0;
}
