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
	enum ConfigsModifier {ADDFILE, CHANGETRIGGER, CHANGERATIO, RENDERGRID, BLOOMSTRENGTH, BLOOM, RENDERDEBUG, RENDERSKYBOX, SHADOW, DEFAULT};
	enum SceneModifier {ADDCOMPONENT, DELETECOMPONENT, COPYCOMPONENT};
	enum JsonType {Scene, Config};
	enum ScallingWay {Up = 1, Bottom = -1, EMPTY = 0};
	enum FramebufferType {COLORBUFFER, DEPTHBUFFER};

}

#endif