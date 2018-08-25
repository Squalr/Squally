#include "City.h"

const float City::vaporCorpOffset = 1280;

City* City::create()
{
	City* instance = new City();

	instance->autorelease();

	return instance;
}

City::City()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->sky = LayerGradient::create(Color4B::ORANGE, Color4B(70, 0, 131, 255), Vec2(0.0f, 1.04f));
	this->darkFilter = LayerColor::create(Color4B::BLACK);
	this->cityBackground = InfiniteParallaxNode::create(Resources::Cutscenes_City_CityBackground);
	this->cityMidground = InfiniteParallaxNode::create(Resources::Cutscenes_City_CityMidground);
	this->vaporCorp = Sprite::create(Resources::Cutscenes_City_VaporCorp);
	this->cityForeground = InfiniteParallaxNode::create(Resources::Cutscenes_City_CityForeground);

	// Make this larger than the screen to maximize the initial orange light initially
	this->sky->setContentSize(Size(visibleSize.width, visibleSize.height * 2.0f));
	this->darkFilter->setOpacity(0);

	this->sky->setAnchorPoint(Vec2(0.5f, 1.0f));
	this->cityBackground->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->cityMidground->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->vaporCorp->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->cityForeground->setAnchorPoint(Vec2(0.5f, 0.0f));

	this->cityBackground->setScale(1.0f);
	this->cityMidground->setScale(1.0f);
	this->vaporCorp->setScale(1.0f);
	this->cityForeground->setScale(0.35f);

	this->dialoguePlate = LayerColor::create(Color4B(0, 0, 0, 127), visibleSize.width, 256.0f);
	this->dialogue = Dialogue::loadDialogueFromFile(Resources::Strings_Dialogue_CutsceneCity, Localization::getPixelFont());
	this->escapeLabel = Label::create("Press esc to exit", Localization::getMainFont(), 28.0f, Size::ZERO, TextHAlignment::LEFT);

	this->escapeLabel->setAnchorPoint(Vec2(0.0f, 0.5f));

	this->addChild(InputManager::claimInstance());

	this->addChild(this->sky);
	this->addChild(this->darkFilter);
	this->addChild(this->cityBackground);
	this->addChild(this->cityMidground);
	this->addChild(this->vaporCorp);
	this->addChild(this->cityForeground);
	this->addChild(this->dialoguePlate);
	this->addChild(this->dialogue);
	this->addChild(this->escapeLabel);
}

City::~City()
{
}

void City::onEnter()
{
	Cutscene::onEnter();

	this->scheduleUpdate();
	this->initializePositions();
	this->initializeListeners();

	this->cutscenePan();
}

void City::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->cityBackground->setPosition(Vec2(0.0f, 96.0f));
	this->cityMidground->setPosition(Vec2(212.0f, 0.0f));
	this->vaporCorp->setPosition(Vec2(visibleSize.width / 2.0f + City::vaporCorpOffset, 0.0f));
	this->cityForeground->setPosition(Vec2(0.0f, 0.0f));

	this->dialoguePlate->setPosition(Vec2(visibleSize.width / 2.0f - this->dialoguePlate->getContentSize().width / 2.0f, visibleSize.height - this->dialoguePlate->getContentSize().height));
	this->dialogue->setPosition(Vec2(24.0f, visibleSize.height - 24.0f));
	this->escapeLabel->setPosition(Vec2(visibleSize.width - 128.0f, 48.0f));
}

void City::initializeListeners()
{
	this->getEventDispatcher()->removeEventListenersForTarget(this);
}

void City::update(float dt)
{
	FadeScene::update(dt);

	if (InputManager::getInstance()->isPressed(EventKeyboard::KeyCode::KEY_ESCAPE))
	{
		this->endCutscene();
	}
}

void City::endCutscene()
{
	NavigationEvents::loadMap(Resources::Maps_Isometric_Sanctum);
}

void City::cutscenePan()
{
	CallFunc* panCamera = CallFunc::create([=]()
	{
		const float moveDuration = 5.0f;
		const float deltaX = City::vaporCorpOffset;

		this->sky->runAction(EaseSineInOut::create(ScaleTo::create(moveDuration, 4.0f)));
		this->darkFilter->runAction(EaseSineInOut::create(FadeTo::create(moveDuration, 128)));
		this->cityBackground->runAction(EaseSineInOut::create(MoveTo::create(moveDuration, Vec2(this->cityBackground->getPositionX() - deltaX + 256.0f, this->cityBackground->getPositionY()))));
		this->cityMidground->runAction(EaseSineInOut::create(MoveTo::create(moveDuration, Vec2(this->cityMidground->getPositionX() - deltaX + 128.0f, this->cityMidground->getPositionY()))));
		this->vaporCorp->runAction(EaseSineInOut::create(MoveTo::create(moveDuration, Vec2(this->vaporCorp->getPositionX() - deltaX, this->vaporCorp->getPositionY()))));
		this->cityForeground->runAction(EaseSineInOut::create(MoveTo::create(moveDuration, Vec2(this->cityForeground->getPositionX() - deltaX - 64.0f, this->cityForeground->getPositionY()))));
	});

	this->runAction(Sequence::create(
		panCamera,
		nullptr
	));
}
