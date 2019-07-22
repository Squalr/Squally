#pragma once

#include "Objects/Platformer/Breakables/CagedAnimals/CagedAnimal.h"

namespace cocos2d
{
	class Sprite;
};

class CagedZebra : public CagedAnimal
{
public:
	static CagedZebra* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyCagedZebra;

protected:
	CagedZebra(cocos2d::ValueMap& initProperties);
	virtual ~CagedZebra();

	void initializePositions() override;

private:
	typedef CagedAnimal super;

	cocos2d::Sprite* animalSprite;
};
