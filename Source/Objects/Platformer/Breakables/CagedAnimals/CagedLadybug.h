#pragma once

#include "Objects/Platformer/Breakables/CagedAnimals/CagedAnimal.h"

namespace cocos2d
{
	class Sprite;
};

class CagedLadybug : public CagedAnimal
{
public:
	static CagedLadybug* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyCagedLadybug;

protected:
	CagedLadybug(cocos2d::ValueMap& initProperties);
	virtual ~CagedLadybug();

	void initializePositions() override;

private:
	typedef CagedAnimal super;

	cocos2d::Sprite* animalSprite;
};
