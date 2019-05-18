#include "IntroCutscene.h"

#include "Engine/Sound/Music.h"
#include "Scenes/Cutscenes/IntroCutscene/BoardMembers.h"
#include "Scenes/Cutscenes/IntroCutscene/HomeAssistantRobot.h"
#include "Scenes/Cutscenes/IntroCutscene/NeonCity.h"
#include "Scenes/Cutscenes/IntroCutscene/RobotDoctor.h"
#include "Scenes/Cutscenes/IntroCutscene/SquallyUploadMars.h"
#include "Scenes/Cutscenes/IntroCutscene/SquallyUploadSpace.h"
#include "Scenes/Cutscenes/IntroCutscene/VaporLabs.h"
#include "Scenes/Cutscenes/IntroCutscene/VaporWeb.h"

#include "Resources/MusicResources.h"

using namespace cocos2d;

IntroCutscene* IntroCutscene::create(std::function<void()> cutsceneCompleteCallback)
{
	IntroCutscene* instance = new IntroCutscene(cutsceneCompleteCallback);

	instance->autorelease();

	return instance;
}

IntroCutscene::IntroCutscene(std::function<void()> cutsceneCompleteCallback) : Cutscene(cutsceneCompleteCallback)
{
	this->music = Music::create(MusicResources::HeartBeat);

	this->enqueueCutsceneClip(NeonCity::create(NeonCity::NeonCityScene::Intro));
	this->enqueueCutsceneClip(HomeAssistantRobot::create(HomeAssistantRobot::HomeAssistantRobotScene::Intro));
	this->enqueueCutsceneClip(RobotDoctor::create(RobotDoctor::RobotDoctorScene::Intro));
	this->enqueueCutsceneClip(NeonCity::create(NeonCity::NeonCityScene::Return));
	this->enqueueCutsceneClip(BoardMembers::create());
	this->enqueueCutsceneClip(VaporLabs::create());
	this->enqueueCutsceneClip(NeonCity::create(NeonCity::NeonCityScene::Singularity));
	this->enqueueCutsceneClip(HomeAssistantRobot::create(HomeAssistantRobot::HomeAssistantRobotScene::Singularity));
	this->enqueueCutsceneClip(RobotDoctor::create(RobotDoctor::RobotDoctorScene::Singularity));
	this->enqueueCutsceneClip(VaporWeb::create());

	this->addChild(this->music);
}

IntroCutscene::~IntroCutscene()
{
}

void IntroCutscene::onEnter()
{
	Cutscene::onEnter();

	this->music->play(true);
}
