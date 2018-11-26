#pragma once
#include "cocos2d.h"

#include "Engine/Cutscenes/CutsceneClip.h"
#include "Engine/Dialogue/Dialogue.h"
#include "Engine/Utils/GameUtils.h"
#include "Resources/CutsceneResources.h"
#include "Resources/StringResources.h"
#include "Scenes/Cutscenes/Objects/StarLayer.h"

using namespace cocos2d;

class HomeAssistantRobot : public CutsceneClip
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
	void initializePositions() override;
	void initializeListeners() override;
	void onDialogueShown();

	HomeAssistantRobotScene activeScene;

	Sprite* background;
	Sprite* robot;
	Sprite* brokenPlate;

	LayerColor* dialoguePlate;
	Dialogue* dialogue;
	Label* escapeLabel;

	static const Vec2 panOffset;
};
