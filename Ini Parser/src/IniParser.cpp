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

//
// Constructors
///////////////////////////////////////////////////////////////////////////
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
//-------------------------------------------------------------------------

//
// Destructor
///////////////////////////////////////////////////////////////////////////
ConfigurationFile::~ConfigurationFile()
{
    ReadedLines.clear();
    ReadedLines.shrink_to_fit(); // Shrink the capacity to fit the size (which is 0 now)
}

//-------------------------------------------------------------------------


//
// InitFile() - Open file and read all lines
///////////////////////////////////////////////////////////////////////////
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
//-----------------------------------------------------------------------

//
// GetFileName()
////////////////////////////////////////////////////////////////////////
std::string ConfigurationFile::GetFileName()
{
    return FileName;
}
//----------------------------------------------------------------------

//
// DsiplayAllLines()
///////////////////////////////////////////////////////////////////////
void ConfigurationFile::DisplayAllLines()
{
    for (const auto& Line : ReadedLines)
    {
        std::cout << Line << "\n";
    }
}
//---------------------------------------------------------------------

//
// GetValue:
//   Section  - Section name. Can be with or without square brackets.
//   Property - Property name.
//   Found    - Found value.
// Returns 0 if success.
//////////////////////////////////////////////////////////////////////
int ConfigurationFile::GetValue(std::string Section, std::string Property, std::string &Found)
{
    std::size_t       FoundPosition;
    std::size_t       StartPosition;
    bool              IsSectionFound = false;
    const std::string CommentSymbol  = ";";
    
    FoundPosition = Section.find(std::string("["));
    
    if (FoundPosition == std::string::npos)
    {
        Section = std::string("[") + Section + std::string("]");
    }
    
    for (const auto& Line : ReadedLines)
    {
        StartPosition = 0;
        FoundPosition = Line.find(CommentSymbol);
        
        if (FoundPosition != std::string::npos)
            StartPosition = FoundPosition;
        
        if (!IsSectionFound)
        {
            FoundPosition = Line.find(Section, StartPosition);
            
            if (FoundPosition != std::string::npos)
                IsSectionFound = true;
        }
        else
        {
            FoundPosition = Line.find(Property, StartPosition);
            
            if (FoundPosition != std::string::npos)
            {
                FoundPosition = Line.find("=");
                
                if (FoundPosition == std::string::npos)
                    return -1;
                
                Found = Line.substr(++FoundPosition, Line.length() - FoundPosition);
                return 0;
            }
        }
    }
    return -1;
}
//--------------------------------------------------------------------
