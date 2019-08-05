#pragma once

#include "Objects/Platformer/Breakables/BreakableCage.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedString;

class CagedAnimal : public BreakableCage
{
public:

protected:
	CagedAnimal(cocos2d::ValueMap& initProperties, std::string saveKey);
	~CagedAnimal();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	cocos2d::Vec2 getButtonOffset() override;
	void onBreak() override;

	virtual LocalizedString* getAnimalName() = 0;
	virtual std::string getSpriteResource() = 0;

	cocos2d::Node* animalNode;

private:
	typedef BreakableCage super;

	cocos2d::Sprite* shineFx;
	std::string saveKey;

	bool alreadyCollected;
};
