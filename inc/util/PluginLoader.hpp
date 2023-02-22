/**
 * @brief This file is part of {{ stem.inc.util }}
 * 
 * @file PluginLoader.hpp
 * @author Christian Santos
 * @version 1.0.1
 * @date 7/2/2022
 * 
 * <a href="https://m.cplusplus.com/articles/48TbqMoL/"> TwilightSpectre </a>
 */

#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <filesystem>

#include <windows.h>

#include "EntryPoint.hpp"

namespace fs = std::filesystem;

namespace stem
{
  /**
   * @class PluginLoader
   * @brief handles loading plugins
   */
  class PluginLoader
  {
  public:
    /**
     * @brief PluginLoader() constructor
     */
    PluginLoader();

    /**
     * @brief loads plugins from plugin path
     */
    void loadPlugins();
    /**
     * @brief unloads plugins
     */
    void unloadPlugins();

    /// list of EntryPoint pointers
    std::vector<std::unique_ptr<stem::EntryPoint>> m_entryPoints;
  private:
    /// list of DLL handles
    std::vector<HINSTANCE> m_modules;
    /// plugin path
    fs::path m_plugin_path;
    /// path iterator
    fs::directory_iterator m_path_itr;

    /**
     * @brief loads Handle instances from given directory (plugin)
    */
    void loadModules();
    /**
     * @brief retrieves entry point function pointers from m_modules
    */
    void retrieveFuncPointers();
  };
}