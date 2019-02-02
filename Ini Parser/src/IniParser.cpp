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
#include <iostream>

ConfigurationFile::ConfigurationFile (std::string File)
{
    FileName   = File;
    IsReadOnly = true;
    
    InitFile();
}

ConfigurationFile::ConfigurationFile (std::string File, bool IsReadOnly)
{
    FileName   = File;
    IsReadOnly = IsReadOnly;
    
    InitFile();
}

void ConfigurationFile::InitFile()
{
    std::string BufferString;
    
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
    
    while (std::getline(IniFile, BufferString))
    {
        ReadedLines.push_back(BufferString);
    }
    
    IniFile.close();
}

std::string ConfigurationFile::GetFileName()
{
    return FileName;
}

void ConfigurationFile::DisplayAllLines()
{
    for (const auto& Line : ReadedLines)
    {
        std::cout << Line << "\n";
    }
}
