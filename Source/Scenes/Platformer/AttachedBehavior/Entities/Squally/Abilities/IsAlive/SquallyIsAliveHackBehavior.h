#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class IsAliveClippy;
class Squally;

class SquallyIsAliveHackBehavior : public AttachedBehavior
{
public:
	static SquallyIsAliveHackBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SquallyIsAliveHackBehavior(GameObject* owner);
	virtual ~SquallyIsAliveHackBehavior();

	void update(float dt) override;
	void registerHackables();
	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehavior super;

	bool isSquallyAliveHack();

	IsAliveClippy* clippy;
	Squally* squally;
	float cooldown;

	static const std::string IdentifierIsAlive;
	static const std::string EventSquallyTrapped;
};
