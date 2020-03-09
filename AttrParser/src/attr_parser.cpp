#include <sstream>
#include <string>
#include <iostream>
#include <unordered_map>
#include <cassert>

#include "attr_parser.hpp"

void HRML::ParseInput() 
{
    std::string l = "<tag1 attr1 = \"val1\" bbb = \"ccccc\"> \n"
                         " <tag2 vssstt = \"rrrrrrrrrrrr\" attt = \"vvvvvvvvv\"> </tag2> \n"
                         " <tag3 aaa=\"lll\"> </tag3>"
                    "</tag1>";
    //while (std::getline(std::cin, l)) {
        ParseTags(l);
        //ParseCommands();
    //}
    
} 

void HRML::ParseTag(std::stringstream& ss, Tag* tag) 
{
    assert(tag);
    ParseAndSetName(ss, tag);
    ParseAndSetAttributes(ss, tag);
    ParseAndSetSubTags(ss, tag);
}

void HRML::dump() {
    std::cout << "Dumping .... " << std::endl;
    for (auto t : m_tags) {
        t.second->dump();
    }
}      

std::string HRML::ParseName(std::stringstream& ss)
{
    char c = 0;
    std::string name;
    ss >> std::ws;
    while (ss >> c && std::isalnum(c)) {
        name += c;
    }
    ss.putback(c);
    return name;
}

void HRML::ParseAndSetName(std::stringstream& ss, Tag* tag)
{
    assert(tag);
    std::string name = ParseName(ss);
    tag->setName(name);
}

void HRML::ParseAndSetAttributes(std::stringstream& ss, Tag* tag)
{
    assert(tag);
    char c = 0;
    do {
        std::string name = ParseName(ss);
        std::string value;
        ss >> std::ws >> c;
        if (c == '=') {
            ss >> std::ws >> c;
            if (c == '\"') {
                value = ParseName(ss);
                ss >> c;
                assert (c == '\"');
            }
        }
        if (value.empty()) { 
            //error
        }
        tag->addAttribute(name, value);
    } while (ss >> std::ws >> c && c != '>');
}

void HRML::ParseAndSetSubTags(std::stringstream& ss, Tag* tag)
{
    char c = 0;
    while (ss >> std::ws >> c && c == '<') {

        //if (c == '<') { ss >> c; }
        
        if (ss >> c && c == '/') {
            std::string name = ParseName(ss);
            assert(tag->getName() == name);
            ss >> c;
            assert(c == '>');
            continue;
        }

        ss.putback(c);

        Tag* subTag = new Tag;
        ParseTag(ss, subTag);
        tag->AddSubTag(subTag);
    }
}

void HRML::AddTag(Tag* tag)
{
    m_tags.insert({tag->getName(), tag});
} 

void HRML::ParseTags(const std::string& line) 
{
    std::stringstream ss(line);
    ss >> std::noskipws;

    char c = 0;

    while (ss >> c)  {
        if (c == '<') {
            Tag* t  = new Tag;
            ParseTag(ss, t);
            AddTag(t);
        } else if (c == '>') {

        } else if (c == '/') {

        } else if (c == '=') {

        } else if (std::isalnum(c)) {
            ///ss.putback(c);
            ///std::string attr_name;
            ///std::string attr_value;
            ///ss >> attr_name;
            ///ss >> attr_value;
            ///t->addAttribute(attr_name, attr_value);
        }
    }
}


