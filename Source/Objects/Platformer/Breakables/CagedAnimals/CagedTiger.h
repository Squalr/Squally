#pragma once

#include "Objects/Platformer/Breakables/CagedAnimals/CagedAnimal.h"

namespace cocos2d
{
	class Sprite;
};

class CagedTiger : public CagedAnimal
{
public:
	static CagedTiger* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyCagedTiger;

protected:
	CagedTiger(cocos2d::ValueMap& initProperties);
	~CagedTiger();

	void initializePositions() override;

	LocalizedString* getAnimalName() override;
	std::string getSpriteResource() override;

private:
	typedef CagedAnimal super;

	cocos2d::Sprite* animalSprite;
};
