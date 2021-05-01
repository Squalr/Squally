#pragma once

#include "Scenes/Platformer/Components/Entities/Combat/EntityCombatBehaviorBase.h"

namespace cocos2d
{
	class Sprite;
}

class Squally;

class GeckyCombatBehaviorGroup : public EntityCombatBehaviorBase
{
public:
	static GeckyCombatBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	GeckyCombatBehaviorGroup(GameObject* owner);
	virtual ~GeckyCombatBehaviorGroup();

	void onLoad() override;
	void onDisable() override;

private:
	typedef EntityCombatBehaviorBase super;
};
