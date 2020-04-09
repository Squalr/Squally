#pragma once

#include "Objects/Platformer/Breakables/CagedAnimals/CagedAnimal.h"

namespace cocos2d
{
	class Sprite;
};

class CagedBear : public CagedAnimal
{
public:
	static CagedBear* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	CagedBear(cocos2d::ValueMap& properties);
	virtual ~CagedBear();

	void initializePositions() override;

	LocalizedString* getAnimalName() override;
	std::string getSpriteResource() override;

private:
	typedef CagedAnimal super;

	cocos2d::Sprite* animalSprite;
};
