#pragma once

#include "Objects/Platformer/Breakables/CagedAnimals/CagedAnimal.h"

namespace cocos2d
{
	class Sprite;
};

class CagedCat : public CagedAnimal
{
public:
	static CagedCat* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyCagedCat;

protected:
	CagedCat(cocos2d::ValueMap& properties);
	~CagedCat();

	void initializePositions() override;

	LocalizedString* getAnimalName() override;
	std::string getSpriteResource() override;

private:
	typedef CagedAnimal super;

	cocos2d::Sprite* animalSprite;
};
