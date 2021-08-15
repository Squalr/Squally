#pragma once

#include "Engine/Components/GameComponent.h"

class ZFadeBehavior : public GameComponent
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
	typedef GameComponent super;

	GameObject* object = nullptr;
	float multiplier = 1.0f;
	
	static const std::string PropertyFadeMultiplier;
};
