#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class Squally;

class SquallyIsAliveHackBehavior : public AttachedBehavior
{
public:
	static SquallyIsAliveHackBehavior* create(GameObject* owner, std::string attachedBehaviorArgs);

	static const std::string MapKeyAttachedBehavior;

protected:
	SquallyIsAliveHackBehavior(GameObject* owner, std::string attachedBehaviorArgs);
	~SquallyIsAliveHackBehavior();

	void update(float dt) override;
	void registerHackables() override;
	void onLoad() override;

private:
	typedef AttachedBehavior super;

	bool isSquallyAliveHack();

	Squally* squally;

	static const std::string IdentifierIsAlive;
	static const std::string EventSquallyTrapped;
};
