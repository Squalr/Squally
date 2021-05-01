#pragma once

#include "Engine/Components/Component.h"

class Scrappy;

class ScrappyHackableCueBehavior : public Component
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
	typedef Component super;

	float cueCooldown;
	bool disabled;
	
	Scrappy* scrappy;
};
