#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;
class PlatformerEntity;

class EntityRuneBehaviorBase : public AttachedBehavior
{
public:	
	int getAvailableRunes();
	bool tryUseRune();
	float getRuneCooldown(int runeIndex);
	void setRuneCooldown(int runeIndex, float cooldown);
	int getMaxRunes();

	static const int MaxRunes;
	static const float RuneCooldown;

protected:
	EntityRuneBehaviorBase(GameObject* owner, std::string attachedBehaviorArgs);
	~EntityRuneBehaviorBase();

	void onLoad() override;
	void update(float) override;

	PlatformerEntity* entity;

	std::vector<float> runeCooldowns;

private:
	typedef AttachedBehavior super;
};
