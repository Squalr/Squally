#ifndef SPRITER2DX_IMAGEFILE_H
#define SPRITER2DX_IMAGEFILE_H

#include <vector>
#include <functional>
#include "2d/CCNode.h"
#include "2d/CCSprite.h"
#include "SpriterPlusPlus/spriterengine/override/imagefile.h"

NS_CC_BEGIN


    typedef std::vector<cocos2d::Sprite*> SpriteList;
    typedef std::function<cocos2d::Sprite*(const std::string&)> SpriteLoader;

	class CC_DLL CCImageFile : public SpriterEngine::ImageFile
	{
	public:
        CCImageFile(std::string initialFilePath
                   ,SpriterEngine::point initialDefaultPivot
				   ,cocos2d::Node* parent
                   ,SpriteLoader loader);
        ~CCImageFile();

		void renderSprite(SpriterEngine::UniversalObjectInterface *spriteInfo) override;
        void resetSprites();


	private:
        SpriteLoader loader;
        cocos2d::Sprite* nextSprite();

        cocos2d::Node* parent;
        SpriteList avail;
        SpriteList used;
	};

NS_CC_END

#endif // SPRITER2DX_IMAGEFILE_H
