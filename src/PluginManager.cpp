#include "PluginManager.hpp"

stem::PluginManager::PluginManager()
  : m_plugin_path("plugin")
{
  try 
  {
    m_path_itr = fs::directory_iterator(m_plugin_path);
  } 
  catch (fs::filesystem_error e)
  {
    std::cout << "Could not locate " << m_plugin_path << std::endl;
  }
}

void stem::PluginManager::loadPlugins()
{
  for (fs::directory_entry const& dir_entry : m_path_itr)
  {
    HINSTANCE temp = LoadLibraryA(dir_entry.path().string().c_str());

    // If file not found
    if (!temp)
    {
      std::cout << "Couldn't load library " << dir_entry.path().string() << std::endl;
      continue;
    }

    // add loaded module to list of modules
    m_modules.push_back(temp);
  }
  //std::cout << "Loaded plugins" << std::endl;
}

void stem::PluginManager::unloadPlugins()
{
  for (HINSTANCE hInst : m_modules)
  {
    FreeLibrary(hInst);
  }
  //std::cout << "Unloaded plugins" << std::endl;
}

void stem::PluginManager::executePlugins()
{
  
}