#pragma once

#include "Objects/Platformer/Breakables/CagedAnimals/CagedAnimal.h"

namespace cocos2d
{
	class Sprite;
};

class CagedPig : public CagedAnimal
{
public:
	static CagedPig* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	CagedPig(cocos2d::ValueMap& properties);
	virtual ~CagedPig();

	void initializePositions() override;

	LocalizedString* getAnimalName() override;
	std::string getSpriteResource() override;

private:
	typedef CagedAnimal super;

	cocos2d::Sprite* animalSprite;
};
