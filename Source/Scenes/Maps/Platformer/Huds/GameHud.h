#pragma once

#include "Engine/UI/HUD/Hud.h"

class HackableBar;
class StatsBars;

class GameHud : public Hud
{
public:
	static GameHud* create();

	HackableBar* getHackableBar();
	StatsBars* getStatsBars();

private:
	typedef Hud super;
	GameHud();
	virtual ~GameHud();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;

	StatsBars* statsBars;
	HackableBar* hackableBar;
};
