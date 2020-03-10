
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
    std::unordered_map<std::string, Tag*> m_subTags;
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
        m_subTags.insert({tag->getName(), tag});
    }

    void dump ()
    {
        static std::string tab = "";
        std::cout << tab;
        std::cout << '<' << m_name << '>' << " subtags: " << m_subTags.size() << std::endl;
        tab += "\t";
        for (auto att : m_attributes) {
            std::cout << tab;
            std::cout << att.first << " : " << att.second << std::endl;
        }
        for (auto t : m_subTags) {
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
    void ParseTagName(std::stringstream& ss, Tag* tag);
    void ParseTagAttributes(std::stringstream& ss, Tag* tag);
    void ParseSubTags(std::stringstream& ss, Tag* tag);
    void ParseTagEnd(std::stringstream& ss, Tag* tag);
    void ParseTag(std::stringstream& ss, Tag* parentTag = nullptr) ;
    void ParseTags(const std::string& line);
    void AddTag(Tag* tag);

    bool IsNewTag(std::stringstream& ss);
    std::string ParseToken(std::stringstream& ss);
};
