#pragma once

#include "Objects/Platformer/Breakables/CagedAnimals/CagedAnimal.h"

namespace cocos2d
{
	class Sprite;
};

class CagedKillerWhale : public CagedAnimal
{
public:
	static CagedKillerWhale* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyCagedKillerWhale;

protected:
	CagedKillerWhale(cocos2d::ValueMap& initProperties);
	virtual ~CagedKillerWhale();

	void initializePositions() override;

private:
	typedef CagedAnimal super;

	cocos2d::Sprite* animalSprite;
};
