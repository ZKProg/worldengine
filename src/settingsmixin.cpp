#include "settingsmixin.hpp"

SettingsMixin::SettingsMixin(const std::string file)
{
    std::ifstream fileStream(file);
    if (!fileStream.is_open())
    {
        std::cout << "The file " << file << " could not be opened." << std::endl;
        exit(-1);
    }

    std::string content, current;
    std::string currentSection;
    while (std::getline(fileStream, current))
    {
        if (current.size() != 0 && current.at(0) == '[')
        {
            std::size_t p = current.find_last_of(']');
            currentSection = current.substr(1, p - 1);
        }

        if (current.size() > 0)
        {
            std::size_t p = current.find_first_of('=');
            if (p != std::string::npos)
            {
                // String before the '='
                std::string k = current.substr(0, p);
                // String after the '=', hence the p + 1
                std::string v = current.substr(p + 1, current.size());

                m_kV[currentSection].insert(std::pair<std::string, std::string>(k, v));
            }
        }

        content += current + "\r\n";
    }
    
    m_fileContent = content;
}


SettingsMixin::~SettingsMixin()
{

}

void SettingsMixin::displayContent()
{   
    //std::cout << "WIDTH: " << m_kV["window"]["width"].c_str() << std::endl;
}