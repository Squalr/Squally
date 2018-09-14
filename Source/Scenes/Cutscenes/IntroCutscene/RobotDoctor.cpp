#include "RobotDoctor.h"

const Vec2 RobotDoctor::panOffset = Vec2(-608.0f, 256.0f);

RobotDoctor* RobotDoctor::create(RobotDoctorScene robotDoctorScene)
{
	RobotDoctor* instance = new RobotDoctor(robotDoctorScene);

	instance->autorelease();

	return instance;
}

RobotDoctor::RobotDoctor(RobotDoctorScene robotDoctorScene)
{
	this->activeScene = robotDoctorScene;

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->background = Sprite::create(Resources::Cutscenes_RobotDoctor_Background);
	this->bed = Sprite::create(Resources::Cutscenes_RobotDoctor_Bed);

	switch (this->activeScene)
	{
	case RobotDoctorScene::Intro:
		this->robot = Sprite::create(Resources::Cutscenes_RobotDoctor_Doctor);
		this->dialogue = Dialogue::create(Resources::Strings_Dialogue_CutsceneRobotDoctor, Localization::getPixelFont(), Size(visibleSize.width - 48.0f, 256.0f - 48.0f));
		break;
	case RobotDoctorScene::Singularity:
		this->robot = Sprite::create(Resources::Cutscenes_RobotDoctor_DoctorEvil);
		this->dialogue = Dialogue::create(Resources::Strings_Dialogue_CutsceneRobotDoctorSingularity, Localization::getPixelFont(), Size(visibleSize.width - 48.0f, 256.0f - 48.0f));
		break;
	}

	this->dialoguePlate = LayerColor::create(Color4B(0, 0, 0, 196), visibleSize.width, 256.0f);
	this->escapeLabel = Label::create("Press esc to skip", Localization::getPixelFont(), 20.0f, Size::ZERO, TextHAlignment::LEFT);

	this->escapeLabel->setAnchorPoint(Vec2(1.0f, 0.5f));

	this->addChild(this->background);
	this->addChild(this->robot);
	this->addChild(this->bed);
	this->addChild(this->dialoguePlate);
	this->addChild(this->dialogue);
	this->addChild(this->escapeLabel);
}

RobotDoctor::~RobotDoctor()
{
}

void RobotDoctor::onEnter()
{
	CutsceneClip::onEnter();

	this->dialogue->showNextDialogue();

	const float floatOffset = 16.0f;
	const float floatDuration = 2.0f;
	Vec2 initialPosition = this->robot->getPosition();

	this->robot->runAction(RepeatForever::create(Sequence::create(
		MoveTo::create(floatDuration, initialPosition + Vec2(0.0f, floatOffset)),
		MoveTo::create(floatDuration, initialPosition),
		nullptr
	)));
}

void RobotDoctor::initializePositions()
{
	CutsceneClip::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->background->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->robot->setPosition(Vec2(visibleSize.width / 2.0f + 24.0f, visibleSize.height / 2.0f + 96.0f));
	this->bed->setPosition(Vec2(visibleSize.width / 2.0f + 224.0f, visibleSize.height / 2.0f + 8.0f));
	this->dialoguePlate->setPosition(Vec2(visibleSize.width / 2.0f - this->dialoguePlate->getContentSize().width / 2.0f, 0.0f));
	this->dialogue->setPosition(Vec2(24.0f, this->dialoguePlate->getContentSize().height - 24.0f));
	this->escapeLabel->setPosition(Vec2(visibleSize.width - 24.0f, 24.0f));
}

void RobotDoctor::initializeListeners()
{
	CutsceneClip::initializeListeners();

	this->dialogue->setDialogueShownCallback(CC_CALLBACK_0(RobotDoctor::onDialogueShown, this));
}

void RobotDoctor::onDialogueShown()
{
	switch (this->activeScene)
	{
	case RobotDoctorScene::Intro:
		this->dialogue->runAction(Sequence::create(
			DelayTime::create(3.0f),
			CallFunc::create([=]() {
				if (!this->dialogue->showNextDialogue())
				{
					this->endCutsceneClip();
				}
			}),
			nullptr
			));
		break;
	case RobotDoctorScene::Singularity:
		this->dialogue->runAction(Sequence::create(
			DelayTime::create(3.0f),
			CallFunc::create([=]() {
				if (!this->dialogue->showNextDialogue())
				{
					this->endCutsceneClip();
				}
			}),
			nullptr
			));
		break;
	}
}
