#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class IsAliveClippy;
class Squally;

class SquallySwimHackBehavior : public AttachedBehavior
{
public:
	static SquallySwimHackBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	SquallySwimHackBehavior(GameObject* owner);
	virtual ~SquallySwimHackBehavior();

	void update(float dt) override;
	void registerHackables() override;
	void onLoad() override;

private:
	typedef AttachedBehavior super;

	bool canSwimHack();

	IsAliveClippy* clippy;
	Squally* squally;

	static const std::string IdentifierCanSwim;
};
