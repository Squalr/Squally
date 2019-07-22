#pragma once

#include "Objects/Platformer/Breakables/CagedAnimals/CagedAnimal.h"

namespace cocos2d
{
	class Sprite;
};

class CagedGiraffe : public CagedAnimal
{
public:
	static CagedGiraffe* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyCagedGiraffe;

protected:
	CagedGiraffe(cocos2d::ValueMap& initProperties);
	virtual ~CagedGiraffe();

	void initializePositions() override;

private:
	typedef CagedAnimal super;

	cocos2d::Sprite* animalSprite;
};
