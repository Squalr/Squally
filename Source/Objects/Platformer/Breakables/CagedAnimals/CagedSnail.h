#pragma once

#include "Objects/Platformer/Breakables/CagedAnimals/CagedAnimal.h"

namespace cocos2d
{
	class Sprite;
};

class CagedSnail : public CagedAnimal
{
public:
	static CagedSnail* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	CagedSnail(cocos2d::ValueMap& properties);
	virtual ~CagedSnail();

	void initializePositions() override;

	LocalizedString* getAnimalName() override;
	std::string getSpriteResource() override;

private:
	typedef CagedAnimal super;

	cocos2d::Sprite* animalSprite;
};
