#pragma once

#include "Objects/Platformer/Breakables/CagedAnimals/CagedAnimal.h"

namespace cocos2d
{
	class Sprite;
};

class CagedSquid : public CagedAnimal
{
public:
	static CagedSquid* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyCagedSquid;

protected:
	CagedSquid(cocos2d::ValueMap& properties);
	~CagedSquid();

	void initializePositions() override;

	LocalizedString* getAnimalName() override;
	std::string getSpriteResource() override;

private:
	typedef CagedAnimal super;

	cocos2d::Sprite* animalSprite;
};
