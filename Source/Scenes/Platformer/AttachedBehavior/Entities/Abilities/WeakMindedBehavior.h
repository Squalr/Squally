#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerEntity;
class SmartAnimationSequenceNode;

class WeakMindedBehavior : public AttachedBehavior
{
public:
	static WeakMindedBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	WeakMindedBehavior(GameObject* owner);
	virtual ~WeakMindedBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehavior super;

	void onActivate();
	void onDeactivate();

	PlatformerEntity* entity;
	SmartAnimationSequenceNode* glowAnim;
};
