#pragma once

#include "Objects/Platformer/Breakables/CagedAnimals/CagedAnimal.h"

namespace cocos2d
{
	class Sprite;
};

class CagedDinosaur : public CagedAnimal
{
public:
	static CagedDinosaur* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyCagedDinosaur;

protected:
	CagedDinosaur(cocos2d::ValueMap& initProperties);
	virtual ~CagedDinosaur();

	void initializePositions() override;

private:
	typedef CagedAnimal super;

	cocos2d::Sprite* animalSprite;
};
