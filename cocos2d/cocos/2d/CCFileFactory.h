#ifndef CCFILEFACTORY_H
#define CCFILEFACTORY_H

#include <memory>
#include "2d/CCNode.h"
#include "SpriterPlusPlus/spriterengine/override/filefactory.h"
#include "CCImageFile.h"

NS_CC_BEGIN

	class CC_DLL CCFileFactory : public SpriterEngine::FileFactory
	{
	public:
		CCFileFactory(cocos2d::Node* parent, SpriteLoader loader);
		~CCFileFactory();
		
		SpriterEngine::ImageFile *newImageFile(const std::string& initialFilePath, SpriterEngine::point initialDefaultPivot, SpriterEngine::atlasdata atlasData) override;

		SpriterEngine::SoundFile *newSoundFile(const std::string& initialFilePath) override;

		SpriterEngine::SpriterFileDocumentWrapper *newScmlDocumentWrapper() override;

		/**
		 * After each render cycle, this method must be called to hide
		 * all the Cocos2d Sprites in use and mark them available in the pools
		 * maintained in each CCImageFile.
		 * @memberof CCFileFactory
		 */
		void resetSprites();

	private:
		class impl;
		std::unique_ptr<impl> self;
	};

NS_CC_END

#endif // CCFILEFACTORY_H
