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
    DeallocateCache();
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
size_t ConfigurationFile::GetValue(std::string Section, std::string Property, std::string &Found)
{
    std::size_t       FoundPosition;
    std::size_t       StartPosition;
    bool              IsSectionFound = false;
    const std::string CommentSymbol  = ";";
    
    Reload(); // Actualize cache
    
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
                    return 100;
                
                Found = Line.substr(++FoundPosition, Line.length() - FoundPosition);
                return 0;
            }
        }
    }
    return -1;
}
//--------------------------------------------------------------------

//
// InsertSection:
//   - SectionName should be without square brackets
//   Will be inserted at the end
///////////////////////////////////////////////////////////////////////
void ConfigurationFile::InsertSection(std::string SectionName)
{
    std::string FinalName;
    FinalName = std::string("[") + SectionName + std::string("]");
    
    if (!IniFile.is_open())
    {
        IniFile.open(FileName, std::ios::out | std::ios::app);
        if (!IniFile.is_open())
        {
            throw std::runtime_error("Can't open configuration file!");
        }
    }
    
    IniFile << FinalName;
    IniFile.close();
}
//---------------------------------------------------------------------

//
// Reload:
//   Actualize cache
///////////////////////////////////////////////////////////////////////
void ConfigurationFile::Reload()
{
    ClearCache();
    InitFile();
}
//---------------------------------------------------------------------

//
// DeallocateCache:
//   - Clear the vector and deallocate memory
///////////////////////////////////////////////////////////////////////
inline void ConfigurationFile::DeallocateCache()
{
    ClearCache();
    ReadedLines.shrink_to_fit(); // Shrink the capacity to fit the size (which is 0 now)
}
//---------------------------------------------------------------------

//
// ClearCache:
//   - Clear the vector
///////////////////////////////////////////////////////////////////////
inline void ConfigurationFile::ClearCache()
{
    ReadedLines.clear();
}
//---------------------------------------------------------------------

//
// InsertProperty:
//   Section  - Section name. Can be with or without square brackets. If section will not be found -> insert it
//   Property - Property name.
//   Found    - Value.
///////////////////////////////////////////////////////////////////////
void ConfigurationFile::InsertProperty(std::string Section, std::string Property, std::string Value)
{
  
    

}
//---------------------------------------------------------------------

//
// FindSection
//   Returns -1 if not found. Else number of line
///////////////////////////////////////////////////////////////////////
int ConfigurationFile::FindSection(std::string Section)
{
    size_t            FoundPosition;
    size_t            StartPosition;
    int               CurrentLine    = -1;
    bool              IsSectionFound = false;
    const std::string CommentSymbol  = ";";
    
    Reload(); // Actualize cache
    
    FoundPosition = Section.find(std::string("["));
    
    if (FoundPosition == std::string::npos)
    {
        Section = std::string("[") + Section + std::string("]");
    }
    
    for (const auto& Line : ReadedLines)
    {   CurrentLine++;
        StartPosition = 0;
        FoundPosition = Line.find(CommentSymbol);
        
        if (FoundPosition != std::string::npos)
            StartPosition = FoundPosition;
        
        if (!IsSectionFound)
        {
            FoundPosition = Line.find(Section, StartPosition);
            
            if (FoundPosition != std::string::npos)
            {
                IsSectionFound = true;
                break;
            }
        }
    }
    
    if (IsSectionFound)
        return CurrentLine;
    else
        return -1;
}
//---------------------------------------------------------------------
