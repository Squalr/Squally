#pragma once

#include "Engine/SmartNode.h"

class CurrencyDisplay;
class LocalizedLabel;
class RuneBar;
class StatsBars;

class GameHud : public SmartNode
{
public:
	static GameHud* create();

	CurrencyDisplay* getCurrencyDisplay();
	RuneBar* getRuneBar();
	StatsBars* getStatsBars();

private:
	typedef SmartNode super;
	GameHud();
	virtual ~GameHud();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;

	CurrencyDisplay* currencyDisplay;
	StatsBars* statsBars;
	RuneBar* runeBar;
	LocalizedLabel* controlsLabel;
};
