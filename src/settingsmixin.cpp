#include "settingsmixin.hpp"

SettingsMixin::SettingsMixin(const std::string file)
  : m_file(file)
{
  this->parseSettingsFile();  
}

SettingsMixin::SettingsMixin(SettingsMixin&& mixin)
  : m_cameras(mixin.m_cameras),
    m_rendererType(mixin.m_rendererType),
    m_applicationName(mixin.m_applicationName),
    m_file(mixin.m_file),
    m_width(mixin.m_width),
    m_height(mixin.m_height)
{
  // TODO MeshesGL Vector not copied at this point
  std::cout << "Settings Mixin Copy constructor called." << std::endl;
}


SettingsMixin::~SettingsMixin()
{

}

void SettingsMixin::parseSettingsFile()
{
    // XML Version
  XMLDocument settings;
  if (settings.LoadFile(m_file.c_str()) != XML_SUCCESS)
  {
    std::cout << "The settings file could not be found/parsed." << std::endl;
    exit(-1);
  }

  XMLElement *rootElement = settings.RootElement();

  if (rootElement != nullptr)
  {
    XMLElement *window = rootElement->FirstChildElement("window");
    if (window == nullptr) this->exitCorruptFile("Window section corrupt. No window node detected.");
    
    XMLElement *windowRenderer = window->FirstChildElement("renderer");
    if (window == nullptr) this->exitCorruptFile("Window section corrupt. Renderer missing or bad syntax.");

    // WINDOW      ///////////////////////////////////////////////////////////////////////////////////////////////
    m_rendererType = windowRenderer->GetText();
    
    // TODO must test for errors all of the xml parsing! No complete testing for now...
    float m_width = std::stof(windowRenderer->Attribute("width"));
    float m_height = std::stof(windowRenderer->Attribute("height"));
    
    // APPLICATIONS //////////////////////////////////////////////////////////////////////////////////////////////
    XMLElement *application = rootElement->FirstChildElement("application");
    if (application == nullptr) this->exitCorruptFile("Application node missing or bad syntax.");
    
    m_applicationName = application->FirstChildElement("name")->GetText();
    
    // MODELS      ///////////////////////////////////////////////////////////////////////////////////////////////
    XMLElement *models = rootElement->FirstChildElement("models");
    if (application == nullptr) this->exitCorruptFile("Models node missing or bad syntax.");
    
    XMLElement *model = models->FirstChildElement("model");
    while (!model)
    {
      // TODO make the diff between name and file name
      std::string name = model->FirstChildElement("name")->GetText();
    
      model = models->FirstChildElement("model");
    }
    
  }

}

void SettingsMixin::exitCorruptFile(const char *probableReason)
{
  std::cout << "Corrupt xml settings file: " << probableReason << std::endl;
  exit(-1);
}
