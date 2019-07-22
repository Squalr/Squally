#pragma once

#include "Objects/Platformer/Breakables/CagedAnimals/CagedAnimal.h"

namespace cocos2d
{
	class Sprite;
};

class CagedRhino : public CagedAnimal
{
public:
	static CagedRhino* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyCagedRhino;

protected:
	CagedRhino(cocos2d::ValueMap& initProperties);
	virtual ~CagedRhino();

	void initializePositions() override;

private:
	typedef CagedAnimal super;

	cocos2d::Sprite* animalSprite;
};
