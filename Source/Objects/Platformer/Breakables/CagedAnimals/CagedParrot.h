#pragma once

#include "Objects/Platformer/Breakables/CagedAnimals/CagedAnimal.h"

namespace cocos2d
{
	class Sprite;
};

class CagedParrot : public CagedAnimal
{
public:
	static CagedParrot* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyCagedParrot;

protected:
	CagedParrot(cocos2d::ValueMap& properties);
	~CagedParrot();

	void initializePositions() override;

	LocalizedString* getAnimalName() override;
	std::string getSpriteResource() override;

private:
	typedef CagedAnimal super;

	cocos2d::Sprite* animalSprite;
};
