#pragma once

#include "Objects/Platformer/Breakables/CagedAnimals/CagedAnimal.h"

namespace cocos2d
{
	class Sprite;
};

class CagedSkunk : public CagedAnimal
{
public:
	static CagedSkunk* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyCagedSkunk;

protected:
	CagedSkunk(cocos2d::ValueMap& properties);
	~CagedSkunk();

	void initializePositions() override;

	LocalizedString* getAnimalName() override;
	std::string getSpriteResource() override;

private:
	typedef CagedAnimal super;

	cocos2d::Sprite* animalSprite;
};
