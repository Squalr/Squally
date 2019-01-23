#pragma once

#include "Engine/UI/HUD/Hud.h"

class StatsBars;

class GameHud : public Hud
{
public:
	static GameHud* create();

private:
	typedef Hud super;
	GameHud();
	virtual ~GameHud();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;

	StatsBars* statsBars;
};
