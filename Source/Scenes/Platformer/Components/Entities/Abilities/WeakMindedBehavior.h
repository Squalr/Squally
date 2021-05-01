#pragma once

#include "Engine/Components/Component.h"

class PlatformerEntity;
class SmartAnimationSequenceNode;

class WeakMindedBehavior : public Component
{
public:
	static WeakMindedBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	WeakMindedBehavior(GameObject* owner);
	virtual ~WeakMindedBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef Component super;

	void onActivate();
	void onDeactivate();

	PlatformerEntity* entity;
	SmartAnimationSequenceNode* glowAnim;
};
