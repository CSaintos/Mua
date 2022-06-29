/**
 * @brief This file is part of {{ stem.inc }}
 * 
 * @file PluginManager.hpp
 * @author Christian Santos
 * @version 1.0.0
 * @date 6/29/2022
 */

#pragma once

#include <iostream>
#include <vector>
#include <filesystem>

#include <windows.h>

namespace fs = std::filesystem;

namespace stem
{
  /**
   * @class PluginManager
   * @brief handles loading plugins
   */
  class PluginManager
  {
  public:
    /**
     * @brief PluginManager() constructor
     */
    PluginManager();

    /**
     * @brief loads plugins from plugin path
     */
    void loadPlugins();
    /**
     * @brief unloads plugins
     */
    void unloadPlugins();
    /**
     * @brief executes plugins
     */
    void executePlugins();
  private:
    /// list of DLL handles
    std::vector<HINSTANCE> m_modules;
    /// plugin path
    fs::path m_plugin_path;
    /// path iterator
    fs::directory_iterator m_path_itr;
  };
}