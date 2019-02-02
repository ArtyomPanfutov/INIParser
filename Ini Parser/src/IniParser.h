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

class ConfigurationFile
{
    std::string  FileName;          // Name of configuration file
    bool         IsReadOnly;        // By default is true
    std::fstream IniFile;
    
    void InitFile();
public:
    ConfigurationFile (std::string File);
    ConfigurationFile (std::string File, bool IsReadOnly);
    std::string GetFileName();
};

#endif /* IniParser_h */
