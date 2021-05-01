#pragma once

#include "Engine/Components/Component.h"

class Squally;

class SquallyCameraFollowBehavior : public Component
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
	typedef Component super;

	float getLayerZoom();

	Squally* squally;
};
