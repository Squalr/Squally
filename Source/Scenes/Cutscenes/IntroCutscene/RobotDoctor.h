#pragma once
#include "cocos2d.h"

#include "Engine/Cutscenes/CutsceneClip.h"
#include "Engine/Dialogue/Dialogue.h"
#include "Engine/Utils/GameUtils.h"
#include "Resources.h"
#include "Scenes/Cutscenes/Objects/StarLayer.h"

using namespace cocos2d;

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

	Sprite* background;
	Sprite* robot;
	Sprite* bed;

	LayerColor* dialoguePlate;
	Dialogue* dialogue;
	Label* escapeLabel;

	static const Vec2 panOffset;
};
