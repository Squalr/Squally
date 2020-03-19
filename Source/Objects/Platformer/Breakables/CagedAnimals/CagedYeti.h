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

	static const std::string MapKey;

protected:
	CagedYeti(cocos2d::ValueMap& properties);
	virtual ~CagedYeti();

	void initializePositions() override;

	LocalizedString* getAnimalName() override;
	std::string getSpriteResource() override;

private:
	typedef CagedAnimal super;

	cocos2d::Sprite* animalSprite;
};
