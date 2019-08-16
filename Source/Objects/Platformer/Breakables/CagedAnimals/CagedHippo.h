#pragma once

#include "Objects/Platformer/Breakables/CagedAnimals/CagedAnimal.h"

namespace cocos2d
{
	class Sprite;
};

class CagedHippo : public CagedAnimal
{
public:
	static CagedHippo* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyCagedHippo;

protected:
	CagedHippo(cocos2d::ValueMap& properties);
	~CagedHippo();

	void initializePositions() override;

	LocalizedString* getAnimalName() override;
	std::string getSpriteResource() override;

private:
	typedef CagedAnimal super;

	cocos2d::Sprite* animalSprite;
};
