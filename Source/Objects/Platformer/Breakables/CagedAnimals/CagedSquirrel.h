#pragma once

#include "Objects/Platformer/Breakables/CagedAnimals/CagedAnimal.h"

namespace cocos2d
{
	class Sprite;
};

class CagedSquirrel : public CagedAnimal
{
public:
	static CagedSquirrel* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	CagedSquirrel(cocos2d::ValueMap& properties);
	virtual ~CagedSquirrel();

	void initializePositions() override;

	LocalizedString* getAnimalName() override;
	std::string getSpriteResource() override;

private:
	typedef CagedAnimal super;

	cocos2d::Sprite* animalSprite;
};
