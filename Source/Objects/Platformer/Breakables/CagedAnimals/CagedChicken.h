#pragma once

#include "Objects/Platformer/Breakables/CagedAnimals/CagedAnimal.h"

namespace cocos2d
{
	class Sprite;
};

class CagedChicken : public CagedAnimal
{
public:
	static CagedChicken* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyCagedChicken;

protected:
	CagedChicken(cocos2d::ValueMap& initProperties);
	~CagedChicken();

	void initializePositions() override;

	LocalizedString* getAnimalName() override;
	std::string getSpriteResource() override;

private:
	typedef CagedAnimal super;

	cocos2d::Sprite* animalSprite;
};
