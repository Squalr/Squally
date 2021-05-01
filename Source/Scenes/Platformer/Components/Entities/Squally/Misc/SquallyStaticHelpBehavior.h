#pragma once

#include "Engine/Components/Component.h"

class Squally;

class SquallyStaticHelpBehavior : public Component
{
public:
	static SquallyStaticHelpBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SquallyStaticHelpBehavior(GameObject* owner);
	virtual ~SquallyStaticHelpBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef Component super;

	Squally* squally;

	static float* PositionXPtr;
	static float* PositionYPtr;
	static float* PositionZPtr;
	static float* MovementXPtr;
	static float* MovementYPtr;
	static float* MovementZPtr;
	static int* HealthPtr;
	static int* ManaPtr;
	static int* EqPtr;
	static int* ExpPtr;
};
