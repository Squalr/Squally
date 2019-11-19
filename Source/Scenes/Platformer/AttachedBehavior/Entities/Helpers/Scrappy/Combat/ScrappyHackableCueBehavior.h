#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class Scrappy;
class Squally;

class ScrappyHackableCueBehavior : public AttachedBehavior
{
public:
	static ScrappyHackableCueBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	ScrappyHackableCueBehavior(GameObject* owner);
	~ScrappyHackableCueBehavior();

	void update(float dt) override;
	void onLoad() override;

private:
	typedef AttachedBehavior super;

	float cueCooldown;

	Scrappy* scrappy;
};
