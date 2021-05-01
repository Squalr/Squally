#pragma once

#include "Engine/Components/ComponentGroup.h"

namespace cocos2d
{
	class Sprite;
}

class Squally;

class EntityBehaviorGroup : public ComponentGroup
{
public:
	static EntityBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	EntityBehaviorGroup(GameObject* owner);
	virtual ~EntityBehaviorGroup();

	void onLoad() override;

private:
	typedef ComponentGroup super;
};
