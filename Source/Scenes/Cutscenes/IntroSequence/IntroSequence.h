#pragma once
#include "cocos2d.h"

#include "Engine/Cutscenes/CutsceneSequence.h"
#include "Resources.h"
#include "Scenes/Cutscenes/IntroSequence/BoardMembers.h"
#include "Scenes/Cutscenes/IntroSequence/HomeAssistantRobot.h"
#include "Scenes/Cutscenes/IntroSequence/IntroSequence.h"
#include "Scenes/Cutscenes/IntroSequence/NeonCity.h"
#include "Scenes/Cutscenes/IntroSequence/RobotDoctor.h"
#include "Scenes/Cutscenes/IntroSequence/SquallyUploadMars.h"
#include "Scenes/Cutscenes/IntroSequence/SquallyUploadSpace.h"
#include "Scenes/Cutscenes/IntroSequence/VaporLabs.h"
#include "Scenes/Cutscenes/IntroSequence/VaporWeb.h"

using namespace cocos2d;

class IntroSequence : public CutsceneSequence
{
public:
	static IntroSequence* create(std::function<void()> cutsceneCompleteCallback);

private:
	IntroSequence(std::function<void()> cutsceneCompleteCallback);
	~IntroSequence();
};
