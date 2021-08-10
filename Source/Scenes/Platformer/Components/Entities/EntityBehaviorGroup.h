#pragma once

#include "Engine/Components/GameComponentGroup.h"

namespace cocos2d
{
	class Sprite;
}

class Squally;

class EntityBehaviorGroup : public GameComponentGroup
{
public:
	static EntityBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	EntityBehaviorGroup(GameObject* owner);
	virtual ~EntityBehaviorGroup();

	void onLoad() override;

private:
	typedef GameComponentGroup super;
};
