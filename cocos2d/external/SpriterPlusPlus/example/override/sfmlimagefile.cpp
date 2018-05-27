#include "sfmlimagefile.h"

#include "../../spriterengine/global/settings.h"

#include "../../spriterengine/objectinfo/universalobjectinterface.h"

#include "sfmlatlasfile.h"

namespace SpriterEngine
{

	SfmlImageFile::SfmlImageFile(std::string initialFilePath, point initialDefaultPivot, sf::RenderWindow *validRenderWindow) :
		ImageFile(initialFilePath,initialDefaultPivot),
		renderWindow(validRenderWindow)
	{
		initializeFile();
	}

	void SfmlImageFile::initializeFile()
	{
		if (texture.loadFromFile(path()))
		{
			// texture.setSmooth(true);
			sprite.setTexture(texture);
		}
		else
		{
			Settings::Settings::error("SfmlImageFile::initializeFile - sfml texture unable to load file from path \"" + path() + "\"");
		}
	}

	void SfmlImageFile::renderSprite(UniversalObjectInterface * spriteInfo)
	{
		sprite.setColor(sf::Color(255, 255, 255, 255 * spriteInfo->getAlpha()));

		if(atlasFile) {
			// Adding of transformations is in the reverse order you would expect.
			sf::Transform t;
			if(atlasFrameData.rotated) {
				t.translate(spriteInfo->getPosition().x, spriteInfo->getPosition().y);
				t.rotate(toDegrees(spriteInfo->getAngle()));
				t.scale(spriteInfo->getScale().x, spriteInfo->getScale().y);
				t.translate(-spriteInfo->getPivot().x * atlasFrameData.sourceSize.x, -spriteInfo->getPivot().y * atlasFrameData.sourceSize.y);
				// Turn it because the image is rotated
				t.rotate(-90);
				// Translate the cutoff in atlas (spriteSourcePosition is the position of the atlas in the original == offset)
				// X and Y swapped
				// Also translate it the height (sourceSize.y) up so that the left-up corner of the original image is at the x0 y0.
				t.translate(atlasFrameData.spriteSourcePosition.y - atlasFrameData.sourceSize.y, atlasFrameData.spriteSourcePosition.x);
			}
			else {
				t.translate(spriteInfo->getPosition().x, spriteInfo->getPosition().y);
				t.rotate(toDegrees(spriteInfo->getAngle()));
				t.scale(spriteInfo->getScale().x, spriteInfo->getScale().y);
				// Translate the cutoff in atlas (spriteSourcePosition is the position of the atlas in the original == offset)
				// Also translate the pivot at onces (saves an extra instruction)
				t.translate(atlasFrameData.spriteSourcePosition.x - spriteInfo->getPivot().x * atlasFrameData.sourceSize.x,
							atlasFrameData.spriteSourcePosition.y - spriteInfo->getPivot().y * atlasFrameData.sourceSize.y);
			}
			renderWindow->draw(sprite, t);
		}
		else {
			sprite.setPosition(spriteInfo->getPosition().x, spriteInfo->getPosition().y);
			sprite.setRotation(toDegrees(spriteInfo->getAngle()));
			sprite.setScale(spriteInfo->getScale().x, spriteInfo->getScale().y);
			sprite.setOrigin(spriteInfo->getPivot().x*texture.getSize().x, spriteInfo->getPivot().y*texture.getSize().y);
			renderWindow->draw(sprite);
		}
	}

	// Overwritten so we can create the sprite from the texture.
	void SfmlImageFile::setAtlasFile(AtlasFile *initialAtlasFile, atlasframedata initialAtlasFrameData) {
		// First call baseclass implementation
		ImageFile::setAtlasFile(initialAtlasFile, initialAtlasFrameData);

		// atlasFile should be a SfmlAtlasFile
		if(atlasFile && static_cast<SfmlAtlasFile*>(atlasFile)->loaded()) {
			const sf::Texture *texture = static_cast<SfmlAtlasFile*>(atlasFile)->getTexture();
			sprite.setTexture(*texture);
			if(atlasFrameData.rotated) {
				// When rotated, the atlasdata framesize are relative to the original. Not the frame
				sprite.setTextureRect(sf::IntRect(atlasFrameData.framePosition.x, atlasFrameData.framePosition.y,
												  atlasFrameData.frameSize.y, atlasFrameData.frameSize.x));
			}
			else {
				sprite.setTextureRect(sf::IntRect(atlasFrameData.framePosition.x, atlasFrameData.framePosition.y,
												  atlasFrameData.frameSize.x, atlasFrameData.frameSize.y));
			}
		}
	}
}
