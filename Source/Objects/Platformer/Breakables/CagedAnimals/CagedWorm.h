#pragma once

#include "Objects/Platformer/Breakables/CagedAnimals/CagedAnimal.h"

namespace cocos2d
{
	class Sprite;
};

class CagedWorm : public CagedAnimal
{
public:
	static CagedWorm* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyCagedWorm;

protected:
	CagedWorm(cocos2d::ValueMap& initProperties);
	~CagedWorm();

	void initializePositions() override;

	LocalizedString* getAnimalName() override;
	std::string getSpriteResource() override;

private:
	typedef CagedAnimal super;

	cocos2d::Sprite* animalSprite;
};
