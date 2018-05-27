#ifndef SFMLATLASFILE_H
#define SFMLATLASFILE_H

#include "../../spriterengine/override/atlasfile.h"

#include <SFML/Graphics.hpp>

namespace SpriterEngine
{
	class SfmlAtlasFile : public AtlasFile
	{
	public:
		SfmlAtlasFile(std::string initialFilePath);

		const sf::Texture *getTexture() const;

		bool loaded() {return m_loaded;}

	private:
		sf::Texture texture;

		void initializeFile();

		void renderSprite(UniversalObjectInterface *spriteInfo, const atlasframedata data) override;

		bool m_loaded;
	};

}

#endif // SFMLATLASFILE_H
