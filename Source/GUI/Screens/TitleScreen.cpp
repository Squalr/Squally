#include "TitleScreen.h"

int TitleScreen::hackerMode = 1;

TitleScreen::TitleScreen()
{
	SimpleAudioEngine* audio = SimpleAudioEngine::getInstance();
	audio->preloadBackgroundMusic(Resources::Music_Will_we_get_there_Together.c_str());
	audio->playBackgroundMusic(Resources::Music_Will_we_get_there_Together.c_str(), true);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->background = Sprite::create(Resources::Menus_TitleScreen_TitleScreen);
	this->squally = Sprite::create(Resources::Menus_TitleScreen_Squally);
	this->titleLabel = new MenuLabel("Squally", Resources::Fonts_Marker_Felt, titleFontSize);
	this->storyModeLabel = new MenuLabel("Story Mode", Resources::Fonts_Marker_Felt, menuFontSize, CC_CALLBACK_1(TitleScreen::OnMenuClick, this));
	this->optionsLabel = new MenuLabel("Options", Resources::Fonts_Marker_Felt, menuFontSize, CC_CALLBACK_1(TitleScreen::OnMenuClick, this));
	this->exitLabel = new MenuLabel("Exit", Resources::Fonts_Marker_Felt, menuFontSize, CC_CALLBACK_1(TitleScreen::OnMenuClick, this));
	this->monitor = new MenuSprite(Resources::Menus_TitleScreen_Monitor, Resources::Menus_TitleScreen_MonitorSelected, CC_CALLBACK_1(TitleScreen::OnTutorialClick, this));

	std::stringstream stream;
	stream << std::hex << (int)(&this->hackerMode);
	std::string hackerModeAddress = stream.str();
	std::transform(hackerModeAddress.begin(), hackerModeAddress.end(), hackerModeAddress.begin(), ::toupper);

	this->hackerModeLabel = Label::create(hackerModeAddress, Resources::Fonts_Stormblade, 16);
	this->hackerModeLabel->setColor(Color3B(173, 135, 108));
	this->hackerModeLabel->setSkewX(-12.0f);

	this->mouse = new Mouse();
	this->clickableMenus = new vector<MenuLabel*>();

	this->hackerModeLabel->setPosition(Vec2(origin.x + visibleSize.width / 2 - 96.0f, origin.x + visibleSize.height / 2 + 296.0f));

	this->monitor->setPosition(Vec2(origin.x + visibleSize.width / 2 + 4.0f, origin.y + visibleSize.height / 2 - this->monitor->getContentSize().height + 384.0f));
	this->titleLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - this->titleLabel->getContentSize().height + menuOffset - spacing * 1.5));
	this->storyModeLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - this->storyModeLabel->getContentSize().height / 2 + menuOffset + spacing * 0));
	this->optionsLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - this->optionsLabel->getContentSize().height / 2 + menuOffset + spacing * 1));
	this->exitLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - this->exitLabel->getContentSize().height / 2 + menuOffset + spacing * 2));
	this->background->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->squally->setPosition(Vec2(origin.x + visibleSize.width / 2 - 240.0f, origin.y + visibleSize.height / 2 - 32.0f));

	this->clickableMenus->push_back(this->storyModeLabel);
	this->clickableMenus->push_back(this->optionsLabel);
	this->clickableMenus->push_back(this->exitLabel);

	this->addChild(this->background);
	this->addChild(this->squally);
	this->addChild(this->monitor);
	this->addChild(this->hackerModeLabel);
	this->addChild(this->titleLabel);
	this->addChild(this->storyModeLabel);
	this->addChild(this->optionsLabel);
	this->addChild(this->exitLabel);
	this->addChild(this->mouse);

	this->monitor->setVisible(false);

	this->scheduleUpdate();
}

TitleScreen::~TitleScreen()
{
	delete(this->mouse);

	for (std::vector<MenuLabel*>::iterator it = this->clickableMenus->begin(); it != this->clickableMenus->end(); ++it)
	{
		MenuLabel* label = *it;
		delete(label);
	}

	delete(this->clickableMenus);
}

void TitleScreen::onEnter()
{
	Scene::onEnter();

	this->InitializeListeners();

	float distanceX = 8.0f;
	float distanceY = 64.0f;
	float speedX = 3.5f;
	float speedY = 8.0f;

	FiniteTimeAction* bounceX1 = EaseSineInOut::create(MoveBy::create(speedX, Vec2(distanceX, 0.0f)));
	FiniteTimeAction* bounceX2 = EaseSineInOut::create(MoveBy::create(speedX, Vec2(-distanceX, 0.0f)));
	FiniteTimeAction* bounceY1 = EaseSineInOut::create(MoveBy::create(speedY, Vec2(0.0f, distanceY)));
	FiniteTimeAction* bounceY2 = EaseSineInOut::create(MoveBy::create(speedY, Vec2(0.0f, -distanceY)));

	this->squally->runAction(RepeatForever::create(Sequence::create(bounceX1, bounceX2, nullptr)));
	this->squally->runAction(RepeatForever::create(Sequence::create(bounceY1, bounceY2, nullptr)));
}

void TitleScreen::update(float dt)
{
	Scene::update(dt);

	if (this->hackerMode != 0 && !this->monitor->isVisible())
	{
		this->monitor->setVisible(true);
	}
}

void TitleScreen::OnTutorialClick(MenuSprite* menuSprite)
{
	if (menuSprite == monitor)
	{
		Director::getInstance()->replaceScene(new TutorialMap());
	}
}

void TitleScreen::OnMenuClick(MenuLabel* menuLabel)
{
	if (menuLabel == storyModeLabel)
	{
		Director::getInstance()->replaceScene(new StoryMap());
	}
	else if (menuLabel == optionsLabel)
	{
		Director::getInstance()->replaceScene(new OptionsMenu());
	}
	else if (menuLabel == exitLabel)
	{
		CCDirector::getInstance()->end();
	}
}

void TitleScreen::InitializeListeners()
{
	EventListenerMouse* mouseListener = EventListenerMouse::create();

	mouseListener->onMouseMove = CC_CALLBACK_1(TitleScreen::OnMouseMove, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

void TitleScreen::OnMouseMove(EventMouse* event)
{
	this->mouse->SetCanClick(false);

	for (std::vector<MenuLabel*>::iterator it = this->clickableMenus->begin(); it != this->clickableMenus->end(); ++it)
	{
		MenuLabel* label = *it;

		if (Utils::Intersects(label, Vec2(event->getCursorX(), event->getCursorY())))
		{
			this->mouse->SetCanClick(true);
			return;
		}
	}
}
