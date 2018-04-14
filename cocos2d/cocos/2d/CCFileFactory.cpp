#include "CCFileFactory.h"

#include "TinyXmlSpriterFileDocumentWrapper.h"

#include "CCImageFile.h"
#include "CCSoundFile.h"
#include "2d/CCNode.h"

NS_CC_BEGIN

	class CCFileFactory::impl
	{
	public:
		impl(cocos2d::Node* parent, SpriteLoader loader) : parent(parent), loader(loader) {}

		~impl() {}

		SpriterEngine::ImageFile* newImageFile(const std::string&initialFilePath, SpriterEngine::point initialDefaultPivot)
		{
			auto file = new CCImageFile(initialFilePath, initialDefaultPivot, parent, loader);
			images.push_back(file);
			return file;
		}

		void resetSprites()
		{
			for (auto file: images) {
				file->resetSprites();
			}
		}

	private:
		SpriteLoader loader;
		cocos2d::Node* parent;
		std::vector<CCImageFile*> images;
	};

	CCFileFactory::CCFileFactory(cocos2d::Node* parent, SpriteLoader loader)
			: self(new CCFileFactory::impl(parent, loader)) {}

	CCFileFactory::~CCFileFactory() { }

	SpriterEngine::ImageFile* CCFileFactory::newImageFile(const std::string&initialFilePath, SpriterEngine::point initialDefaultPivot, SpriterEngine::atlasdata atlasData)
	{
		return self->newImageFile(initialFilePath, initialDefaultPivot);
	}

	SpriterEngine::SoundFile* CCFileFactory::newSoundFile(const std::string& initialFilePath)
	{
		return new CCSoundFile(initialFilePath);
	}

	SpriterEngine::SpriterFileDocumentWrapper* CCFileFactory::newScmlDocumentWrapper()
	{
		return new cocos2d::TinyXmlSpriterFileDocumentWrapper();
	}

	void CCFileFactory::resetSprites()
	{
		self->resetSprites();
	}

NS_CC_END
