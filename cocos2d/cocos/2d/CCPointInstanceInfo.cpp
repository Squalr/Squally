#include "CCPointInstanceInfo.h"
#include "SpriterPlusPlus/spriterengine/global/settings.h"

NS_CC_BEGIN

	CCPointInstanceInfo::CCPointInstanceInfo(cocos2d::Node* parent) : parent(parent)
	{
		//circle(10)
//		circle.setFillColor(sf::Color::Red);
//		circle.setOrigin(5, 5);
	}

	void CCPointInstanceInfo::render()
	{
		if (SpriterEngine::Settings::renderDebugPoints)
		{
//			circle.setPosition(getPosition().x, getPosition().y);
//			circle.setRotation(toDegrees(getAngle()));
//			renderWindow->draw(circle);
		}
	}

NS_CC_END
