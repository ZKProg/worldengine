#pragma once

#include "pch.h"

class SettingsMixin
{
public:

    SettingsMixin(const std::string file = "./settings.ini");
    ~SettingsMixin();

    void displayContent();

    std::map<
        std::string,                        // first
        std::map<std::string, std::string>> // second
        m_kV;                               // var name


protected:

    std::string m_fileContent;
    
};