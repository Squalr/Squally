#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityCollisionBehaviorBase.h"

namespace cocos2d
{
	class ParticleSystem;
}

class LocalizedLabel;
class LocalizedString;
class PlatformerEntity;
class ProgressBar;
class Sound;

class FriendlyExpBarBehavior : public EntityCollisionBehaviorBase
{
public:
	static FriendlyExpBarBehavior* create(GameObject* owner);

	void giveExp(float startProgress, float endProgress, bool didLevelUp, int expGain);

	static const std::string MapKeyAttachedBehavior;

protected:
	FriendlyExpBarBehavior(GameObject* owner);
	virtual ~FriendlyExpBarBehavior();

	void onLoad() override;

private:
	typedef EntityCollisionBehaviorBase super;

	void fillBar(float startProgress, float endProgress, float fillDuration, float startDelay, int* tickCounter, std::function<void()> onComplete = nullptr);
	void runLevelUpEffect();

	PlatformerEntity* owner;
	
	int tickCounterA;
	int tickCounterB;
	ProgressBar* expProgressBar;
	LocalizedString* deltaString;
	LocalizedLabel* deltaLabel;
	LocalizedLabel* levelUpLabel;
	cocos2d::ParticleSystem* levelUpFx;
	Sound* levelUpSound;
};
