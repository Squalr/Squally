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

	this->background = Sprite::create(Resources::Cutscenes_RobotDoctor_RobotDoctor);

	switch (this->activeScene)
	{
	case RobotDoctorScene::Intro:
		this->dialogue = Dialogue::create(Resources::Strings_Dialogue_CutsceneRobotDoctor, Localization::getPixelFont(), Size(visibleSize.width - 48.0f, 256.0f - 48.0f));
		break;
	case RobotDoctorScene::Singularity:
		this->dialogue = Dialogue::create(Resources::Strings_Dialogue_CutsceneRobotDoctorSingularity, Localization::getPixelFont(), Size(visibleSize.width - 48.0f, 256.0f - 48.0f));
		break;
	}

	this->dialoguePlate = LayerColor::create(Color4B(0, 0, 0, 196), visibleSize.width, 256.0f);
	this->escapeLabel = Label::create("Press esc to skip", Localization::getPixelFont(), 20.0f, Size::ZERO, TextHAlignment::LEFT);

	this->escapeLabel->setAnchorPoint(Vec2(1.0f, 0.5f));

	this->addChild(InputManager::claimInstance());

	this->addChild(this->background);
	this->addChild(this->dialoguePlate);
	this->addChild(this->dialogue);
	this->addChild(this->escapeLabel);
}

RobotDoctor::~RobotDoctor()
{
}

void RobotDoctor::onEnter()
{
	Cutscene::onEnter();

	this->scheduleUpdate();
	this->initializePositions();
	this->initializeListeners();
}

void RobotDoctor::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->background->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->dialoguePlate->setPosition(Vec2(visibleSize.width / 2.0f - this->dialoguePlate->getContentSize().width / 2.0f, 0.0f));
	this->dialogue->setPosition(Vec2(24.0f, this->dialoguePlate->getContentSize().height - 24.0f));
	this->escapeLabel->setPosition(Vec2(visibleSize.width - 24.0f, 24.0f));
}

void RobotDoctor::initializeListeners()
{
	this->getEventDispatcher()->removeEventListenersForTarget(this);

	this->dialogue->setDialogueShownCallback(CC_CALLBACK_0(RobotDoctor::onDialogueShown, this));
}

void RobotDoctor::update(float dt)
{
	FadeScene::update(dt);

	if (InputManager::getInstance()->isPressed(EventKeyboard::KeyCode::KEY_ESCAPE))
	{
		this->endCutscene();
	}
}

void RobotDoctor::endCutscene()
{
	NavigationEvents::loadMap(Resources::Maps_Isometric_Sanctum);
}

void RobotDoctor::onDialogueShown()
{
	this->dialogue->runAction(Sequence::create(
		DelayTime::create(2.0f),
		CallFunc::create([=]() {
			if (!this->dialogue->showNextDialogue())
			{
				switch(this->activeScene)
				{
				case RobotDoctorScene::Intro:
					NavigationEvents::loadCutscene(NavigationEvents::CutsceneEnum::CutsceneNeonCityPt2);
					break;
				case RobotDoctorScene::Singularity:
					NavigationEvents::loadCutscene(NavigationEvents::CutsceneEnum::CutsceneVaporWeb);
					break;
				}
			}
		}),
		nullptr
	));
}
