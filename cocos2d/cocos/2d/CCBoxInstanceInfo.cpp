#include "CCBoxInstanceInfo.h"

#include "SpriterPlusPlus/spriterengine/global/settings.h"

NS_CC_BEGIN

	CCBoxInstanceInfo::CCBoxInstanceInfo(SpriterEngine::point initialSize) :
		SpriterEngine::BoxInstanceInfo(initialSize)
	{
	}

	void CCBoxInstanceInfo::render()
	{
		if (SpriterEngine::Settings::renderDebugBoxes)
		{
            //TODO: debug draw
//			rectangle.setPosition(getPosition().x, getPosition().y);
//			rectangle.setRotation(toDegrees(getAngle()));
//			rectangle.setScale(getScale().x, getScale().y);
//			rectangle.setOrigin(getPivot().x*getSize().x, getPivot().y*getSize().y);
//			renderWindow->draw(rectangle);
		}
	}

NS_CC_END
