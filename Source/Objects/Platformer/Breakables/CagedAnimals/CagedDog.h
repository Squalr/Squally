#pragma once

#include "Objects/Platformer/Breakables/CagedAnimals/CagedAnimal.h"

namespace cocos2d
{
	class Sprite;
};

class CagedDog : public CagedAnimal
{
public:
	static CagedDog* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyCagedDog;

protected:
	CagedDog(cocos2d::ValueMap& initProperties);
	virtual ~CagedDog();

	void initializePositions() override;

private:
	typedef CagedAnimal super;

	cocos2d::Sprite* animalSprite;
};
