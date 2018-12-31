#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class ParticleSystem;
}

class DialogMenu;
class FloatingSprite;
class MenuSprite;

class Monitor : public HackableObject
{
public:
	static Monitor* create(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyMonitor;

protected:
	Monitor(cocos2d::ValueMap* initProperties);
	~Monitor();

private:
	typedef HackableObject super;
	MenuSprite* monitorSprite;
	FloatingSprite* monitorSpriteFloating;
	cocos2d::ParticleSystem* monitorParticles;
	cocos2d::ParticleSystem* monitorParticlesBack;
	cocos2d::ParticleSystem* monitorSparkles;
	DialogMenu* monitorDialog;

	void onMonitorClick(MenuSprite* menuSprite);
};
