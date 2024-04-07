#pragma once
#include <memory>
#include <sstream>
#include <iostream>

typedef float f32;
typedef unsigned int ui32;
typedef  int i32;


class OVertexArrayObject;
class OUniformBuffer;
class OShader;

typedef std::shared_ptr<OUniformBuffer> OUniformBufferPtr;
typedef std::shared_ptr<OVertexArrayObject> OVertexArrayObjectPtr;
typedef std::shared_ptr<OShader> OShaderPtr;


struct OVertexAttribute
{
	ui32 numElements = 0;
};


struct OVertexBufferDesc
{
	void* verticesList = 0;
	ui32 vertexSize = 0;
	ui32 listSize = 0;

	OVertexAttribute* attributesList = nullptr;
	ui32 attributesListSize = 0;
};

struct OIndexBufferDesc
{
	void* indicesList = 0;
	//  ui32 indexSize = 0;
	ui32 listSize = 0;
};


enum OTriangleType
{
	TriangleList = 0,
	TriangleStrip
};


enum OCullType
{
	BackFace = 0,
	FrontFace,
	Both
};

enum OWindingOrder
{
	ClockWise = 0,
	CounterClockWise
};

struct OUniformBufferDesc
{
	ui32 size = 0;
};


struct OShaderDesc
{
	const wchar_t* vertexShaderFile;
	const wchar_t* fragmentShaderFile;
};



enum OKey
{
	KeyEscape = 0,
	KeyShift,
	KeyA,
	KeyB,
	KeyC,
	KeyD,
	KeyE,
	KeyF,
	KeyG,
	KeyH,
	KeyI,
	KeyJ,
	KeyK,
	KeyL,
	KeyM,
	KeyN,
	KeyO,
	KeyP,
	KeyQ,
	KeyR,
	KeyS,
	KeyT,
	KeyU,
	KeyV,
	KeyW,
	KeyX,
	KeyY,
	KeyZ,
	Key0,
	Key1,
	Key2,
	Key3,
	Key4,
	Key5,
	Key6,
	Key7,
	Key8,
	Key9,
	KeyF1,
	KeyF2,
	KeyF3,
	KeyF4,
	KeyF5,
	KeyF6,
	KeyF7,
	KeyF8,
	KeyF9,
	KeyF10,
	KeyF11,
	KeyF12,
};


enum OMouseButton
{
	MouseButtonLeft,
	MouseButtonMiddle,
	MouseButtonRight
};

#define OGL3D_ERROR(message)\
{\
std::stringstream m;\
m << "OGL3D Error: " << message << std::endl;\
throw std::runtime_error(m.str());\
}

#define OGL3D_WARNING(message)\
std::wclog << "OGL3D Warning: "  << message << std::endl;

#define OGL3D_INFO(message)\
std::wclog << "OGL3D Info: "  << message << std::endl;