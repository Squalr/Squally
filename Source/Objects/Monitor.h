#pragma once
#include "cocos2d.h"
#include "Collision/CollisionObject.h"
#include "GUI/Components/FloatingSprite.h"
#include "GUI/Components/MenuSprite.h"
#include "GUI/Menus/Dialog/DialogMenu.h"

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
