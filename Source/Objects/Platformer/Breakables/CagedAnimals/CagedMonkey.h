#pragma once

#include "Objects/Platformer/Breakables/CagedAnimals/CagedAnimal.h"

namespace cocos2d
{
	class Sprite;
};

class CagedMonkey : public CagedAnimal
{
public:
	static CagedMonkey* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyCagedMonkey;

protected:
	CagedMonkey(cocos2d::ValueMap& initProperties);
	~CagedMonkey();

	void initializePositions() override;

	LocalizedString* getAnimalName() override;
	std::string getSpriteResource() override;

private:
	typedef CagedAnimal super;

	cocos2d::Sprite* animalSprite;
};
