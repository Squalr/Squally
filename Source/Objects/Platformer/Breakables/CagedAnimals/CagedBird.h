#pragma once

#include "Objects/Platformer/Breakables/CagedAnimals/CagedAnimal.h"

namespace cocos2d
{
	class Sprite;
};

class CagedBird : public CagedAnimal
{
public:
	static CagedBird* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	CagedBird(cocos2d::ValueMap& properties);
	virtual ~CagedBird();

	void initializePositions() override;

	LocalizedString* getAnimalName() override;
	std::string getSpriteResource() override;

private:
	typedef CagedAnimal super;

	cocos2d::Sprite* animalSprite;
};
