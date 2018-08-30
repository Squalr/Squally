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
	enum HomeAssistantRobotScene {
		Intro,
		Singularity
	};

	static HomeAssistantRobot* create(HomeAssistantRobotScene homeAssistantRobotScene);

protected:
	HomeAssistantRobot(HomeAssistantRobotScene homeAssistantRobotScene);
	~HomeAssistantRobot();

private:
	void onEnter() override;
	void update(float) override;
	void initializePositions();
	void initializeListeners();

	void onDialogueShown();
	void endCutscene();

	HomeAssistantRobotScene activeScene;

	Sprite* background;
	Sprite* robot;
	Sprite* brokenPlate;

	LayerColor* dialoguePlate;
	Dialogue* dialogue;
	Label* escapeLabel;

	static const Vec2 panOffset;
};
