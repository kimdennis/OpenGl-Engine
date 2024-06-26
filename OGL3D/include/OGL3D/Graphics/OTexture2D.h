#pragma once
#include <OGL3D/OPrerequisites.h>


class OTexture2D
{
public:
    OTexture2D(const OTexture2DDesc& desc);
    ~OTexture2D();
    ui32 getId();
private:
    ui32 m_textureId = 0;
    OTexture2DDesc m_desc = {};
};

