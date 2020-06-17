#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityCombatBehaviorBase.h"

namespace cocos2d
{
	class Sprite;
}

class Squally;

class GuanoPetrifiedCombatBehaviorGroup : public EntityCombatBehaviorBase
{
public:
	static GuanoPetrifiedCombatBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	GuanoPetrifiedCombatBehaviorGroup(GameObject* owner);
	virtual ~GuanoPetrifiedCombatBehaviorGroup();

	void onLoad() override;
	void onDisable() override;

private:
	typedef EntityCombatBehaviorBase super;
};
