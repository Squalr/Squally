#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;
class PlatformerEntity;

class EntityRuneBehavior : public AttachedBehavior
{
public:
	static EntityRuneBehavior* create(GameObject* owner, std::string attachedBehaviorArgs);

	int getAvailableRunes();
	bool tryUseRune();
	float getRuneCooldown(int runeIndex);
	void setRuneCooldown(int runeIndex, float cooldown);
	int getMaxRunes();

	static const int MaxRunes;
	static const float RuneCooldown;

protected:
	EntityRuneBehavior(GameObject* owner, std::string attachedBehaviorArgs);
	~EntityRuneBehavior();

	void onLoad() override;
	void update(float) override;

	PlatformerEntity* entity;

	std::vector<float> runeCooldowns;

private:
	typedef AttachedBehavior super;
};
