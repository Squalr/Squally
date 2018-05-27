#ifndef SFMLPOINTINSTANCEINFO_H
#define SFMLPOINTINSTANCEINFO_H

#include "SFML/Graphics/RenderWindow.hpp"

#include "SFML/Graphics/CircleShape.hpp"

#include "../../spriterengine/objectinfo/pointinstanceinfo.h"

namespace SpriterEngine
{

	class SfmlPointInstanceInfo : public PointInstanceInfo
	{
	public:
		SfmlPointInstanceInfo(sf::RenderWindow *validRenderWindow);

		void render() override;

	private:
		sf::RenderWindow *renderWindow;

		sf::CircleShape circle;
	};

}

#endif // SFMLPOINTINSTANCEINFO_H
