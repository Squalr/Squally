#pragma once

#include "Objects/Platformer/Breakables/CagedAnimals/CagedAnimal.h"

namespace cocos2d
{
	class Sprite;
};

class CagedPig : public CagedAnimal
{
public:
	static CagedPig* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyCagedPig;

protected:
	CagedPig(cocos2d::ValueMap& initProperties);
	virtual ~CagedPig();

	void initializePositions() override;

private:
	typedef CagedAnimal super;

	cocos2d::Sprite* animalSprite;
};
