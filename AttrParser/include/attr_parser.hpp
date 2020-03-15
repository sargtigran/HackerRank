
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

    std::string GetAttribute(const std::string& name)
    {
        auto it = m_attributes.find(name);
        if (it != m_attributes.end()) {
            return it->second;
        }
        return "";
    }

    void AddSubTag(Tag* tag)
    {
        m_subTags.insert({tag->getName(), tag});
    }

    Tag* GetSubTag(const std::string& name)
    {
        auto it = m_subTags.find(name);
        if (it != m_subTags.end()) {
            return it->second;
        }
        return nullptr;
    }

    void dump(std::string tab = "")
    {
        std::cout << tab;
        std::cout << '<' << m_name << '>' << std::endl;
        tab += "\t";
        for (auto att : m_attributes) {
            std::cout << tab;
            std::cout << att.first << " : " << att.second << std::endl;
        }
        for (auto t : m_subTags) {
            t.second->dump(tab);
        }
    } 
};

class HRML 
{
private:
    std::unordered_map<std::string, Tag*> m_tags;
    std::istream& input;
    std::ostream& output;

public:
    
    HRML(std::istream& istr = std::cin, std::ostream& ostr = std::cout)
        : input(istr)
        , output(ostr)
    {}
    
    void ParseInput();
    void dump(); 

private:
    void ParseTags(const unsigned n);
    void RunQueries(const unsigned q);

    void ParseTagName(Tag* tag);
    void ParseTagAttributes(Tag* tag);
    void ParseSubTags(Tag* tag);
    void ParseTagEnd(Tag* tag);
    void ParseTag(Tag* parentTag = nullptr) ;
    void RunQuery(std::string& out);

    bool IsNewTag();
    std::string ParseToken();
    std::string ParseLiteral();
    void AddTag(Tag* tag);
    Tag* GetTag(const std::string& name);
};

