#pragma once

#include "Objects/Platformer/Breakables/CagedAnimals/CagedAnimal.h"

namespace cocos2d
{
	class Sprite;
};

class CagedPanda : public CagedAnimal
{
public:
	static CagedPanda* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyCagedPanda;

protected:
	CagedPanda(cocos2d::ValueMap& initProperties);
	virtual ~CagedPanda();

	void initializePositions() override;

private:
	typedef CagedAnimal super;

	cocos2d::Sprite* animalSprite;
};
