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

class UnknownValueBarBehavior : public AttachedBehavior
{
public:
	static UnknownValueBarBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	UnknownValueBarBehavior(GameObject* owner);
	virtual ~UnknownValueBarBehavior();

	void onLoad() override;
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
	WorldSound* healSound;

	static int Health;
	static const int MaxHealth;
};
