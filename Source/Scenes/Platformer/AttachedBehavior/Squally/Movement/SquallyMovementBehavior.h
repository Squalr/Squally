#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Movement/EntityMovementBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class Squally;

class SquallyMovementBehavior : public EntityMovementBehavior
{
public:
	static SquallyMovementBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	SquallyMovementBehavior(GameObject* owner);
	~SquallyMovementBehavior();

	void update(float dt) override;
	void onLoad() override;

private:
	typedef EntityMovementBehavior super;

	Squally* squally;

	bool isDisposing;
	float elapsed;
};
