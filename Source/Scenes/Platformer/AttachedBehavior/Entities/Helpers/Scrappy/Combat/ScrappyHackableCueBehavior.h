#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class Scrappy;
class Squally;

class ScrappyHackableCueBehavior : public AttachedBehavior
{
public:
	static ScrappyHackableCueBehavior* create(GameObject* owner);

	void disable();

	static const std::string MapKey;

protected:
	ScrappyHackableCueBehavior(GameObject* owner);
	virtual ~ScrappyHackableCueBehavior();

	void update(float dt) override;
	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehavior super;

	float cueCooldown;
	bool disabled;
	
	Scrappy* scrappy;
};
