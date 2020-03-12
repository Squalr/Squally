#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class LocalizedLabel;
class LocalizedString;
class PlatformerEntity;
class ProgressBar;
class SmartParticles;
class Sound;

class FriendlyExpBarBehavior : public AttachedBehavior
{
public:
	static FriendlyExpBarBehavior* create(GameObject* owner);

	void giveExp(float startProgress, float endProgress, bool didLevelUp, int expGain);

	static const std::string MapKeyAttachedBehavior;

protected:
	FriendlyExpBarBehavior(GameObject* owner);
	virtual ~FriendlyExpBarBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehavior super;

	void fillBar(float startProgress, float endProgress, float fillDuration, float startDelay, int* tickCounter, std::function<void()> onComplete = nullptr);
	void runLevelUpEffect();

	PlatformerEntity* entity;
	
	int tickCounterA;
	int tickCounterB;
	ProgressBar* expProgressBar;
	LocalizedString* deltaString;
	LocalizedLabel* deltaLabel;
	LocalizedLabel* levelUpLabel;
	SmartParticles* levelUpFx;
	Sound* levelUpSound;
};
