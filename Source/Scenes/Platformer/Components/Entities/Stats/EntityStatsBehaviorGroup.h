#pragma once

#include "Engine/Components/GameComponentGroup.h"

namespace cocos2d
{
	class Sprite;
}

class Squally;

class EntityStatsBehaviorGroup : public GameComponentGroup
{
public:
	static EntityStatsBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	EntityStatsBehaviorGroup(GameObject* owner);
	virtual ~EntityStatsBehaviorGroup();

	void onLoad() override;

private:
	typedef GameComponentGroup super;
};
