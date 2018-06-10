#pragma once
#include "cocos2d.h"

#include "Events/DialogEvents.h"
#include "Objects/Collision/CollisionObject.h"
#include "Engine/Rendering/Components/FloatingSprite.h"
#include "Engine/Rendering/Components/MenuSprite.h"
#include "Scenes/Menus/Dialog/DialogMenu.h"


using namespace cocos2d;

class Monitor : public CollisionObject
{
public:
	static Monitor* create(std::string dialogFile);

protected:
	Monitor(std::string dialogFile);
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
