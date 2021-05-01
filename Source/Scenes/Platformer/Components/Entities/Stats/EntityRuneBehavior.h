#pragma once

#include "Engine/Components/Component.h"

class PlatformerEntity;

class EntityRuneBehavior : public Component
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

	PlatformerEntity* entity;

	std::vector<float> runeCooldowns;

private:
	typedef Component super;

	void onRevive();
};
