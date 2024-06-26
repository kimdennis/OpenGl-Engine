#include <OGL3D/Graphics/OVertexArrayObject.h>
#include <glad/glad.h>
#include <stdexcept>

OVertexArrayObject::OVertexArrayObject(const OVertexBufferDesc& desc)
{ 
    if (!desc.vertexSize) OGL3D_ERROR("OVertexArrayObject - vertexSize is NULL");
    if (!desc.listSize) OGL3D_ERROR("OVertexArrayObject - listSize is NULL");
    if (!desc.verticesList) OGL3D_ERROR("OVertexArrayObject - verticesList is NULL");

    //vertex array object VAO creation ------------------------
    glGenVertexArrays(1, &m_vertexArrayObjectId);
    glBindVertexArray(m_vertexArrayObjectId);

    //vertex buffer creation --------------------------------
    glGenBuffers(1, &m_vertexBufferObjectId);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObjectId);
    glBufferData(GL_ARRAY_BUFFER, desc.vertexSize * desc.listSize, desc.verticesList, GL_STATIC_DRAW);
    //--------------------------------------

    for (ui32 i = 0; i < desc.attributesListSize; i++)
    {
        //adding vertex attribute for vertex
        glVertexAttribPointer(
            i, //index of attribute (to use in the glsl shader)
            desc.attributesList[i].numElements, //number of elements of the vertex
            GL_FLOAT, //type of the elements
            GL_FALSE,
            desc.vertexSize, //size of the entire composed vertex (veretx+color)
            (void*)((i==0)?0:desc.attributesList[i-1].numElements * sizeof(float)) //offset from previous attribute
        );
        glEnableVertexAttribArray(i);
        //end of vertex attribute for vertex

    }
    glBindVertexArray(0);
    //---------------------------------------------------
}

OVertexArrayObject::OVertexArrayObject(const OVertexBufferDesc& vbDesc, const OIndexBufferDesc& ibDesc):OVertexArrayObject(vbDesc)
{
    if (!ibDesc.listSize) OGL3D_ERROR("OVertexArrayObject - listSize is NULL");
   // if (!ibDesc.indexSize) OGL3D_ERROR("OVertexArrayObject - indexSize is NULL");
    if (!ibDesc.indicesList) OGL3D_ERROR("OVertexArrayObject - indicesList is NULL");


   // OVertexArrayObject::OVertexArrayObject(vbDesc); // initialize vertex buffer
    
    glBindVertexArray(m_vertexArrayObjectId);

    //initialize index buffer
    glGenBuffers(1, &m_elementBufferObjectId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBufferObjectId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, ibDesc.listSize, ibDesc.indicesList, GL_STATIC_DRAW);

    glBindVertexArray(0);
}

ui32 OVertexArrayObject::getId()
{
    return m_vertexArrayObjectId;
}
OVertexArrayObject::~OVertexArrayObject()
{
    glDeleteBuffers(1, &m_vertexBufferObjectId);
    glDeleteVertexArrays(1, &m_vertexArrayObjectId);
}
