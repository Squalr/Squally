#include "sfmlboxinstanceinfo.h"

#include "../../spriterengine/global/settings.h"

namespace SpriterEngine
{

	SfmlBoxInstanceInfo::SfmlBoxInstanceInfo(point initialSize, sf::RenderWindow *validRenderWindow) :
		BoxInstanceInfo(initialSize),
		renderWindow(validRenderWindow),
		rectangle(sf::Vector2f(initialSize.x, initialSize.y))
	{
	}

	void SfmlBoxInstanceInfo::render()
	{
		if (Settings::renderDebugBoxes)
		{
			rectangle.setPosition(getPosition().x, getPosition().y);
			rectangle.setRotation(toDegrees(getAngle()));
			rectangle.setScale(getScale().x, getScale().y);
			rectangle.setOrigin(getPivot().x*getSize().x, getPivot().y*getSize().y);
			renderWindow->draw(rectangle);
		}
	}

}
