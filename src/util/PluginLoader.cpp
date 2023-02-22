#include "PluginLoader.hpp"

stem::PluginLoader::PluginLoader()
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

void stem::PluginLoader::loadModules()
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
}

void stem::PluginLoader::retrieveFuncPointers()
{
  // Create function pointers
  typedef std::unique_ptr<stem::EntryPoint> (__cdecl *ObjProc)(void);
  typedef std::string (__cdecl *NameProc)(void);
  // Create instances of function pointers
  ObjProc objFunc;
  NameProc nameFunc;
  // Function addresses
  std::string objFuncAddress = "getObj";
  std::string nameFuncAddress = "getName";

  for (HINSTANCE hInst : m_modules)
  {
    // Get function object
    objFunc = (ObjProc)GetProcAddress(hInst, objFuncAddress.c_str());
    nameFunc = (NameProc)GetProcAddress(hInst, nameFuncAddress.c_str());

    // If successfully retrieved function object...
    if (nameFunc != NULL)
    {
      m_entryPoints.push_back(objFunc());
      //std::cout << "Plugin " << nameFunc() << " loaded!" << std::endl;
    }
    else
    {
      std::cout << "Unable to get proc address" << std::endl;
    }
  }
}

void stem::PluginLoader::loadPlugins()
{
  loadModules();
  retrieveFuncPointers();
}

void stem::PluginLoader::unloadPlugins()
{
  for (HINSTANCE hInst : m_modules)
  {
    FreeLibrary(hInst);
  }

  //std::cout << "Unloaded plugins" << std::endl;
}