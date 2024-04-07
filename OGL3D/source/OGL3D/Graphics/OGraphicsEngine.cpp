#include <OGL3D/Graphics/OGraphicsEngine.h>
#include <OGL3D/Graphics/OVertexArrayObject.h>
#include <glad/glad.h>

OVertexArrayObjectPtr OGraphicsEngine::createVertexArrayObject(const OVertexBufferDesc& desc)
{
    return std::make_shared<OVertexArrayObject>(desc);
}
OVertexArrayObjectPtr OGraphicsEngine::createVertexArrayObject(const OVertexBufferDesc& vbDesc, const OIndexBufferDesc& ibDesc)
{
    return std::make_shared<OVertexArrayObject>(vbDesc, ibDesc);
}
OUniformBufferPtr OGraphicsEngine::createUniformBuffer(const OUniformBufferDesc& desc)
{
    return std::make_shared<OUniformBuffer>(desc);
}
OShaderPtr OGraphicsEngine::createShader(const OShaderDesc& desc)
{
    return std::make_shared<OShader>(desc);
}

void OGraphicsEngine::clear(const OVec4& color)
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(color.x, color.y, color.z, color.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDepthFunc(GL_LESS);
}

void OGraphicsEngine::setFaceCulling(const OCullType& type)
{
    auto cullType = GL_BACK;

    if (type == FrontFace)
        cullType = GL_FRONT;
    else if (type == BackFace)
        cullType = GL_BACK;
    else  if (type == Both)
        cullType = GL_FRONT_AND_BACK;

    glEnable(GL_CULL_FACE);
    glCullFace(cullType);

}

void OGraphicsEngine::setWindingOrder(const OWindingOrder& order)
{
    auto orderType = GL_CW;

    if (order == ClockWise)
        orderType = GL_CW;
    else if (order == CounterClockWise)
        orderType = GL_CCW;

    glFrontFace(orderType);
}

void OGraphicsEngine::setVertexArrayObject(const OVertexArrayObjectPtr& vao)
{
    glBindVertexArray(vao->getId());
}
void OGraphicsEngine::drawTriangles(const OTriangleType& triangleType, ui32 vertexCount, ui32 offset)
{
    auto glTriType = GL_TRIANGLE_STRIP;

    if (triangleType == TriangleList) glTriType = GL_TRIANGLES;
    if (triangleType == TriangleStrip) glTriType = GL_TRIANGLE_STRIP;

    glDrawArrays(glTriType, offset, vertexCount);
}

void OGraphicsEngine::drawIndexedTriangles(const OTriangleType& triangleType, ui32 indicesCount)
{
    auto glTriType = GL_TRIANGLE_STRIP;

    if (triangleType == TriangleList) glTriType = GL_TRIANGLES;
    if (triangleType == TriangleStrip) glTriType = GL_TRIANGLE_STRIP;

    glDrawElements(glTriType, indicesCount, GL_UNSIGNED_INT, nullptr);
}

void OGraphicsEngine::setViewport(const ORect& size)
{
    glViewport(size.left, size.top, size.width, size.height);
}
void OGraphicsEngine::setUniformBuffer(const OUniformBufferPtr& buffer, ui32 slot)
{
    glBindBufferBase(GL_UNIFORM_BUFFER, slot, buffer->getId());
}
void OGraphicsEngine::setShader(const OShaderPtr& shader)
{
    glUseProgram(shader->getId());
}