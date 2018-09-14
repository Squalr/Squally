#include "IntroSequence.h"

IntroSequence* IntroSequence::create(std::function<void()> cutsceneCompleteCallback)
{
	IntroSequence* instance = new IntroSequence(cutsceneCompleteCallback);

	instance->autorelease();

	return instance;
}

IntroSequence::IntroSequence(std::function<void()> cutsceneCompleteCallback) : CutsceneSequence()
{
	this->setCutsceneEndCallback(cutsceneCompleteCallback);

	this->enqueueCutscene(NeonCity::create(NeonCity::NeonCityScene::Intro));
	this->enqueueCutscene(HomeAssistantRobot::create(HomeAssistantRobot::HomeAssistantRobotScene::Intro));
	this->enqueueCutscene(RobotDoctor::create(RobotDoctor::RobotDoctorScene::Intro));
	this->enqueueCutscene(NeonCity::create(NeonCity::NeonCityScene::Return));
	this->enqueueCutscene(BoardMembers::create());
	this->enqueueCutscene(VaporLabs::create());
	this->enqueueCutscene(NeonCity::create(NeonCity::NeonCityScene::Singularity));
	this->enqueueCutscene(HomeAssistantRobot::create(HomeAssistantRobot::HomeAssistantRobotScene::Singularity));
	this->enqueueCutscene(RobotDoctor::create(RobotDoctor::RobotDoctorScene::Singularity));
	this->enqueueCutscene(VaporWeb::create());
}

IntroSequence::~IntroSequence()
{
}
