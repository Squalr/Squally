#pragma once
#include <set>

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
	static HackableHint* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyHackableHint;

protected:
	HackableHint(cocos2d::ValueMap& initProperties);
	virtual ~HackableHint();
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef GameObject super;

	InteractMenu* interactMenu;
	CollisionObject* hintCollision;
};
