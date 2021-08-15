#pragma once

#include "Engine/Components/GameComponent.h"

class PlatformerEntity;

class EntityRuneBehavior : public GameComponent
{
public:
	static EntityRuneBehavior* create(GameObject* owner);

	int getAvailableRunes();
	bool tryUseRune();
	float getRuneCooldown(int runeIndex);
	void setRuneCooldown(int runeIndex, float cooldown);

	static const int MaxRunes;
	static const float RuneCooldown;

protected:
	EntityRuneBehavior(GameObject* owner);
	virtual ~EntityRuneBehavior();

	void onLoad() override;
	void onDisable() override;
	void update(float) override;

	PlatformerEntity* entity = nullptr;
	std::vector<float> runeCooldowns;

private:
	typedef GameComponent super;

	void onRevive();
};
