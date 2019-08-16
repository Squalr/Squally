#pragma once

#include "Objects/Platformer/Breakables/CagedAnimals/CagedAnimal.h"

namespace cocos2d
{
	class Sprite;
};

class CagedMountainLion : public CagedAnimal
{
public:
	static CagedMountainLion* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyCagedMountainLion;

protected:
	CagedMountainLion(cocos2d::ValueMap& properties);
	virtual ~CagedMountainLion();

	void initializePositions() override;

	LocalizedString* getAnimalName() override;
	std::string getSpriteResource() override;

private:
	typedef CagedAnimal super;

	cocos2d::Sprite* animalSprite;
};
