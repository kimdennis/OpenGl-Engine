#include <OGL3D/Graphics/OShader.h>
#include <glad/glad.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <filesystem>

OShader::OShader(const OShaderDesc& desc)
{
    m_programId = glCreateProgram(); // contains all shaders
    attach(desc.vertexShaderFile, VertexShader);
    attach(desc.fragmentShaderFile, FragmentShader);
    link();
}


void OShader::attach(const wchar_t* fileName, const OShaderType& type)
{
    // Read the Shader code from the file
    std::string shaderCode;
    auto path = std::filesystem::path(fileName);

    std::ifstream shaderStream(path);
    if (shaderStream.is_open()) {
        std::stringstream sstr;
        sstr << shaderStream.rdbuf();
        shaderCode = sstr.str();
        shaderStream.close();
    }
    else
    {
        OGL3D_WARNING("OShader - " << fileName << " not found");
        return;
    }



    //Compile Vertex Shader
    ui32 shaderId = 0;
    if (type == VertexShader)
        shaderId = glCreateShader(GL_VERTEX_SHADER);
    else  if (type == FragmentShader)
        shaderId = glCreateShader(GL_FRAGMENT_SHADER);


    char const* sourcePointer = shaderCode.c_str();
    glShaderSource(shaderId, 1, &sourcePointer, NULL); // set shader source code to the just created shader
    glCompileShader(shaderId);

    // Check Shader for errors  
    GLint result = GL_FALSE;
    int logLength = 0;
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) {
        std::vector<char> errorMessage(logLength + 1);
        glGetShaderInfoLog(shaderId, logLength, NULL, &errorMessage[0]);
        OGL3D_WARNING("OShader - " << fileName << " compiled with errors:" << std::endl << &errorMessage[0]);
        return;
    }

    glAttachShader(m_programId, shaderId); //attaches shader here
    m_attachedShaders[type] = shaderId;

    OGL3D_INFO("OShader - " << fileName << " compiled successfully");
}


void OShader::link()
{
    glLinkProgram(m_programId);

    GLint result = GL_FALSE;
    int logLength;
    glGetProgramiv(m_programId, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) {
        std::vector<char> errorMessage(logLength + 1);
        glGetProgramInfoLog(m_programId, logLength, NULL, &errorMessage[0]);
        OGL3D_WARNING("OShader - " << &errorMessage[0]);
        return;
    }
}
ui32 OShader::getId()
{
    return m_programId;
}
void OShader::setUniformBufferSlot(const char* name, ui32 slot)
{
    unsigned int index = glGetUniformBlockIndex(m_programId, name);
    glUniformBlockBinding(m_programId, index, slot);
}
OShader::~OShader()
{
    for (ui32 i = 0;i < 2;i++)
    {
        glDetachShader(m_programId, m_attachedShaders[i]);
        glDeleteShader(m_attachedShaders[i]);
    }
    glDeleteProgram(m_programId);
}