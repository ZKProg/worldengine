#pragma once

#include "pch.h"

#include "camera.hpp"
#include "meshgl.hpp"

class SettingsMixin
{
public:

  SettingsMixin(const std::string file = "./settings.xml");
  SettingsMixin(SettingsMixin&& mixin);
  ~SettingsMixin();

  void parseSettingsFile();
  void exitCorruptFile(const char* probableReason);
  
  // Map : name => cameraInstance
  std::map<std::string, Camera> m_cameras;
  std::string m_rendererType = "opengl debug"; // sdlgl, wxgl, qtgl, sdlvulkan
  std::string m_applicationName;
  std::string m_file;x
  std::vector<MeshGL> m_meshesGL;

  float m_width, m_height;
  
protected:

  
};
