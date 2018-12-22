#pragma once
#include "cocos/math/Vec2.h"

#include "Engine/Cutscenes/CutsceneClip.h"

namespace cocos2d
{
	class Label;
	class LayerColor;
	class Sprite;
}

class DialogueLabel;

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

	cocos2d::Sprite* background;
	cocos2d::Sprite* robot;
	cocos2d::Sprite* brokenPlate;

	cocos2d::LayerColor* dialoguePlate;
	DialogueLabel* dialogue;
	cocos2d::Label* escapeLabel;

	static const cocos2d::Vec2 panOffset;
};
