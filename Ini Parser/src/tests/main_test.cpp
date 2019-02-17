//
//  main_test.cpp
//  Ini Parser
//
//  Created by Артем on 02/02/2019.
//  Copyright © 2019 Artyom Panfutov. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <string>
#include "../IniParser.h"

class LogWriter
{
public:
    void ScratchMessage(std::string Message)
    {
        std::cout << std::endl << "Tester ->> "  << Message;
    }
};

int main()
{
    try
    {
        LogWriter Clerk;
        std::string FoundValue;
        size_t RetVal;
        
        ConfigurationFile develop_test(std::string("develop_test.ini"));
        Clerk.ScratchMessage(std::string("Configuration file: " + develop_test.GetFileName()));
        
        Clerk.ScratchMessage(std::string("\n All lines from file: \n"));
        develop_test.DisplayAllLines();
        
        RetVal = develop_test.GetValue(std::string("Options"), std::string ("Parameter_1"), FoundValue);
        
        if (RetVal == 0)
            Clerk.ScratchMessage(std::string("Found value = ") +  FoundValue);
        else
            Clerk.ScratchMessage(std::string("Not found."));
        
        develop_test.InsertSection(std::string("Inserted from program"));
        
        develop_test.InsertProperty(std::string("FIRE"), std::string("PropertyInsertedFromProgram"), std::string("Success!"));
        develop_test.DisplayAllLines();
        std::cout << "\nYes!\n";
        return 0;
    }
    catch (std::exception &e)
    {
        LogWriter Clerk;
        Clerk.ScratchMessage(e.what());
    }
    
}
