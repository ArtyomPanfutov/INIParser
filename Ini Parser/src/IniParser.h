//
//  IniParser.h
//  Ini Parser
//
//  Created by Artyom Panfutov on 02/02/2019.
//

#ifndef IniParser_h
#define IniParser_h

#include <cstring>

class ConfigurationFile
{
    std::string FileName;
public:
    ConfigurationFile (std::string File);
    std::string GetFileName();
};

#endif /* IniParser_h */
