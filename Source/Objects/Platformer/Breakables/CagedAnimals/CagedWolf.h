#pragma once

#include "Objects/Platformer/Breakables/CagedAnimals/CagedAnimal.h"

namespace cocos2d
{
	class Sprite;
};

class CagedWolf : public CagedAnimal
{
public:
	static CagedWolf* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyCagedWolf;

protected:
	CagedWolf(cocos2d::ValueMap& initProperties);
	virtual ~CagedWolf();

	void initializePositions() override;

private:
	typedef CagedAnimal super;

	cocos2d::Sprite* animalSprite;
};
