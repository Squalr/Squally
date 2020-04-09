#pragma once

#include "Objects/Platformer/Breakables/CagedAnimals/CagedAnimal.h"

namespace cocos2d
{
	class Sprite;
};

class CagedDuck : public CagedAnimal
{
public:
	static CagedDuck* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	CagedDuck(cocos2d::ValueMap& properties);
	virtual ~CagedDuck();

	void initializePositions() override;

	LocalizedString* getAnimalName() override;
	std::string getSpriteResource() override;

private:
	typedef CagedAnimal super;

	cocos2d::Sprite* animalSprite;
};
