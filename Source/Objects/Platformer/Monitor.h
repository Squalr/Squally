#pragma once
#include "cocos2d.h"

#include "Events/DialogEvents.h"
#include "Engine/Hackables/HackableObject.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/UI/FloatingSprite.h"
#include "Menus/Dialog/DialogMenu.h"

using namespace cocos2d;

class Monitor : public HackableObject
{
public:
	static Monitor* create(ValueMap* initProperties);

protected:
	Monitor(ValueMap* initProperties);
	~Monitor();

private:
	MenuSprite * monitorSprite;
	FloatingSprite * monitorSpriteFloating;
	ParticleSystem * monitorParticles;
	ParticleSystem * monitorParticlesBack;
	ParticleSystem * monitorSparkles;
	DialogMenu* monitorDialog;

	void onMonitorClick(MenuSprite* menuSprite);
};
