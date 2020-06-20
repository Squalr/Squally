#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class ConstantString;
class LocalizedLabel;
class PlatformerEntity;
class ProgressBar;
class WorldSound;

class KnownValueBarInt32Behavior : public AttachedBehavior
{
public:
	static KnownValueBarInt32Behavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	KnownValueBarInt32Behavior(GameObject* owner);
	virtual ~KnownValueBarInt32Behavior();

	void onLoad() override;
	void onDisable() override;
	void update(float dt) override;

private:
	typedef AttachedBehavior super;

	void addHealth(int newHealth);
	void setHealth(int newHealth);
	void onDeath();

	PlatformerEntity* entity;
	cocos2d::Sprite* spellAura;
	
	ProgressBar* healthBar;
	ConstantString* deltaString;
	LocalizedLabel* deltaLabel;
	ConstantString* healthString;
	LocalizedLabel* healthLabel;
	WorldSound* healSound;

	static int Health;
	static const int MaxHealth;
};
