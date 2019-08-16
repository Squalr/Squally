#pragma once

#include "Objects/Platformer/Breakables/CagedAnimals/CagedAnimal.h"

namespace cocos2d
{
	class Sprite;
};

class CagedYeti : public CagedAnimal
{
public:
	static CagedYeti* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyCagedYeti;

protected:
	CagedYeti(cocos2d::ValueMap& properties);
	~CagedYeti();

	void initializePositions() override;

	LocalizedString* getAnimalName() override;
	std::string getSpriteResource() override;

private:
	typedef CagedAnimal super;

	cocos2d::Sprite* animalSprite;
};
