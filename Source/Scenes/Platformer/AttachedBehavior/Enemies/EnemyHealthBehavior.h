#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerEntity;

class EnemyHealthBehavior : public AttachedBehavior
{
public:
	static EnemyHealthBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;
	static const std::string SaveKeyIsDead;

protected:
	EnemyHealthBehavior(GameObject* owner);
	~EnemyHealthBehavior();

	void onLoad() override;

private:
	typedef AttachedBehavior super;
	
	void saveState();
};
