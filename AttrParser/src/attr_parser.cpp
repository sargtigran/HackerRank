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
                    "</tag1> \n"
                    "<tag55 attr55 = \"val55\" bbb55 = \"ccccc55\"> \n"
                    "</tag55>";
    ParseTags(l);
    ParseCommands();
} 

void HRML::ParseCommands(const std::string& cl) 
{
    std::stringstream ss;
    ss << cl;

    do {
        std::string tag_name = ParseToken(ss);
        tag = GetTag(tag_name);
    } while (ss >> c && c == '.');

}

void HRML::ParseTag(std::stringstream& ss, Tag* tag) 
{
    assert(tag);
    ParseTagName(ss, tag);
    ParseTagAttributes(ss, tag);
    ParseSubTags(ss, tag);
    ParseTagEnd(ss, tag);
}


void HRML::ParseTagEnd(std::stringstream& ss, Tag* tag)
{
    assert(tag);
    char c = 0;
    
    //if (! (ss >> std::ws >> c && c == '<')) {
    //    assert(! "Syntax error");
    //    // handle error
    //}

    if (ss >> c && c == '/') {
        std::string name = ParseToken(ss);
        if (tag->getName() != name) {
            std::cerr << "begin name: " << tag->getName() << std::endl;
            std::cerr << "end name: " << name << std::endl;
            assert (! "Syntax error, do not matchting tag begin name with tag end name");
        }
        if (! (ss >> c && c == '>')) {
            assert (! "Syntax error, do not exist closing brackets of tag end");
        }
    } else {
        assert(! "Syntax error");
    }
}

void HRML::dump() {
    std::cout << "Dumping .... "  << m_tags.size() << std::endl;
    for (auto t : m_tags) {
        t.second->dump();
    }
}      

std::string HRML::ParseToken(std::stringstream& ss)
{
    char c = 0;
    std::string token;
    ss >> std::ws;
    while (ss >> c && std::isalnum(c)) {
        token += c;
    }
    ss.putback(c);
    return token;
}

void HRML::ParseTagName(std::stringstream& ss, Tag* tag)
{
    assert(tag);
    std::string name = ParseToken(ss);
    tag->setName(name);
}

void HRML::ParseTagAttributes(std::stringstream& ss, Tag* tag)
{
    assert(tag);
    char c = 0;
    do {
        std::string name = ParseToken(ss);
        std::string value;
        ss >> std::ws >> c;
        if (c == '=') {
            ss >> std::ws >> c;
            if (c == '\"') {
                value = ParseToken(ss);
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

bool HRML::IsNewTag(std::stringstream& ss)
{
    char c = 0;
    bool res  = false;
    ss >> std::ws >> c; 
    if (c == '<') {
        res  = true;
        char c1 = ss.peek();
        if (c1 == '/') {
            res = false;
        }
    }
    //ss.putback(c);
    return res;
}

void HRML::ParseSubTags(std::stringstream& ss, Tag* tag)
{
    while (IsNewTag(ss)) {
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
    std::stringstream ss(std::cin);
    ss >> std::noskipws;

    while (IsNewTag(ss))  {
        Tag* t  = new Tag;
        ParseTag(ss, t);
        AddTag(t);
    }
}


