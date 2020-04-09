#pragma once

#include "Objects/Platformer/Breakables/CagedAnimals/CagedAnimal.h"

namespace cocos2d
{
	class Sprite;
};

class CagedRaccoon : public CagedAnimal
{
public:
	static CagedRaccoon* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	CagedRaccoon(cocos2d::ValueMap& properties);
	virtual ~CagedRaccoon();

	void initializePositions() override;

	LocalizedString* getAnimalName() override;
	std::string getSpriteResource() override;

private:
	typedef CagedAnimal super;

	cocos2d::Sprite* animalSprite;
};
