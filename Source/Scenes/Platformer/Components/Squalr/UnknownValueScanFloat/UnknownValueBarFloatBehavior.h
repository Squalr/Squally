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

class UnknownValueBarFloatBehavior : public GameComponent
{
public:
	static UnknownValueBarFloatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	UnknownValueBarFloatBehavior(GameObject* owner);
	virtual ~UnknownValueBarFloatBehavior();

	void onLoad() override;
	void onDisable() override;
	void update(float dt) override;

private:
	typedef GameComponent super;

	void addHealth(float newHealth);
	void setHealth(float newHealth);
	void onDeath();

	PlatformerEntity* entity = nullptr;
	cocos2d::Sprite* spellAura = nullptr;
	
	ProgressBar* healthBar = nullptr;
	ConstantString* deltaString = nullptr;
	LocalizedLabel* deltaLabel = nullptr;
	WorldSound* healSound = nullptr;

	static float Health;
	static const float MaxHealth;
};
