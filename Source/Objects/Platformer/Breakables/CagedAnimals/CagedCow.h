#pragma once

#include "Objects/Platformer/Breakables/CagedAnimals/CagedAnimal.h"

namespace cocos2d
{
	class Sprite;
};

class CagedCow : public CagedAnimal
{
public:
	static CagedCow* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyCagedCow;

protected:
	CagedCow(cocos2d::ValueMap& initProperties);
	virtual ~CagedCow();

	void initializePositions() override;

private:
	typedef CagedAnimal super;

	cocos2d::Sprite* animalSprite;
};
