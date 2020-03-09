
#pragma once

#include <sstream>
#include <string>
#include <iostream>
#include <unordered_map>
#include <cassert>

class Tag 
{
public:
    using  AttrType = std::unordered_map<std::string, std::string>;

private:
    std::unordered_map<std::string, Tag*> m_tags;
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
    void addAttribute(const std::string& key, const std::string& value)
    {
        m_attributes[key] = value;
    }

    AttrType& getAttributes()
    {
        return m_attributes;
    }

    void AddSubTag(Tag* tag)
    {
        m_tags.insert({tag->getName(), tag});
    }

    void dump ()
    {
        std::cout <<  m_name << "\n\t";
        for (auto att : m_attributes) {
            std::cout << att.first << " : " << att.second << "\n\t";
        }
        for (auto t : m_tags) {
            t.second->dump();
        }
    } 
};

class HRML 
{
private:
    std::unordered_map<std::string, Tag*> m_tags;

public:
    void ParseInput();
    void dump(); 

private:
    std::string ParseName(std::stringstream& ss);
    void ParseAndSetName(std::stringstream& ss, Tag* tag);
    void ParseAndSetAttributes(std::stringstream& ss, Tag* tag);
    void ParseTag(std::stringstream& ss, Tag* parentTag = nullptr) ;
    void ParseTags(const std::string& line);
    void AddTag(Tag* tag);
};
