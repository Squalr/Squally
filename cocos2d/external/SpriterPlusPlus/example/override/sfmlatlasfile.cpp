#include "sfmlatlasfile.h"

#include "../../spriterengine/global/settings.h"

namespace SpriterEngine
{

	SfmlAtlasFile::SfmlAtlasFile(std::string initialFilePath) :
		AtlasFile(initialFilePath), m_loaded(false)
	{
		initializeFile();
	}

	const sf::Texture* SfmlAtlasFile::getTexture() const
	{
		return &texture;
	}

	void SfmlAtlasFile::initializeFile()
	{
		if (texture.loadFromFile(path()))
		{
			m_loaded = true;
		}
		else
		{
			m_loaded = false;
			Settings::Settings::error("SfmlAtlasFile::initializeFile - sfml texture unable to load file from path \"" + path() + "\"");
		}
	}

	void SfmlAtlasFile::renderSprite(UniversalObjectInterface *spriteInfo, const atlasframedata data)
	{
	}

}
