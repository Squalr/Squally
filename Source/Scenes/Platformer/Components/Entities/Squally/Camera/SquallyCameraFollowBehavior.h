#pragma once

#include "Engine/Components/GameComponent.h"

class Squally;

class SquallyCameraFollowBehavior : public GameComponent
{
public:
	static SquallyCameraFollowBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SquallyCameraFollowBehavior(GameObject* owner);
	virtual ~SquallyCameraFollowBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponent super;

	float getLayerZoom();

	Squally* squally;
};
