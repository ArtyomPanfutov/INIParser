//
//  IniParser.h
//  Ini Parser
//
//  Created by Artyom Panfutov on 02/02/2019.
//

#ifndef IniParser_h
#define IniParser_h

#include <cstring>
#include <fstream>
#include <vector>

class ConfigurationFile
{
    std::string              FileName;          // Name of configuration file
    bool                     IsReadOnly;        // By default is true
    std::fstream             IniFile;
    std::vector<std::string> ReadedLines;
    
    void        InitFile();
    void        CopyToFile();
    inline void DeallocateCache();
    inline void ClearCache();
public:
    ConfigurationFile (std::string File);
    ConfigurationFile (std::string File, bool IsReadOnly);
    ~ConfigurationFile();
    
    std::string GetFileName();
    size_t      GetValue(std::string Section, std::string Property, std::string &Value);
    void        DisplayAllLines();
    void        Reload();
    
    void InsertSection(std::string SectionName);
    void InsertProperty(std::string Section, std::string Property, std::string Value);
    int  FindSection(std::string Section);
};

#endif /* IniParser_h */
