#pragma once

#include "Objects/Platformer/Breakables/CagedAnimals/CagedAnimal.h"

namespace cocos2d
{
	class Sprite;
};

class CagedDog : public CagedAnimal
{
public:
	static CagedDog* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyCagedDog;

protected:
	CagedDog(cocos2d::ValueMap& properties);
	~CagedDog();

	void initializePositions() override;

	LocalizedString* getAnimalName() override;
	std::string getSpriteResource() override;

private:
	typedef CagedAnimal super;

	cocos2d::Sprite* animalSprite;
};
