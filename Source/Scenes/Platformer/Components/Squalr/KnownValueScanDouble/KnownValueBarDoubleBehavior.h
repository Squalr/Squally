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

class KnownValueBarDoubleBehavior : public GameComponent
{
public:
	static KnownValueBarDoubleBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	KnownValueBarDoubleBehavior(GameObject* owner);
	virtual ~KnownValueBarDoubleBehavior();

	void onLoad() override;
	void onDisable() override;
	void update(float dt) override;

private:
	typedef GameComponent super;

	void addHealth(double newHealth);
	void setHealth(double newHealth);
	void onDeath();

	PlatformerEntity* entity = nullptr;
	cocos2d::Sprite* spellAura;
	
	ProgressBar* healthBar;
	ConstantString* deltaString;
	LocalizedLabel* deltaLabel;
	ConstantString* healthString;
	LocalizedLabel* healthLabel;
	WorldSound* healSound;

	static double Health;
	static const double MaxHealth;
};
