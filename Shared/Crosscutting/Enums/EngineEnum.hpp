/******************************************************************************************************************************************/
// File : EngineEnum.hpp
// Purpose : Enumerator for the engine
/******************************************************************************************************************************************/
#ifndef ENGINEENUM_H
#define ENGINEENUM_H

namespace Enums {

	enum EngineEnum {BEGIN, END};
	enum ServiceEnum {SDL, OPENGL, IMGUI};
	enum ShaderType {NORMAL, GEOMETRIC};
	enum ShaderModifier {VEC3, MAT4, TEXTURE, FLOAT, INT };
	enum CameraMovement {FORWARD, BACKWARD, LEFT, RIGHT};
	enum ConfigsModifier {ADDFILE};
	enum JsonType {Scene, Config};
	enum ScrollDir {Up = 1, Bottom = -1};
}

#endif