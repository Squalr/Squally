#pragma once

#include "Objects/Platformer/Breakables/CagedAnimals/CagedAnimal.h"

namespace cocos2d
{
	class Sprite;
};

class CagedLion : public CagedAnimal
{
public:
	static CagedLion* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyCagedLion;

protected:
	CagedLion(cocos2d::ValueMap& initProperties);
	virtual ~CagedLion();

	void initializePositions() override;

private:
	typedef CagedAnimal super;

	cocos2d::Sprite* animalSprite;
};
