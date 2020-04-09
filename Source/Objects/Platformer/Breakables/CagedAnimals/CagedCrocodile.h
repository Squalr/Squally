#pragma once

#include "Objects/Platformer/Breakables/CagedAnimals/CagedAnimal.h"

namespace cocos2d
{
	class Sprite;
};

class CagedCrocodile : public CagedAnimal
{
public:
	static CagedCrocodile* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	CagedCrocodile(cocos2d::ValueMap& properties);
	virtual ~CagedCrocodile();

	void initializePositions() override;

	LocalizedString* getAnimalName() override;
	std::string getSpriteResource() override;

private:
	typedef CagedAnimal super;

	cocos2d::Sprite* animalSprite;
};
