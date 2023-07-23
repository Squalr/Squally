#pragma once

#include "Scenes/Platformer/Components/Entities/Combat/EntityCombatBehaviorBase.h"

namespace cocos2d
{
	class Sprite;
}

class Squally;

class GrimCombatBehaviorGroup : public EntityCombatBehaviorBase
{
public:
	static GrimCombatBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	GrimCombatBehaviorGroup(GameObject* owner);
	virtual ~GrimCombatBehaviorGroup();

	void onLoad() override;
	void onDisable() override;

private:
	typedef EntityCombatBehaviorBase super;
};
