#include "Debug.hpp"
#include <iostream>

namespace Engine
{
    void FatalError(std::string _message, int _exitCode)
    {
        std::cout << "\033[0;31mFatalError: \033[0m" + _message << std::endl;
        std::cout << "Press enter to quit";
        std::cin.get();
        exit(_exitCode);
    }

    void Error(std::string _message)
    {
        std::cout << "\033[1;31mError: \033[0m" + _message << std::endl;
    }

    void Warning(std::string _message)
    {
        std::cout << "\033[1;33mWarning: \033[0m" + _message << std::endl;
    }

    void Log(std::string _message)
    {
        std::cout << "\033[1;32mLog: \033[0m" + _message << std::endl;
    }
} // end of Engine namespace