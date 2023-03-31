#pragma once
#include <string>

namespace Engine
{
    extern void FatalError(std::string _message, int _exitCode);

    extern void Error(std::string _message);

    extern void Warning(std::string _message);
    
    extern void Log(std::string _message); 
}