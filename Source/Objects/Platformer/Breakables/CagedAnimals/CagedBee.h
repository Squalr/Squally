#pragma once

#include "Objects/Platformer/Breakables/CagedAnimals/CagedAnimal.h"

namespace cocos2d
{
	class Sprite;
};

class CagedBee : public CagedAnimal
{
public:
	static CagedBee* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyCagedBee;

protected:
	CagedBee(cocos2d::ValueMap& initProperties);
	virtual ~CagedBee();

	void initializePositions() override;

private:
	typedef CagedAnimal super;

	cocos2d::Sprite* animalSprite;
};
