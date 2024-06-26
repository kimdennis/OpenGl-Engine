#pragma once
#include <OGL3D/Game/OGraphicsEntity.h>
#include <OGL3D/Math/OMat4.h>
#include <OGL3D/Math/ORect.h>

//the OCubeEntity class is the entity class that allows to add a cube in the scene
class OCubeEntity : public OGraphicsEntity
{
public:


	virtual void onCreate();

	virtual void setTexture(const OTexturePtr& texture);
protected:
	virtual void onGraphicsUpdate(f32 deltaTime);

private:
	OVertexArrayObjectPtr m_mesh;
	OUniformBufferPtr m_uniform;
	OShaderPtr m_shader;
	OTexturePtr m_texture;

};