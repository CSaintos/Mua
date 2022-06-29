/**
 * @brief This file is part of {{ stem.test }}
 * 
 * @file PMTest.cpp
 * @author Christian Santos
 * @version 1.0.0
 * @date 6/29/2022
 */

#include <iostream>

#include "PluginManager.hpp"

int main(int argc, char* argv[])
{
  stem::PluginManager plugin_manager;
  plugin_manager.loadPlugins();
  plugin_manager.executePlugins();
  plugin_manager.unloadPlugins();

  return 0;
}