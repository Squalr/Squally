#ifndef EXAMPLEOBJECTFACTORY_H
#define EXAMPLEOBJECTFACTORY_H

#include "SFML/Graphics/RenderWindow.hpp"

#include "../../spriterengine/override/SPPobjectfactory.h"

namespace SpriterEngine
{

	class ExampleObjectFactory : public ObjectFactory
	{
	public:
		ExampleObjectFactory(sf::RenderWindow *validRenderWindow);
		
		PointInstanceInfo *newPointInstanceInfo() override;

		BoxInstanceInfo *newBoxInstanceInfo(point size) override;

		BoneInstanceInfo *newBoneInstanceInfo(point size) override;

	private:
		sf::RenderWindow *renderWindow;
	};

}

#endif // EXAMPLEOBJECTFACTORY_H
