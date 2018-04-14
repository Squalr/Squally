#include <sstream>
#include "CCImageFile.h"
#include "SpriterPlusPlus/spriterengine/objectinfo/universalobjectinterface.h"
#include "2d/CCSprite.h"
#include "platform/CCFileUtils.h"

namespace se = SpriterEngine;
namespace cc = cocos2d;

NS_CC_BEGIN

	CCImageFile::CCImageFile(std::string initialFilePath
                            ,se::point initialDefaultPivot
                            ,cc::Node* parent
                            ,SpriteLoader loader ) :
		se::ImageFile(initialFilePath,initialDefaultPivot), parent(parent), loader(loader)
	{
	}

    CCImageFile::~CCImageFile()
    {
        for (auto sprite: avail) {
            sprite->removeFromParentAndCleanup(true);
        }
        for (auto sprite: used) {
            sprite->removeFromParentAndCleanup(true);
        }
    }

	void CCImageFile::renderSprite(se::UniversalObjectInterface* spriteInfo)
	{
        auto sprite = nextSprite();
        sprite->setOpacity((spriteInfo->getAlpha())*255);
        sprite->setPosition(float(spriteInfo->getPosition().x), -float(spriteInfo->getPosition().y));
        sprite->setRotation(float(se::toDegrees(spriteInfo->getAngle())));
        sprite->setScale(float(spriteInfo->getScale().x), float(spriteInfo->getScale().y));
        sprite->setAnchorPoint(cc::Vec2(float(spriteInfo->getPivot().x), 1.0f - float(spriteInfo->getPivot().y)));
        sprite->setVisible(true);
	}

    cc::Sprite* CCImageFile::nextSprite()
    {
        cc::Sprite* sprite {nullptr};
        if ( avail.size() > 0 ) {
            sprite = avail.back();
            avail.pop_back();
        } else {
            sprite = loader(path());
            if (sprite)
            {
                parent->addChild(sprite);
            }
            else
            {
                CCLOGERROR("CCImageFile() - cocos sprite unable to load file from path %s",path().c_str());
            }
        }
        used.push_back(sprite);
        return sprite;
    }

    void CCImageFile::resetSprites()
    {
        for (auto sprite: used) {
            sprite->setVisible(false);
            avail.push_back(sprite);
        }
        used.clear();
    }

NS_CC_END
