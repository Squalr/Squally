#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class Squally;

class SquallyHealthBehavior : public AttachedBehavior
{
public:
	static SquallyHealthBehavior* create(GameObject* owner, std::string attachedBehaviorArgs);

	static const std::string MapKeyAttachedBehavior;

protected:
	SquallyHealthBehavior(GameObject* owner, std::string attachedBehaviorArgs);
	~SquallyHealthBehavior();

	void onLoad() override;

private:
	typedef AttachedBehavior super;
	
	void saveState();
	void respawn();

	cocos2d::Vec2 spawnCoords;

	Squally* squally;
};
