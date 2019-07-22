#pragma once

#include "Objects/Platformer/Breakables/CagedAnimals/CagedAnimal.h"

namespace cocos2d
{
	class Sprite;
};

class CagedTurtle : public CagedAnimal
{
public:
	static CagedTurtle* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyCagedTurtle;

protected:
	CagedTurtle(cocos2d::ValueMap& initProperties);
	virtual ~CagedTurtle();

	void initializePositions() override;

private:
	typedef CagedAnimal super;

	cocos2d::Sprite* animalSprite;
};
