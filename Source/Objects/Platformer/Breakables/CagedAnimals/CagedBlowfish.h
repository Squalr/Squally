#pragma once

#include "Objects/Platformer/Breakables/CagedAnimals/CagedAnimal.h"

namespace cocos2d
{
	class Sprite;
};

class CagedBlowfish : public CagedAnimal
{
public:
	static CagedBlowfish* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyCagedBlowfish;

protected:
	CagedBlowfish(cocos2d::ValueMap& properties);
	~CagedBlowfish();

	void initializePositions() override;

	LocalizedString* getAnimalName() override;
	std::string getSpriteResource() override;

private:
	typedef CagedAnimal super;

	cocos2d::Sprite* animalSprite;
};
