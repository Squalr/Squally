#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityCollisionBehaviorBase.h"

class LocalizedLabel;
class LocalizedString;
class PlatformerEntity;
class ProgressBar;

class FriendlyExpBarBehavior : public EntityCollisionBehaviorBase
{
public:
	static FriendlyExpBarBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	FriendlyExpBarBehavior(GameObject* owner);
	~FriendlyExpBarBehavior();

	void onLoad() override;

private:
	typedef EntityCollisionBehaviorBase super;

	void giveExp();

	PlatformerEntity* owner;
	
	ProgressBar* expProgressBar;
	LocalizedString* deltaString;
	LocalizedLabel* deltaLabel;
};
