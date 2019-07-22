#pragma once

#include "Objects/Platformer/Breakables/CagedAnimals/CagedAnimal.h"

namespace cocos2d
{
	class Sprite;
};

class CagedBear : public CagedAnimal
{
public:
	static CagedBear* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyCagedBear;

protected:
	CagedBear(cocos2d::ValueMap& initProperties);
	virtual ~CagedBear();

	void initializePositions() override;

private:
	typedef CagedAnimal super;

	cocos2d::Sprite* animalSprite;
};
