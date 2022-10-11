#pragma once

#include "Engine/Components/GameComponent.h"

class Scrappy;

class ScrappyHackableCueBehavior : public GameComponent
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
	typedef GameComponent super;

	float cueCooldown = 0.0f;
	bool disabled = false;
	Scrappy* scrappy = nullptr;
};
