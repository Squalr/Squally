#pragma once

#include "Engine/AttachedBehavior/AttachedBehaviorGroup.h"

namespace cocos2d
{
	class Sprite;
}

class Squally;

class GuanoCombatBehaviorGroup : public AttachedBehaviorGroup
{
public:
	static GuanoCombatBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	GuanoCombatBehaviorGroup(GameObject* owner);
	virtual ~GuanoCombatBehaviorGroup();

	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehaviorGroup super;
};
