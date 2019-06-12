#pragma once

#include "Engine/UI/HUD/Hud.h"

class IqEqDisplay;
class RuneBar;
class StatsBars;

class GameHud : public Hud
{
public:
	static GameHud* create();

	IqEqDisplay* getIqEqDisplay();
	RuneBar* getRuneBar();
	StatsBars* getStatsBars();

private:
	typedef Hud super;
	GameHud();
	virtual ~GameHud();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;

	IqEqDisplay* iqEqDisplay;
	StatsBars* statsBars;
	RuneBar* runeBar;
};
