#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class HackableCode;
class IsSwimmingClippy;
class Squally;

class SquallySwimHackBehavior : public AttachedBehavior
{
public:
	static SquallySwimHackBehavior* create(GameObject* owner);

	void enableAllClippy();

	static const std::string MapKey;

protected:
	SquallySwimHackBehavior(GameObject* owner);
	virtual ~SquallySwimHackBehavior();

	void update(float dt) override;
	void registerHackables();
	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehavior super;

	bool canSwimHack();

	std::vector<HackableCode*> hackables;

	IsSwimmingClippy* clippy;
	Squally* squally;
};
