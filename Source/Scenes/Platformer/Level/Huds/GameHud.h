#pragma once

#include "Engine/UI/HUD/Hud.h"

class CinematicIndicator;
class CurrencyDisplay;
class ObjectiveDisplay;
class PlatformerDialogueBox;
class StatsBars;

class GameHud : public Hud
{
public:
	static GameHud* create();

protected:
	GameHud();
	virtual ~GameHud();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;

private:
	typedef Hud super;

	CurrencyDisplay* currencyDisplay;
	ObjectiveDisplay* objectiveDisplay;
	StatsBars* statsBars;
	CinematicIndicator* cinematicIndicator;
	PlatformerDialogueBox* dialogueBox;
};
