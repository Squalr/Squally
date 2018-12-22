#pragma once
#include "Engine/Cutscenes/CutsceneClip.h"

namespace cocos2d
{
	class Label;
	class LayerColor;
	class Sprite;
}

class DialogueLabel;

class RobotDoctor : public CutsceneClip
{
public:
	enum RobotDoctorScene {
		Intro,
		Singularity
	};

	static RobotDoctor* create(RobotDoctorScene robotDoctorScene);

protected:
	RobotDoctor(RobotDoctorScene robotDoctorScene);
	~RobotDoctor();

private:
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onDialogueShown();

	RobotDoctorScene activeScene;

	cocos2d::Sprite* background;
	cocos2d::Sprite* robot;
	cocos2d::Sprite* bed;

	cocos2d::LayerColor* dialoguePlate;
	DialogueLabel* dialogue;
	cocos2d::Label* escapeLabel;

	static const cocos2d::Vec2 panOffset;
};
