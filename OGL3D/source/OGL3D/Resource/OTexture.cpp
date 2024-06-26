#include <OGL3D/Resource/OTexture.h>
#include <OGL3D/Resource/OResourceManager.h>
#include <OGL3D/Game/OGame.h>
#include <filesystem>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


OTexture::OTexture(const wchar_t* path, OResourceManager* manager) :OResource(path, manager)
{
	ORect textureSize;
	auto nrChannels = 0;

	std::filesystem::path resPath = path;
	auto str = resPath.generic_string();

	unsigned char* data = stbi_load(str.c_str(), &textureSize.width, &textureSize.height, &nrChannels, 0);

	if (data)
	{
		m_texture2D = manager->getGame()->getGraphicsEngine()->createTexture2D({ data,textureSize, (ui32)nrChannels });
		if (!m_texture2D) OGL3D_ERROR("OTexture - " << path << " not generated.")
	}
	else
	{
		OGL3D_ERROR("OTexture - " << path << " not generated.")
	}

	stbi_image_free(data);
}

OTexture::~OTexture()
{
}

OTexture2DPtr OTexture::getTexture2D()
{
	return m_texture2D;
}