#pragma once

#include "Objects/Platformer/Breakables/CagedAnimals/CagedAnimal.h"

namespace cocos2d
{
	class Sprite;
};

class CagedBird : public CagedAnimal
{
public:
	static CagedBird* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyCagedBird;

protected:
	CagedBird(cocos2d::ValueMap& initProperties);
	virtual ~CagedBird();

	void initializePositions() override;

private:
	typedef CagedAnimal super;

	cocos2d::Sprite* animalSprite;
};
