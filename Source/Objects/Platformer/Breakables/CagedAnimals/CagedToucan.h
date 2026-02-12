#pragma once

#include "Objects/Platformer/Breakables/CagedAnimals/CagedAnimal.h"

namespace cocos2d
{
	class Sprite;
};

class CagedToucan : public CagedAnimal
{
public:
	static CagedToucan* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	CagedToucan(cocos2d::ValueMap& properties);
	virtual ~CagedToucan();

	void initializePositions() override;

	LocalizedString* getAnimalName() override;
	std::string getSpriteResource() override;

private:
	typedef CagedAnimal super;

	cocos2d::Sprite* animalSprite = nullptr;
};
