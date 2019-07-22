#pragma once

#include "Objects/Platformer/Breakables/CagedAnimals/CagedAnimal.h"

namespace cocos2d
{
	class Sprite;
};

class CagedSnail : public CagedAnimal
{
public:
	static CagedSnail* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyCagedSnail;

protected:
	CagedSnail(cocos2d::ValueMap& initProperties);
	virtual ~CagedSnail();

	void initializePositions() override;

private:
	typedef CagedAnimal super;

	cocos2d::Sprite* animalSprite;
};
