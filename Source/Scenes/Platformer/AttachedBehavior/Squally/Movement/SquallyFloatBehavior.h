#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerEnemy;
class Squally;

class SquallyFloatBehavior : public AttachedBehavior
{
public:
	static SquallyFloatBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	SquallyFloatBehavior(GameObject* owner);
	~SquallyFloatBehavior();

	void onLoad() override;
	void update(float dt) override;

private:
	typedef AttachedBehavior super;

	Squally* squally;

	float elapsed;
};
