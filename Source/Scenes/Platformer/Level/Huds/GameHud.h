#pragma once

#include "Engine/UI/HUD/Hud.h"

namespace cocos2d
{
	class LayerColor;
}

class CinematicIndicator;
class CurrencyDisplay;
class ObjectiveDisplay;
class PlatformerDialogueBox;
class QuickPotion;
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

	cocos2d::LayerColor* flashLayer = nullptr;
	CurrencyDisplay* currencyDisplay = nullptr;
	QuickPotion* quickPotion = nullptr;
	ObjectiveDisplay* objectiveDisplay = nullptr;
	StatsBars* statsBars = nullptr;
	CinematicIndicator* cinematicIndicator = nullptr;
	PlatformerDialogueBox* dialogueBox = nullptr;
};
