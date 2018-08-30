#include "NeonCity.h"

const float NeonCity::vaporCorpOffset = 1280;

NeonCity* NeonCity::create(NeonCityScene neonCityScene)
{
	NeonCity* instance = new NeonCity(neonCityScene);

	instance->autorelease();

	return instance;
}

NeonCity::NeonCity(NeonCityScene neonCityScene)
{
	this->activeScene = neonCityScene;

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->sky = LayerGradient::create(Color4B::ORANGE, Color4B(70, 0, 131, 255), Vec2(0.0f, 1.0f));
	this->darkFilter = LayerColor::create(Color4B::BLACK);
	this->starLayer = StarLayer::create();
	this->cityBackground = InfiniteParallaxNode::create(Resources::Cutscenes_NeonCity_CityBackground);
	this->cityMidground = InfiniteParallaxNode::create(Resources::Cutscenes_NeonCity_CityMidground);
	this->vaporCorp = Sprite::create(Resources::Cutscenes_NeonCity_VaporCorp);
	this->junker1 = FlyingCar::create(FlyingCar::CarType::Junker, Vec2(196.0f, 0.0f));
	this->viper1 = FlyingCar::create(FlyingCar::CarType::Viper, Vec2(-256.0f, 0.0f));
	this->viper2 = FlyingCar::create(FlyingCar::CarType::Viper, Vec2(-256.0f, 0.0f));
	this->propeller1 = FlyingCar::create(FlyingCar::CarType::Propeller, Vec2(172.0f, 0.0f));
	this->cityForeground = InfiniteParallaxNode::create(Resources::Cutscenes_NeonCity_CityForeground);

	// Make this larger than the screen to maximize the initial orange light initially
	this->sky->setContentSize(Size(visibleSize.width, visibleSize.height * 2.0f));
	this->darkFilter->setOpacity(0);
	this->starLayer->setCascadeOpacityEnabled(true);
	this->starLayer->setOpacity(0);

	this->sky->setAnchorPoint(Vec2(0.5f, 1.0f));
	this->cityBackground->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->cityMidground->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->vaporCorp->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->cityForeground->setAnchorPoint(Vec2(0.5f, 0.0f));

	this->cityBackground->setScale(1.0f);
	this->cityMidground->setScale(1.0f);
	this->vaporCorp->setScale(1.0f);
	this->cityForeground->setScale(0.35f);

	this->dialoguePlate = LayerColor::create(Color4B(16, 0, 16, 255), visibleSize.width, 256.0f);
	this->escapeLabel = Label::create("Press esc to skip", Localization::getPixelFont(), 20.0f, Size::ZERO, TextHAlignment::LEFT);

	this->escapeLabel->setAnchorPoint(Vec2(1.0f, 0.5f));

	switch (this->activeScene)
	{
	case NeonCityScene::Intro:
		this->dialogue = Dialogue::create(Resources::Strings_Dialogue_CutsceneNeonCity, Localization::getPixelFont(), Size(visibleSize.width - 48.0f, 256.0f - 48.0f));
		break;
	case NeonCityScene::Return:
		this->dialogue = Dialogue::create(Resources::Strings_Dialogue_CutsceneNeonCityReturn, Localization::getPixelFont(), Size(visibleSize.width - 48.0f, 256.0f - 48.0f));
		break;
	case NeonCityScene::Singularity:
		this->dialogue = Dialogue::create(Resources::Strings_Dialogue_CutsceneNeonCitySingularity, Localization::getPixelFont(), Size(visibleSize.width - 48.0f, 256.0f - 48.0f));
		break;
	}

	this->addChild(InputManager::claimInstance());

	this->addChild(this->sky);
	this->addChild(this->darkFilter);
	this->addChild(this->starLayer);
	this->addChild(this->cityBackground);
	this->addChild(this->cityMidground);
	this->addChild(this->propeller1);
	this->addChild(this->vaporCorp);
	this->addChild(this->junker1);
	this->addChild(this->viper1);
	this->addChild(this->viper2);
	this->addChild(this->cityForeground);
	this->addChild(this->dialoguePlate);
	this->addChild(this->dialogue);
	this->addChild(this->escapeLabel);
}

NeonCity::~NeonCity()
{
}

void NeonCity::onEnter()
{
	Cutscene::onEnter();

	this->scheduleUpdate();
	this->initializePositions();
	this->initializeListeners();

	this->cutscenePan();
}

