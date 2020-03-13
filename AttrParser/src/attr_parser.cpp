
// Header files
#include <sstream>
#include <string>
#include <iostream>
#include <unordered_map>
#include <cassert>

#include "attr_parser.hpp"

void HRML::ParseInput() 
{
    unsigned n = 0;
    unsigned q = 0;
    input >> n >> q;
    input >> std::noskipws;
    ParseTags(n);
    RunQueries(q);
} 

void HRML::ParseTags(const unsigned n) 
{
    for (int i = 0; i < n; ++i) {
        assert(IsNewTag());
        Tag* t  = new Tag;
        ParseTag(t);
        AddTag(t);
    }
}


void HRML::RunQueries(const unsigned q)
{
    for (int i = 0; i < q; ++i) {
        assert(input.good());
        std::string out;
        RunQuery(out);
        std::cout << out << std::endl;
    }
}

void HRML::RunQuery(std::string& out) 
{
    std::string name = ParseToken();
    Tag* tag = GetTag(name);
    if (! tag) {
        out = "Not Found!";
        return;
    }
    char c;
    while (input >> c && c == '.') {
        name = ParseToken();
        tag = tag->GetSubTag(name);
        if (! tag) {
            out = "Not found!";
        }
    }

    if (c == '~') {
        name = ParseToken();
        out = tag->GetAttribute(name);

        if (out.empty()) {
            out = "Not found!";
        }
    } else {
        assert (!"Icorrect query format");
    }
}

void HRML::ParseTag(Tag* tag) 
{
    assert(tag);
    ParseTagName(tag);
    ParseTagAttributes(tag);
    ParseSubTags(tag);
    ParseTagEnd(tag);
}

Tag* HRML::GetTag(const std::string& name)
{
    auto it = m_tags.find(name);
    if (it != m_tags.end()) {
        return it->second;
    }
    return nullptr;
}

void HRML::ParseTagEnd(Tag* tag)
{
    assert(tag);
    char c = 0;
    
    //if (! (ss >> std::ws >> c && c == '<')) {
    //    assert(! "Syntax error");
    //    // handle error
    //}

    if (input >> c && c == '/') {
        std::string name = ParseToken();
        if (tag->getName() != name) {
            std::cerr << "begin name: " << tag->getName() << std::endl;
            std::cerr << "end name: " << name << std::endl;
            assert (! "Syntax error, do not matchting tag begin name with tag end name");
        }
        if (! (input >> c && c == '>')) {
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

std::string HRML::ParseToken()
{
    char c = 0;
    std::string token;
    input >> std::ws;
    while (input >> c && std::isalnum(c)) {
        token += c;
    }
    input.putback(c);
    return token;
}

void HRML::ParseTagName(Tag* tag)
{
    assert(tag);
    std::string name = ParseToken();
    tag->setName(name);
}

void HRML::ParseTagAttributes(Tag* tag)
{
    assert(tag);
    char c = 0;
    while (input >> std::ws >> c && c != '>') {
        input.putback(c); // bad practice
        std::string name = ParseToken();
        std::string value;
        input >> std::ws >> c;
        if (c == '=') {
            input >> std::ws >> c;
            if (c == '\"') {
                value = ParseToken();
                input >> c;
                assert (c == '\"');
            }
        }
        if (value.empty()) { 
            //error
        }
        tag->addAttribute(name, value);
    }
}

bool HRML::IsNewTag()
{
    char c = 0;
    bool res  = false;
    input >> std::ws >> c; 
    if (c == '<') {
        res  = true;
        char c1 = input.peek();
        if (c1 == '/') {
            res = false;
        }
    }
    return res;
}

void HRML::ParseSubTags(Tag* tag)
{
    while (IsNewTag()) {
        Tag* subTag = new Tag;
        ParseTag(subTag);
        tag->AddSubTag(subTag);
    }
}

void HRML::AddTag(Tag* tag)
{
    m_tags.insert({tag->getName(), tag});
} 

