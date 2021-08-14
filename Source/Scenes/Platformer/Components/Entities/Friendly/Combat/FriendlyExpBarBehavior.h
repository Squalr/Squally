#pragma once

#include "Engine/Components/GameComponent.h"

class LocalizedLabel;
class LocalizedString;
class PlatformerEntity;
class ProgressBar;
class SmartParticles;
class Sound;

class FriendlyExpBarBehavior : public GameComponent
{
public:
	static FriendlyExpBarBehavior* create(GameObject* owner);

	void giveExp(float startProgress, float endProgress, bool didLevelUp, int expGain);

	static const std::string MapKey;

protected:
	FriendlyExpBarBehavior(GameObject* owner);
	virtual ~FriendlyExpBarBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponent super;

	void fillBar(float startProgress, float endProgress, float fillDuration, float startDelay, int* tickCounter, std::function<void()> onComplete = nullptr);
	void runLevelUpEffect();

	PlatformerEntity* entity = nullptr;
	
	int tickCounterA = 0;
	int tickCounterB = 0;
	ProgressBar* expProgressBar = nullptr;
	LocalizedString* deltaString = nullptr;
	LocalizedLabel* deltaLabel = nullptr;
	LocalizedLabel* levelUpLabel = nullptr;
	SmartParticles* levelUpFx = nullptr;
	Sound* levelUpSound = nullptr;
};