void NeonCity::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->sky->setPosition(Vec2(0.0f, this->dialoguePlate->getContentSize().height));
	this->cityBackground->setPosition(Vec2(0.0f, this->dialoguePlate->getContentSize().height + 96.0f));
	this->cityMidground->setPosition(Vec2(212.0f, this->dialoguePlate->getContentSize().height));
	this->vaporCorp->setPosition(Vec2(visibleSize.width / 2.0f + NeonCity::vaporCorpOffset, this->dialoguePlate->getContentSize().height));
	this->junker1->setPosition(Vec2(320.0f, visibleSize.height / 2.0f + 24.0f));
	this->viper1->setPosition(Vec2(visibleSize.width / 2.0f + NeonCity::vaporCorpOffset + 640.0f, visibleSize.height / 2.0f + 172.0f));
	this->viper2->setPosition(Vec2(visibleSize.width / 2.0f + NeonCity::vaporCorpOffset + 3072.0f, visibleSize.height / 2.0f + 480.0f));
	this->propeller1->setPosition(Vec2(visibleSize.width / 2.0f + NeonCity::vaporCorpOffset - 512.0f, visibleSize.height / 2.0f + 256.0f));
	this->cityForeground->setPosition(Vec2(0.0f, this->dialoguePlate->getContentSize().height));

	this->dialoguePlate->setPosition(Vec2(visibleSize.width / 2.0f - this->dialoguePlate->getContentSize().width / 2.0f, 0.0f));
	this->dialogue->setPosition(Vec2(24.0f, this->dialoguePlate->getContentSize().height - 24.0f));
	this->escapeLabel->setPosition(Vec2(visibleSize.width - 24.0f, 24.0f));
}

void NeonCity::initializeListeners()
{
	this->getEventDispatcher()->removeEventListenersForTarget(this);

	this->dialogue->setDialogueShownCallback(CC_CALLBACK_0(NeonCity::onDialogueShown, this));
}

void NeonCity::update(float dt)
{
	FadeScene::update(dt);

	if (InputManager::getInstance()->isPressed(EventKeyboard::KeyCode::KEY_ESCAPE))
	{
		this->endCutscene();
	}
}

void NeonCity::endCutscene()
{
	NavigationEvents::loadMap(Resources::Maps_Isometric_Sanctum);
}

void NeonCity::onDialogueShown()
{
	this->dialogue->runAction(Sequence::create(
		DelayTime::create(2.0f),
		CallFunc::create([=]() {
		if (!this->dialogue->showNextDialogue())
		{
			switch(this->activeScene)
			{
			case NeonCityScene::Intro:
				NavigationEvents::loadCutscene(NavigationEvents::CutsceneEnum::CutsceneHomeAssistantRobot);
				break;
			case NeonCityScene::Return:
				NavigationEvents::loadCutscene(NavigationEvents::CutsceneEnum::CutsceneBoardMembers);
				break;
			case NeonCityScene::Singularity:
				NavigationEvents::loadCutscene(NavigationEvents::CutsceneEnum::CutsceneHomeAssistantRobotPt2);
				break;
			}
		}
		}),
		nullptr
	));
}

void NeonCity::cutscenePan()
{
	CallFunc* panCamera = CallFunc::create([=]()
	{
		const float moveDuration = 5.0f;
		const float deltaX = NeonCity::vaporCorpOffset;

		this->sky->runAction(EaseSineInOut::create(ScaleTo::create(moveDuration, 4.0f)));
		this->darkFilter->runAction(EaseSineInOut::create(FadeTo::create(moveDuration, 128)));
		this->starLayer->runAction(Sequence::create(
			DelayTime::create(2.0f),
			EaseSineIn::create(FadeTo::create(moveDuration - 2.0f, 255)),
			nullptr
		));
		this->cityBackground->runAction(EaseSineInOut::create(MoveTo::create(moveDuration, Vec2(this->cityBackground->getPositionX() - deltaX + 256.0f, this->cityBackground->getPositionY()))));
		this->cityMidground->runAction(EaseSineInOut::create(MoveTo::create(moveDuration, Vec2(this->cityMidground->getPositionX() - deltaX + 128.0f, this->cityMidground->getPositionY()))));
		this->vaporCorp->runAction(EaseSineInOut::create(MoveTo::create(moveDuration, Vec2(this->vaporCorp->getPositionX() - deltaX, this->vaporCorp->getPositionY()))));
		this->junker1->runAction(EaseSineInOut::create(MoveBy::create(moveDuration, Vec2(-deltaX, 0.0f))));
		this->viper1->runAction(EaseSineInOut::create(MoveBy::create(moveDuration, Vec2(-deltaX, 0.0f))));
		this->viper2->runAction(EaseSineInOut::create(MoveBy::create(moveDuration, Vec2(-deltaX, 0.0f))));
		this->propeller1->runAction(EaseSineInOut::create(MoveBy::create(moveDuration, Vec2(-deltaX, 0.0f))));
		this->cityForeground->runAction(EaseSineInOut::create(MoveTo::create(moveDuration, Vec2(this->cityForeground->getPositionX() - deltaX - 64.0f, this->cityForeground->getPositionY()))));
	});

	this->runAction(Sequence::create(
		panCamera,
		nullptr
	));
}
