#ifndef SFMLIMAGEFILE_H
#define SFMLIMAGEFILE_H

#include "../../spriterengine/override/imagefile.h"

#include <SFML/Graphics.hpp>

namespace SpriterEngine
{
	class SfmlImageFile : public ImageFile
	{
	public:
		SfmlImageFile(std::string initialFilePath, point initialDefaultPivot, sf::RenderWindow *validRenderWindow);

		void renderSprite(UniversalObjectInterface *spriteInfo) override;

		void setAtlasFile(AtlasFile *initialAtlasFile, atlasframedata initialAtlasFrameData) override;

	private:
		sf::Texture texture;
		sf::Sprite sprite;

		sf::RenderWindow *renderWindow;

		void initializeFile();
	};

}

#endif // SFMLIMAGEFILE_H
