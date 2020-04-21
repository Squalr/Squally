#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class HackableCode;
class Squally;

class SquallySwimHackBehavior : public AttachedBehavior
{
public:
	static SquallySwimHackBehavior* create(GameObject* owner);

	static const std::string MapKey;
	static const std::string HackIdentifierIsSwimming;

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

	Squally* squally;
};
