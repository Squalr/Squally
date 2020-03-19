#pragma once

#include "Objects/Platformer/Breakables/CagedAnimals/CagedAnimal.h"

namespace cocos2d
{
	class Sprite;
};

class CagedKoala : public CagedAnimal
{
public:
	static CagedKoala* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	CagedKoala(cocos2d::ValueMap& properties);
	virtual ~CagedKoala();

	void initializePositions() override;

	LocalizedString* getAnimalName() override;
	std::string getSpriteResource() override;

private:
	typedef CagedAnimal super;

	cocos2d::Sprite* animalSprite;
};
