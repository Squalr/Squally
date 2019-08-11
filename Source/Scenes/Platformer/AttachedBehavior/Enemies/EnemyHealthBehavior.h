#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerEntity;

class EnemyHealthBehavior : public AttachedBehavior
{
public:
	static EnemyHealthBehavior* create(GameObject* owner, std::string attachedBehaviorArgs);

	static const std::string MapKeyAttachedBehavior;
	static const std::string SaveKeyIsDead;

protected:
	EnemyHealthBehavior(GameObject* owner, std::string attachedBehaviorArgs);
	~EnemyHealthBehavior();

	void onLoad() override;

private:
	typedef AttachedBehavior super;
	
	void saveState();
};
