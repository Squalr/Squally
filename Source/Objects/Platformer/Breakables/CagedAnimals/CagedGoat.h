#pragma once

#include "Objects/Platformer/Breakables/CagedAnimals/CagedAnimal.h"

namespace cocos2d
{
	class Sprite;
};

class CagedGoat : public CagedAnimal
{
public:
	static CagedGoat* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyCagedGoat;

protected:
	CagedGoat(cocos2d::ValueMap& initProperties);
	virtual ~CagedGoat();

	void initializePositions() override;

private:
	typedef CagedAnimal super;

	cocos2d::Sprite* animalSprite;
};
