#include "HomeAssistantRobot.h"

const Vec2 HomeAssistantRobot::panOffset = Vec2(-608.0f, 256.0f);

HomeAssistantRobot* HomeAssistantRobot::create(HomeAssistantRobotScene homeAssistantRobotScene)
{
	HomeAssistantRobot* instance = new HomeAssistantRobot(homeAssistantRobotScene);

	instance->autorelease();

	return instance;
}

HomeAssistantRobot::HomeAssistantRobot(HomeAssistantRobotScene homeAssistantRobotScene)
{
	this->activeScene = homeAssistantRobotScene;

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->background = Sprite::create(Resources::Cutscenes_HomeAssistant_Kitchen);
	this->brokenPlate = Sprite::create(Resources::Cutscenes_HomeAssistant_BrokenPlate);

	switch (this->activeScene)
	{
	case HomeAssistantRobotScene::Intro:
		this->robot = Sprite::create(Resources::Cutscenes_HomeAssistant_Robot);
		this->dialogue = Dialogue::create(Resources::Strings_Dialogue_CutsceneHomeAssistantRobot, Localization::getPixelFont(), Size(visibleSize.width - 48.0f, 256.0f - 48.0f));
		this->brokenPlate->setVisible(false);
		break;
	case HomeAssistantRobotScene::Singularity:
		this->robot = Sprite::create(Resources::Cutscenes_HomeAssistant_RobotEvil);
		this->dialogue = Dialogue::create(Resources::Strings_Dialogue_CutsceneHomeAssistantRobotSingularity, Localization::getPixelFont(), Size(visibleSize.width - 48.0f, 256.0f - 48.0f));
		break;
	}

	this->dialoguePlate = LayerColor::create(Color4B(0, 0, 0, 196), visibleSize.width, 256.0f);
	this->escapeLabel = Label::create("Press esc to skip", Localization::getPixelFont(), 20.0f, Size::ZERO, TextHAlignment::LEFT);

	this->escapeLabel->setAnchorPoint(Vec2(1.0f, 0.5f));

	this->addChild(InputManager::claimInstance());

	this->addChild(this->background);
	this->addChild(this->robot);
	this->addChild(this->brokenPlate);
	this->addChild(this->dialoguePlate);
	this->addChild(this->dialogue);
	this->addChild(this->escapeLabel);
}

HomeAssistantRobot::~HomeAssistantRobot()
{
}

void HomeAssistantRobot::onEnter()
{
	Cutscene::onEnter();

	this->scheduleUpdate();
	this->initializePositions();
	this->initializeListeners();

	const float duration = 1.5f;
	Vec2 start = this->robot->getPosition();
	Vec2 end = start + Vec2(0.0f, 32.0f);

	this->robot->runAction(RepeatForever::create(Sequence::create(
		EaseSineInOut::create(MoveTo::create(duration, end)),
		EaseSineInOut::create(MoveTo::create(duration, start)),
		nullptr,
		nullptr
	)));
}

void HomeAssistantRobot::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->background->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->robot->setPosition(Vec2(visibleSize.width / 2.0f - 420.0f, visibleSize.height / 2.0f - 96.0f));
	this->brokenPlate->setPosition(Vec2(visibleSize.width / 2.0f - 320.0f, visibleSize.height / 2.0f - 432.0f));
	this->dialoguePlate->setPosition(Vec2(visibleSize.width / 2.0f - this->dialoguePlate->getContentSize().width / 2.0f, 0.0f));
	this->dialogue->setPosition(Vec2(24.0f, this->dialoguePlate->getContentSize().height - 24.0f));
	this->escapeLabel->setPosition(Vec2(visibleSize.width - 24.0f, 24.0f));
}

void HomeAssistantRobot::initializeListeners()
{
	this->getEventDispatcher()->removeEventListenersForTarget(this);

	this->dialogue->setDialogueShownCallback(CC_CALLBACK_0(HomeAssistantRobot::onDialogueShown, this));
}

void HomeAssistantRobot::update(float dt)
{
	FadeScene::update(dt);

	if (InputManager::getInstance()->isPressed(EventKeyboard::KeyCode::KEY_ESCAPE))
	{
		this->endCutscene();
	}
}

void HomeAssistantRobot::endCutscene()
{
	NavigationEvents::loadMap(Resources::Maps_Isometric_Sanctum);
}

void HomeAssistantRobot::onDialogueShown()
{
	this->dialogue->runAction(Sequence::create(
		DelayTime::create(2.0f),
		CallFunc::create([=]() {
			if (!this->dialogue->showNextDialogue())
			{
				switch (this->activeScene)
				{
				case HomeAssistantRobotScene::Intro:
					NavigationEvents::loadCutscene(NavigationEvents::CutsceneEnum::CutsceneRobotDoctor);
					break;
				case HomeAssistantRobotScene::Singularity:
					NavigationEvents::loadCutscene(NavigationEvents::CutsceneEnum::CutsceneRobotDoctorPt2);
					break;
				}
			}
		}),
		nullptr
	));
}
