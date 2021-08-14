#pragma once

#include "Engine/Components/GameComponent.h"

namespace cocos2d
{
	class Sprite;
}

class ConstantString;
class LocalizedLabel;
class PlatformerEntity;
class ProgressBar;
class WorldSound;

class KnownValueBarFloatBehavior : public GameComponent
{
public:
	static KnownValueBarFloatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	KnownValueBarFloatBehavior(GameObject* owner);
	virtual ~KnownValueBarFloatBehavior();

	void onLoad() override;
	void onDisable() override;
	void update(float dt) override;

private:
	typedef GameComponent super;

	void addHealth(float newHealth);
	void setHealth(float newHealth);
	void onDeath();

	PlatformerEntity* entity = nullptr;
	cocos2d::Sprite* spellAura;
	
	ProgressBar* healthBar;
	ConstantString* deltaString;
	LocalizedLabel* deltaLabel;
	ConstantString* healthString;
	LocalizedLabel* healthLabel;
	WorldSound* healSound;

	static float Health;
	static const float MaxHealth;
};
