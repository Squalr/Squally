#pragma once

#include "Engine/Components/GameComponent.h"

namespace cocos2d
{
	class Sprite;
};

class PlatformerEntity;
class Scrappy;

class RopedMovementBehavior : public GameComponent
{
public:
	static RopedMovementBehavior* create(GameObject* owner);

	void detach();

	static const std::string MapKey;

protected:
	RopedMovementBehavior(GameObject* owner);
	virtual ~RopedMovementBehavior();

	void onLoad() override;
	void onDisable() override;
	void update(float dt) override;

private:
	typedef GameComponent super;

	PlatformerEntity* entity = nullptr;
	Scrappy* scrappy = nullptr;
	cocos2d::Sprite* waistRope;

	bool isDetached;
};
