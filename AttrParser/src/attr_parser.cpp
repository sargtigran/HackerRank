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

void HRML::dump() {
    for (auto t : m_tags) {
        std::cout << t.first << "\n\t";
        for (auto att : t.second->getAttributes()) {
            std::cout << att.first << " : " << att.second << "\n\t";
        }  
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

void HRML::ParseTag(std::stringstream& ss, Tag* parentTag) 
{
    char c = 0;
    ss >> std::ws >> c;

    if (c == '<') { ss >> c; }

    if (c == '/') {
        std::string name = ParseName(ss);
        if (parentTag) {
            assert(parentTag->getName() == name);
        }
        return;
    }

    Tag* tag = new Tag;

    ss.putback(c);
    ParseAndSetName(ss, tag);
    ParseAndSetAttributes(ss, tag);
    if (parentTag) {
        parentTag->AddSubTag(tag);
    }
    ParseTag(ss, tag);
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

    Tag* t  = new Tag;
    while (ss >> c)  {
        if (c == '<') {
            ParseTag(ss);
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
    AddTag(tag);
}


