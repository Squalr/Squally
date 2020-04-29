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

class KnownValueBarBehavior : public AttachedBehavior
{
public:
	static KnownValueBarBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	KnownValueBarBehavior(GameObject* owner);
	virtual ~KnownValueBarBehavior();

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
