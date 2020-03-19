#pragma once

#include "Objects/Platformer/Breakables/CagedAnimals/CagedAnimal.h"

namespace cocos2d
{
	class Sprite;
};

class CagedTucan : public CagedAnimal
{
public:
	static CagedTucan* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	CagedTucan(cocos2d::ValueMap& properties);
	virtual ~CagedTucan();

	void initializePositions() override;

	LocalizedString* getAnimalName() override;
	std::string getSpriteResource() override;

private:
	typedef CagedAnimal super;

	cocos2d::Sprite* animalSprite;
};
