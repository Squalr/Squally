#pragma once

#include "Objects/Platformer/Breakables/CagedAnimals/CagedAnimal.h"

namespace cocos2d
{
	class Sprite;
};

class CagedDinosaur : public CagedAnimal
{
public:
	static CagedDinosaur* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	CagedDinosaur(cocos2d::ValueMap& properties);
	virtual ~CagedDinosaur();

	void initializePositions() override;

	LocalizedString* getAnimalName() override;
	std::string getSpriteResource() override;

private:
	typedef CagedAnimal super;

	cocos2d::Sprite* animalSprite;
};
