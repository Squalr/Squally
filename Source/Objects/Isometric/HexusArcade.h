#pragma once
#include "cocos2d.h"

#include "Engine/Hackables/HackableObject.h"
#include "Resources/ObjectResources.h"

using namespace cocos2d;

class HexusArcade : public HackableObject
{
public:
	static HexusArcade* create(ValueMap* initProperties);

protected:
	HexusArcade(ValueMap* initProperties);
	~HexusArcade();

	Vec2 getButtonOffset() override;

private:
	void registerHackables();

	Sprite* arcadeMachine;
};
