#pragma once
#include "cocos2d.h"

#include "Engine/Cutscenes/Cutscene.h"
#include "Engine/Sound/SoundManager.h"
#include "Resources/MusicResources.h"
#include "Scenes/Cutscenes/IntroCutscene/BoardMembers.h"
#include "Scenes/Cutscenes/IntroCutscene/HomeAssistantRobot.h"
#include "Scenes/Cutscenes/IntroCutscene/NeonCity.h"
#include "Scenes/Cutscenes/IntroCutscene/RobotDoctor.h"
#include "Scenes/Cutscenes/IntroCutscene/SquallyUploadMars.h"
#include "Scenes/Cutscenes/IntroCutscene/SquallyUploadSpace.h"
#include "Scenes/Cutscenes/IntroCutscene/VaporLabs.h"
#include "Scenes/Cutscenes/IntroCutscene/VaporWeb.h"

using namespace cocos2d;

class IntroCutscene : public Cutscene
{
public:
	static IntroCutscene* create(std::function<void()> cutsceneCompleteCallback);

private:
	IntroCutscene(std::function<void()> cutsceneCompleteCallback);
	~IntroCutscene();

	void onEnter() override;
};
