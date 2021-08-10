#pragma once

#include "Engine/Components/GameComponent.h"

class EntityCollisionBehaviorBase;
class PlatformerEntity;
class Squally;
class WorldSound;

class BirdBehavior : public GameComponent
{
public:
	static BirdBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	BirdBehavior(GameObject* owner);
	virtual ~BirdBehavior();

	void onLoad() override;
	void onDisable() override;
	void update(float dt) override;

private:
	typedef GameComponent super;

	void tryNextAction();
	void queueNextAction();
	void onHit(EntityCollisionBehaviorBase* collisionBehavior);
	void moveBeak(float duration);

	PlatformerEntity* entity;
	Squally* squally;
	WorldSound* startledSound;
	WorldSound* squawkSound;
	bool wasStartled;
	float hitDelay;
};
