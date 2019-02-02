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
        
        ConfigurationFile develop_test(std::string("develop_test.ini"));
        Clerk.ScratchMessage(std::string("Configuration file: " + develop_test.GetFileName()));
        
        Clerk.ScratchMessage(std::string("\n All lines from file: \n"));
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
