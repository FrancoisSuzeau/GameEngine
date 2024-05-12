/******************************************************************************************************************************************/
// File : StringConstants.hpp
// Purpose : string constant for the application
/******************************************************************************************************************************************/
#ifndef STRINGCONSTANTS_H
#define STRINGCONSTANTS_H

#include <iostream>


namespace Constants {

	std::string const SHADERSPATH = "Shaders/";
	std::string const LOGPATH = "Logs/";
	std::string const LOGEXT = ".txt";
	std::string const SHADERVERTEXT = ".vert";
	std::string const SHADERFRAGEXT = ".frag";
	std::string const SHADERGEOEXT = ".geom";
	std::string const NONE = "NONE";
	std::string const APP = "[APP ";
	std::string const CLIENT = "[CLIENT ";
	std::string const EXTSERVICE = "[EXT SERVICE ";
	std::string const SHARED = "[SHARED ";
	std::string const LOGPATTERN = "%^[%T] %n: %v%$";
	std::string const TRACEFILE = "trace";
	std::string const INFOFILE = "info";
	std::string const DEBUGFILE = "debug";
	std::string const WARNFILE = "warn";
	std::string const ERRFILE = "err";
	std::string const CRITFILE = "crit";
	std::string const IMGUIVERSION = "#version 400";
	std::string const JSONEXT = ".json";
	std::string const CONFIGFILE = "configs";
	std::string const USERPREFNODE = "userpreferences";
	std::string const GUIVIEWMODEL = "GUI";
	std::string const SCENEVIEWMODEL = "SCENE";
	std::string const UNTEXTURED_SHADER = "untextured";
	std::string const TEXTURED_SHADER = "textured";
	std::string const TEXTURED_SPHERE_SHADER = "sphere_textured";
	std::string const HOVER_SHADER = "hover";
	std::string const SCREEN_SHADER = "screen_shader";
	std::string const BLOOM_SHADER = "bloom_shader";
	std::string const DEPTH_SHADER = "depth_mapping_shader";
	std::string const GRID_SHADER = "grid";
	std::string const SKYBOX_SHADER = "skybox";
	std::string const COMPONENT_BASE = "COMPONENT_BASE";
	std::string const COMPONENT_DRAGGABLE = "COMPONENT_DRAGGABLE";
	std::string const COMPONENT_TEXTURED = "COMPONENT_UNTEXTURED";
	std::string const DEFAULT_FILENAME = "default_scene";
	std::string const SCENE_CONFIG_PANNEL = "scene pannel";
	std::string const DEBUG_CONFIG_PANNEL = "debug pannel";
	std::string const GRID_SPACING_SMALL = "Small";
	std::string const GRID_SPACING_MEDIUM = "Medium";
	std::string const GRID_SPACING_LARGE = "Large";
}

#endif