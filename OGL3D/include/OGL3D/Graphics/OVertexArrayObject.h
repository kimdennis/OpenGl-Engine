#pragma once
#include <OGL3D/OPrerequisites.h>


class OVertexArrayObject
{
public:
    OVertexArrayObject(const OVertexBufferDesc& vbDesc);
    OVertexArrayObject(const OVertexBufferDesc& vbDesc, const OIndexBufferDesc& ibDesc);
    ~OVertexArrayObject();

    ui32 getId();
private:
    ui32 m_vertexArrayObjectId = 0;
   
    ui32 m_vertexBufferObjectId = 0; 
    ui32 m_elementBufferObjectId = 0;
};


