#pragma once

#include "Engine/AttachedBehavior/AttachedBehaviorGroup.h"

namespace cocos2d
{
	class Sprite;
}

class Squally;

class SquallyBehaviorGroup : public AttachedBehaviorGroup
{
public:
	static SquallyBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SquallyBehaviorGroup(GameObject* owner);
	virtual ~SquallyBehaviorGroup();

	void onLoad() override;

private:
	typedef AttachedBehaviorGroup super;
};
