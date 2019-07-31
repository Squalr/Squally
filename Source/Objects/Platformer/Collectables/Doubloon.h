#pragma once

#include "Objects/Platformer/Collectables/Collectable.h"

class LocalizedString;
class SmartAnimationSequenceNode;

class Doubloon : public Collectable
{
public:
	static Doubloon* create(cocos2d::ValueMap& initProperties);

	static std::string getIdentifier();
	static std::string getIconResource();
	static LocalizedString* getString();

	static const std::string MapKeyDoubloon;

protected:
	Doubloon(cocos2d::ValueMap& initProperties);
	~Doubloon();

	void onEnter() override;

private:
	typedef Collectable super;

	SmartAnimationSequenceNode* doubloon;
};
