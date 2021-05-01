#pragma once

#include "Engine/Components/Component.h"

class ZFadeBehavior : public Component
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
	typedef Component super;

	GameObject* object;
	float multiplier;
	
	static const std::string PropertyFadeMultiplier;
};
