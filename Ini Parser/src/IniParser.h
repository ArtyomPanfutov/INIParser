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
    
    void InitFile();
public:
    ConfigurationFile (std::string File);
    ConfigurationFile (std::string File, bool IsReadOnly);
    std::string GetFileName();
    int GetValue(std::string Section, std::string Property, std::string &Value);
    void DisplayAllLines();
};

#endif /* IniParser_h */
