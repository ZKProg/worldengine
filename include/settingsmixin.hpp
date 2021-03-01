#pragma once

#include "pch.h"

#include "camera.hpp"

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
  
  // Map : name => cameraInstance
  std::map<std::string, Camera> m_cameras;
    
};
