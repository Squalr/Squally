#pragma once

#include "Engine/Components/GameComponent.h"

class PlatformerEntity;
class SmartAnimationSequenceNode;

class WeakMindedBehavior : public GameComponent
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
	typedef GameComponent super;

	void onActivate();
	void onDeactivate();

	PlatformerEntity* entity;
	SmartAnimationSequenceNode* glowAnim;
};
