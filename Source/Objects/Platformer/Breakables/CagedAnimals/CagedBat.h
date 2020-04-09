#pragma once

#include "Objects/Platformer/Breakables/CagedAnimals/CagedAnimal.h"

namespace cocos2d
{
	class Sprite;
};

class CagedBat : public CagedAnimal
{
public:
	static CagedBat* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	CagedBat(cocos2d::ValueMap& properties);
	virtual ~CagedBat();

	void initializePositions() override;

	LocalizedString* getAnimalName() override;
	std::string getSpriteResource() override;

private:
	typedef CagedAnimal super;

	cocos2d::Sprite* animalSprite;
};
