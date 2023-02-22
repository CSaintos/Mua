/**
 * @brief This file is part of {{ stem.test.util }}
 * 
 * @file PMTest.cpp
 * @author Christian Santos
 * @version 1.0.1
 * @date 7/2/2022
 */

#include <iostream>

#include "PluginLoader.hpp"

int main(int argc, char* argv[])
{
  stem::PluginLoader plugin_manager;
  plugin_manager.loadPlugins();
  plugin_manager.unloadPlugins();

  return 0;
}