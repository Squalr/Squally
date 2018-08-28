#pragma once
#include "cocos2d.h"

#include "Engine/Dialogue/Dialogue.h"
#include "Engine/Input/InputManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Resources.h"
#include "Scenes/Cutscenes/Cutscene.h"
#include "Scenes/Cutscenes/Objects/StarLayer.h"

using namespace cocos2d;

class HomeAssistantRobot : public Cutscene
{
public:
	static HomeAssistantRobot* create();

protected:
	HomeAssistantRobot();
	~HomeAssistantRobot();

private:
	void onEnter() override;
	void update(float) override;
	void initializePositions();
	void initializeListeners();

	void onDialogueShown();
	void endCutscene();

	Sprite* background;

	LayerColor* dialoguePlate;
	Dialogue* dialogue;
	Label* escapeLabel;

	static const Vec2 panOffset;
};
