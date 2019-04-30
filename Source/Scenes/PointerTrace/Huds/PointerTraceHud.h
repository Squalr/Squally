#pragma once

#include "Engine/UI/HUD/Hud.h"

class LocalizedLabel;

class PointerTraceHud : public Hud
{
public:
	static PointerTraceHud* create();

private:
	typedef Hud super;
	PointerTraceHud();
	virtual ~PointerTraceHud();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;

	LocalizedLabel* eaxLabel;
	LocalizedLabel* ebxLabel;
	LocalizedLabel* ecxLabel;
	LocalizedLabel* edxLabel;
	LocalizedLabel* ediLabel;
	LocalizedLabel* esiLabel;
	LocalizedLabel* ebpLabel;
	LocalizedLabel* espLabel;
	LocalizedLabel* eipLabel;
};
