#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityCollisionBehaviorBase.h"

class LocalizedLabel;
class LocalizedString;
class PlatformerEntity;
class ProgressBar;
class Sound;

class FriendlyExpBarBehavior : public EntityCollisionBehaviorBase
{
public:
	static FriendlyExpBarBehavior* create(GameObject* owner);

	void giveExp(int expGain);

	static const std::string MapKeyAttachedBehavior;

protected:
	FriendlyExpBarBehavior(GameObject* owner);
	virtual ~FriendlyExpBarBehavior();

	void onLoad() override;

private:
	typedef EntityCollisionBehaviorBase super;

	void fillBar(float startProgress, float endProgress, float fillDuration, float startDelay, std::function<void()> onComplete = nullptr);
	void runLevelUpEffect();

	PlatformerEntity* owner;
	
	int tickCounter;
	ProgressBar* expProgressBar;
	LocalizedString* deltaString;
	LocalizedLabel* deltaLabel;
	Sound* levelUpSound;
};
