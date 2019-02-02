//
//  IniParser.cpp
//  Ini Parser
//
//  Created by Artyom Panfutov on 02/02/2019.
//

#include <stdio.h>
#include <string>
#include "IniParser.h"
#include <fstream>

ConfigurationFile::ConfigurationFile (std::string File)
{
    FileName   = File;
    IsReadOnly = true;
}

ConfigurationFile::ConfigurationFile (std::string File, bool IsReadOnly)
{
    FileName   = File;
    IsReadOnly = IsReadOnly;
}

void ConfigurationFile::InitFile()
{
    if (IsReadOnly)
    {
        IniFile.open(FileName, std::ios::in);
    }
    else
    {
        IniFile.open(FileName, std::ios::out | std::ios::app);
    }
    
    if (!IniFile.is_open())
    {
        throw std::runtime_error("Can't open configuration file!");
    }
}

std::string ConfigurationFile::GetFileName()
{
    return FileName;
}

