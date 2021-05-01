#pragma once

#include "Engine/Components/Component.h"

class HackableCode;
class Squally;

class SquallySwimHackBehavior : public Component
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
	typedef Component super;

	bool canSwimHack();

	std::vector<HackableCode*> hackables;

	Squally* squally;
};
