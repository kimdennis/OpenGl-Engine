#pragma once
#include <OGL3D/Math/OVec3.h>
#include <OGL3D/Math/OVec2.h>

class  OVertexMesh
{
public:
	OVertexMesh() :m_position(), m_texcoord(), m_normal()
	{
	}
	OVertexMesh(const  OVec3& position, const  OVec2& texcoord, const  OVec3& normal) :
		m_position(position),
		m_texcoord(texcoord),
		m_normal(normal)
	{
	}
	OVertexMesh(const  OVertexMesh& vertex) :
		m_position(vertex.m_position),
		m_texcoord(vertex.m_texcoord),
		m_normal(vertex.m_normal)
	{
	}
public:
	OVec3 m_position;
	OVec2 m_texcoord;
	OVec3 m_normal;

};