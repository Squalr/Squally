#pragma once

#include "Objects/Platformer/Breakables/CagedAnimals/CagedAnimal.h"

namespace cocos2d
{
	class Sprite;
};

class CagedKoala : public CagedAnimal
{
public:
	static CagedKoala* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyCagedKoala;

protected:
	CagedKoala(cocos2d::ValueMap& initProperties);
	virtual ~CagedKoala();

	void initializePositions() override;

private:
	typedef CagedAnimal super;

	cocos2d::Sprite* animalSprite;
};
