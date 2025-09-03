#include "pch.h"
#include "Debug.h"

#include <iostream>

void Debug::Log(const std::string& message)
{
#ifdef _DEBUG
#ifdef RIDER
    std::cout << "[LOG] \033[32m" << message << "\033[0m\n";

#else
    std::wstring wMessage(message.begin(), message.end());
    wMessage += L"\n";
    OutputDebugStringW(wMessage.c_str());
#endif // RIDER
#endif
}

void Debug::Error(const std::string& message)
{
#ifdef _DEBUG
    std::cout << "[ERROR] \033[31m" << message << "\033[0m\n";
#else
    std::cout << "[ERROR] \033[31m Run in Debug for more\n";
#endif
}

void Debug::LogifErrored(HRESULT result, const std::string& message)
{
    if (FAILED(result))
    {
        Error(message);
    }
}
