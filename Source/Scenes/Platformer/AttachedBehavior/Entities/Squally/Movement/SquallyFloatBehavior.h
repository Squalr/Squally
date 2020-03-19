#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerEnemy;
class Squally;

class SquallyFloatBehavior : public AttachedBehavior
{
public:
	static SquallyFloatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SquallyFloatBehavior(GameObject* owner);
	virtual ~SquallyFloatBehavior();

	void onLoad() override;
	void onDisable() override;
	void update(float dt) override;

private:
	typedef AttachedBehavior super;

	Squally* squally;

	float elapsed;
};
