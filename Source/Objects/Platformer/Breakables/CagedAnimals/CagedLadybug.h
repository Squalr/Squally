#pragma once

#include "Objects/Platformer/Breakables/CagedAnimals/CagedAnimal.h"

namespace cocos2d
{
	class Sprite;
};

class CagedLadybug : public CagedAnimal
{
public:
	static CagedLadybug* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	CagedLadybug(cocos2d::ValueMap& properties);
	virtual ~CagedLadybug();

	void initializePositions() override;

	LocalizedString* getAnimalName() override;
	std::string getSpriteResource() override;

private:
	typedef CagedAnimal super;

	cocos2d::Sprite* animalSprite;
};
