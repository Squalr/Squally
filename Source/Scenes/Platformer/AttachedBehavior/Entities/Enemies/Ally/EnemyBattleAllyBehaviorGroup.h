#pragma once

#include "Engine/AttachedBehavior/AttachedBehaviorGroup.h"

namespace cocos2d
{
	class Sprite;
}

class Squally;

class EnemyBattleAllyBehaviorGroup : public AttachedBehaviorGroup
{
public:
	static EnemyBattleAllyBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	EnemyBattleAllyBehaviorGroup(GameObject* owner);
	virtual ~EnemyBattleAllyBehaviorGroup();

	void onLoad() override;

private:
	typedef AttachedBehaviorGroup super;
};
