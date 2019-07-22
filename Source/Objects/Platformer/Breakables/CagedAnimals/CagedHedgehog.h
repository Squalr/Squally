#pragma once

#include "Objects/Platformer/Breakables/CagedAnimals/CagedAnimal.h"

namespace cocos2d
{
	class Sprite;
};

class CagedHedgehog : public CagedAnimal
{
public:
	static CagedHedgehog* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyCagedHedgehog;

protected:
	CagedHedgehog(cocos2d::ValueMap& initProperties);
	virtual ~CagedHedgehog();

	void initializePositions() override;

private:
	typedef CagedAnimal super;

	cocos2d::Sprite* animalSprite;
};
