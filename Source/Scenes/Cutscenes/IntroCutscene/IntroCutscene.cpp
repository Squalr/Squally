#include "IntroCutscene.h"

IntroCutscene* IntroCutscene::create(std::function<void()> cutsceneCompleteCallback)
{
	IntroCutscene* instance = new IntroCutscene(cutsceneCompleteCallback);

	instance->autorelease();

	return instance;
}

IntroCutscene::IntroCutscene(std::function<void()> cutsceneCompleteCallback) : Cutscene(cutsceneCompleteCallback)
{
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
}

IntroCutscene::~IntroCutscene()
{
}

void IntroCutscene::onEnter()
{
	Cutscene::onEnter();

	SoundManager::playMusicResource(Resources::Music_HeartBeat);
}
