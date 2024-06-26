#include <OGL3D/Graphics/OUniformBuffer.h>
#include <glad/glad.h>


OUniformBuffer::OUniformBuffer(const OUniformBufferDesc& desc)
{
	glGenBuffers(1, &m_uniformBufferId);
	glBindBuffer(GL_UNIFORM_BUFFER, m_uniformBufferId); // create uniform buffer
	glBufferData(GL_UNIFORM_BUFFER, desc.size, nullptr, GL_STATIC_DRAW);  //define the size of the uniform buffer
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	m_desc = desc;
}

OUniformBuffer::~OUniformBuffer()
{
	glDeleteBuffers(1, &m_uniformBufferId);
}

void OUniformBuffer::setData(void* data)
{
	glBindBuffer(GL_UNIFORM_BUFFER, m_uniformBufferId); 
	glBufferSubData(GL_UNIFORM_BUFFER, 0, m_desc.size, data);// pass data to uniform buffer
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

ui32 OUniformBuffer::getId()
{
	return m_uniformBufferId;
}
