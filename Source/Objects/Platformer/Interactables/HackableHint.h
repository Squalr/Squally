#pragma once

#include "Engine/Maps/GameObject.h"

namespace cocos2d
{
	class ParticleSystem;
}

class CollisionObject;
class InteractMenu;

class HackableHint : public GameObject
{
public:
	static HackableHint* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyHackableHint;

protected:
	HackableHint(cocos2d::ValueMap& properties);
	~HackableHint();
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef GameObject super;

	InteractMenu* interactMenu;
	CollisionObject* hintCollision;
};
