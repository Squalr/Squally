#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class IsSwimmingClippy;
class Squally;

class SquallySwimHackBehavior : public AttachedBehavior
{
public:
	static SquallySwimHackBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SquallySwimHackBehavior(GameObject* owner);
	virtual ~SquallySwimHackBehavior();

	void update(float dt) override;
	void registerHackables() override;
	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehavior super;

	bool canSwimHack();

	IsSwimmingClippy* clippy;
	Squally* squally;
};
