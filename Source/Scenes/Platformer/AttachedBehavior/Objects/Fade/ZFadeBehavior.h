#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class ZFadeBehavior : public AttachedBehavior
{
public:
	static ZFadeBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	ZFadeBehavior(GameObject* owner);
	virtual ~ZFadeBehavior();

	void onLoad() override;
	void onDisable() override;
	void update(float dt) override;

private:
	typedef AttachedBehavior super;

	GameObject* object;
	float multiplier;
	
	static const std::string PropertyFadeMultiplier;
};
