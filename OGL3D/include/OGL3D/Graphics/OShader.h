#ifndef OSHADER_H
#define OSHADER_H

#include <OGL3D/OPrerequisites.h>


class OShader
{
public:
    OShader(const OShaderDesc& desc);
    ~OShader();
    ui32 getId();
    void setUniformBufferSlot(const char* name, ui32 slot);

private:
    enum OShaderType
    {
        VertexShader = 0,
        FragmentShader
    };

    void attach(const wchar_t* fileName, const OShaderType& type);
    void link();

private:
    ui32 m_programId = 0;
    ui32 m_attachedShaders[5]{};
};

#endif // OSHADER_H