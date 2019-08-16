#pragma once

#include "Objects/Platformer/Breakables/CagedAnimals/CagedAnimal.h"

namespace cocos2d
{
	class Sprite;
};

class CagedPenguin : public CagedAnimal
{
public:
	static CagedPenguin* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyCagedPenguin;

protected:
	CagedPenguin(cocos2d::ValueMap& properties);
	~CagedPenguin();

	void initializePositions() override;

	LocalizedString* getAnimalName() override;
	std::string getSpriteResource() override;

private:
	typedef CagedAnimal super;

	cocos2d::Sprite* animalSprite;
};
