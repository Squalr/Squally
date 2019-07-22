#pragma once

#include "Objects/Platformer/Breakables/CagedAnimals/CagedAnimal.h"

namespace cocos2d
{
	class Sprite;
};

class CagedDuck : public CagedAnimal
{
public:
	static CagedDuck* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyCagedDuck;

protected:
	CagedDuck(cocos2d::ValueMap& initProperties);
	virtual ~CagedDuck();

	void initializePositions() override;

private:
	typedef CagedAnimal super;

	cocos2d::Sprite* animalSprite;
};
