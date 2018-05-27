#include <SFML/Graphics.hpp>

// overridden factories to create our special Sfml and TinyXml based objects
#include "override/exampleobjectfactory.h"
#include "override/examplefilefactory.h"

// include to use Spriter animations
#include "../spriterengine/spriterengine.h"
#include "../spriterengine/global/settings.h"

int main()
{
	SpriterEngine::Settings::setErrorFunction(SpriterEngine::Settings::simpleError);

	// setup Sfml Render Window
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML Spriter Test");


	// setup a clock and a counter for fps
	int fpsCount = 0;
	sf::Clock fpsTimer;


	// setup text objects for fps and object count
	sf::Text fpsText;
	sf::Text objectCountText;
	sf::Font font;

	font.loadFromFile("./PT-Sans/PTC55F.ttf");
	fpsText.setFont(font);
	objectCountText.setFont(font);

	fpsText.setColor(sf::Color::Red);
	fpsText.setCharacterSize(20);
	fpsText.setPosition(50, 50);

	objectCountText.setColor(sf::Color::Red);
	objectCountText.setCharacterSize(20);
	objectCountText.setPosition(50, 80);



	// load Spriter file into SpriterModel object using our custom factories
	SpriterEngine::SpriterModel scmlModel("./GreyGuy/player.scml", new SpriterEngine::ExampleFileFactory(&window), new SpriterEngine::ExampleObjectFactory(&window));
	//SpriterEngine::SpriterModel scmlModel("./GreyGuy/player.scon", new SpriterEngine::ExampleFileFactory(&window), new SpriterEngine::ExampleObjectFactory(&window));
	//SpriterEngine::SpriterModel scmlModel("./GreyGuyAtlas/GreyGuy.scml", new SpriterEngine::ExampleFileFactory(&window), new SpriterEngine::ExampleObjectFactory(&window));

	// create an array to hold instances of our character
	std::vector<SpriterEngine::EntityInstance*> instances;

	// create a timer to run our animations
	sf::Clock spriterAnimTimer;
	
	while (window.isOpen())
	{

		// if window is closed delete everything and exit
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				for (auto& inst : instances)
				{
					delete inst;
				}

				window.close();
				return 0;
			}
		}
		

		// add more instances until there are 100
		if (instances.size()<100)
		{
			// create an instance of the entity named "Player"
			instances.push_back(scmlModel.getNewEntityInstance("Player"));
			SpriterEngine::EntityInstance *inst = instances.back();

			if (inst)
			{
				// set the instance's animation to "walk"
				inst->setCurrentAnimation("walk");

				// set the instance's scale, position, and angle to something random
				SpriterEngine::real scale = ((rand() % 1500) + 500) / 1000.0;
				inst->setScale(SpriterEngine::point(scale, scale));

				inst->setPosition(SpriterEngine::point(rand() % window.getSize().x, rand() % window.getSize().y));

				inst->setAngle(SpriterEngine::toRadians(rand() % 360));
			}

			// update the object count text with the total number of instances
			objectCountText.setString("object count:  " + std::to_string(instances.size()));
		}

		// update the fps text every second
		if (fpsTimer.getElapsedTime().asSeconds() >= 1)
		{
			fpsText.setString("fps:  " + std::to_string(fpsCount));

			fpsTimer.restart();
			fpsCount = 0;
		}
		++fpsCount;


		// clear sfml window
		window.clear();



		// update all instances
		float timeElapsed = spriterAnimTimer.restart().asSeconds() * 1000;
		for (auto& it : instances)
		{
			if (it)
			{
				// tell the instance how much time has elapsed
				it->setTimeElapsed(timeElapsed);
				it->render();
				// it->playSoundTriggers();
			}
		}		

		// render our text
		window.draw(fpsText);
		window.draw(objectCountText);


		// update the sfml window 
		window.display();
	}

	for (auto& it : instances)
	{
		delete it;
	}

	return 0;
}


