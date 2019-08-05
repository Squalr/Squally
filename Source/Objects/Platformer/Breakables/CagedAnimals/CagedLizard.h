#pragma once

#include "Objects/Platformer/Breakables/CagedAnimals/CagedAnimal.h"

namespace cocos2d
{
	class Sprite;
};

class CagedLizard : public CagedAnimal
{
public:
	static CagedLizard* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyCagedLizard;

protected:
	CagedLizard(cocos2d::ValueMap& initProperties);
	~CagedLizard();

	void initializePositions() override;

	LocalizedString* getAnimalName() override;
	std::string getSpriteResource() override;

private:
	typedef CagedAnimal super;

	cocos2d::Sprite* animalSprite;
};
