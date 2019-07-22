#pragma once

#include "Objects/Platformer/Breakables/CagedAnimals/CagedAnimal.h"

namespace cocos2d
{
	class Sprite;
};

class CagedSnake : public CagedAnimal
{
public:
	static CagedSnake* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyCagedSnake;

protected:
	CagedSnake(cocos2d::ValueMap& initProperties);
	virtual ~CagedSnake();

	void initializePositions() override;

private:
	typedef CagedAnimal super;

	cocos2d::Sprite* animalSprite;
};
