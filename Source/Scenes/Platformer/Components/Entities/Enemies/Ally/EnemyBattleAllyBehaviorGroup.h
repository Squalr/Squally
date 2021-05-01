#pragma once

#include "Engine/Components/ComponentGroup.h"

namespace cocos2d
{
	class Sprite;
}

class Squally;

class EnemyBattleAllyBehaviorGroup : public ComponentGroup
{
public:
	static EnemyBattleAllyBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	EnemyBattleAllyBehaviorGroup(GameObject* owner);
	virtual ~EnemyBattleAllyBehaviorGroup();

	void onLoad() override;

private:
	typedef ComponentGroup super;
};
