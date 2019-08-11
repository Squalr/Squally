#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityHealthBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;
class PlatformerEntity;

class EnemyHealthBehavior : public EntityHealthBehavior
{
public:
	static EnemyHealthBehavior* create(GameObject* owner, std::string attachedBehaviorArgs);

	void kill(bool loadDeadAnim = true) override;
	void revive() override;

	static const std::string MapKeyAttachedBehavior;
	static const std::string SaveKeyIsDead;

protected:
	EnemyHealthBehavior(GameObject* owner, std::string attachedBehaviorArgs);
	~EnemyHealthBehavior();

	void onLoad() override;

private:
	typedef EntityHealthBehavior super;
	
	void saveState();
};
