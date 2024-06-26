#pragma once
#include <OGL3D/OPrerequisites.h>
#include <OGL3D/Math/OVec4.h>
#include <OGL3D/Math/ORect.h>
#include <OGL3D/Graphics/OShader.h>
#include <OGL3D/Graphics/OVertexArrayObject.h>
#include <OGL3D/Graphics/OUniformBuffer.h>
#include <OGL3D/Graphics/OTexture2D.h>


class OGraphicsEngine
{
public:
    OGraphicsEngine();
    ~OGraphicsEngine();
public:
    OVertexArrayObjectPtr createVertexArrayObject(const OVertexBufferDesc& desc);
    OVertexArrayObjectPtr createVertexArrayObject(const OVertexBufferDesc& vbDesc, const OIndexBufferDesc& ibDesc);
    OUniformBufferPtr createUniformBuffer(const OUniformBufferDesc& desc);
    OShaderPtr createShader(const OShaderDesc& desc);
    OTexture2DPtr createTexture2D(const OTexture2DDesc& desc);

public:
    void clear(const OVec4& color);
    void setFaceCulling(const OCullType& type);
    void setWindingOrder(const OWindingOrder& order);
    void setVertexArrayObject(const OVertexArrayObjectPtr& vao);
    void drawTriangles(const OTriangleType& triangleType,ui32 vertexCount, ui32 offset);
    void drawIndexedTriangles(const OTriangleType& triangleType, ui32 indicesCount);
    void setViewport(const ORect& size);
    void setUniformBuffer(const OUniformBufferPtr& buffer, ui32 slot);
    void setShader(const OShaderPtr& shader);
    void setTexture2D(const OTexture2DPtr& texture, ui32 slot);
};

