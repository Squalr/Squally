#pragma once

#include "Objects/Platformer/Breakables/CagedAnimals/CagedAnimal.h"

namespace cocos2d
{
	class Sprite;
};

class CagedSheep : public CagedAnimal
{
public:
	static CagedSheep* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyCagedSheep;

protected:
	CagedSheep(cocos2d::ValueMap& initProperties);
	~CagedSheep();

	void initializePositions() override;

	LocalizedString* getAnimalName() override;
	std::string getSpriteResource() override;

private:
	typedef CagedAnimal super;

	cocos2d::Sprite* animalSprite;
};
