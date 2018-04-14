#include "CCBoneInstanceInfo.h"

#include "SpriterPlusPlus/spriterengine/global/settings.h"

NS_CC_BEGIN

	CCBoneInstanceInfo::CCBoneInstanceInfo(SpriterEngine::point initialSize, cocos2d::Node* parent) :
	SpriterEngine::BoneInstanceInfo(initialSize)
	{
//		boneShape.setPointCount(4);
//
//		boneShape.setPoint(0, sf::Vector2f(0, initialSize.y/2.0));
//		boneShape.setPoint(1, sf::Vector2f(4, 0));
//		boneShape.setPoint(2, sf::Vector2f(initialSize.x, initialSize.y/2.0));
//		boneShape.setPoint(3, sf::Vector2f(4, initialSize.y));
//
//		boneShape.setOrigin(0, initialSize.y/2.0);
//
//		boneShape.setFillColor(sf::Color(0, 0, 255, 50));
//
//		boneShape.setOutlineColor(sf::Color::White);
//		boneShape.setOutlineThickness(1);
	}

	void CCBoneInstanceInfo::render()
	{
		if (SpriterEngine::Settings::renderDebugBones)
		{
            //TODO:debug draw
//			boneShape.setPosition(getPosition().x, getPosition().y);
//			boneShape.setRotation(toDegrees(getAngle()));
//			boneShape.setScale(getScale().x, getScale().y);
//			renderWindow->draw(boneShape);
		}
	}

NS_CC_END
