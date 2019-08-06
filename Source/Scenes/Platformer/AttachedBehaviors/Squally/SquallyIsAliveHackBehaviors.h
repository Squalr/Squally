#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class Squally;

class SquallyIsAliveHackBehaviors : public AttachedBehavior
{
public:
	static SquallyIsAliveHackBehaviors* create(GameObject* owner, std::string attachedBehaviorArgs);

	static const std::string MapKeyAttachedBehavior;

protected:
	SquallyIsAliveHackBehaviors(GameObject* owner, std::string attachedBehaviorArgs);
	~SquallyIsAliveHackBehaviors();

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
