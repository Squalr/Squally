#pragma once

#include "Objects/Platformer/Breakables/CagedAnimals/CagedAnimal.h"

namespace cocos2d
{
	class Sprite;
};

class CagedFox : public CagedAnimal
{
public:
	static CagedFox* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyCagedFox;

protected:
	CagedFox(cocos2d::ValueMap& initProperties);
	~CagedFox();

	void initializePositions() override;

	LocalizedString* getAnimalName() override;
	std::string getSpriteResource() override;

private:
	typedef CagedAnimal super;

	cocos2d::Sprite* animalSprite;
};
