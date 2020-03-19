#pragma once

#include "Objects/Platformer/Breakables/CagedAnimals/CagedAnimal.h"

namespace cocos2d
{
	class Sprite;
};

class CagedBunny : public CagedAnimal
{
public:
	static CagedBunny* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	CagedBunny(cocos2d::ValueMap& properties);
	virtual ~CagedBunny();

	void initializePositions() override;

	LocalizedString* getAnimalName() override;
	std::string getSpriteResource() override;

private:
	typedef CagedAnimal super;

	cocos2d::Sprite* animalSprite;
};
