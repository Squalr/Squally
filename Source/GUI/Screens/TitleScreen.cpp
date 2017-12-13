#include "TitleScreen.h"

const int TitleScreen::hackerMode = 0;

TitleScreen::TitleScreen()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->background = Sprite::create(Resources::GUI_TitleScreen_TitleScreen);
	this->titleLabel = new MenuLabel("Squally", Resources::Fonts_Marker_Felt, titleFontSize);
	this->storyModeLabel = new MenuLabel("Story Mode", Resources::Fonts_Marker_Felt, menuFontSize, CC_CALLBACK_1(TitleScreen::OnMenuClick, this));
	this->tutorialModeLabel = new MenuLabel("Tutorial Mode", Resources::Fonts_Marker_Felt, menuFontSize, CC_CALLBACK_1(TitleScreen::OnMenuClick, this));
	this->optionsLabel = new MenuLabel("Options", Resources::Fonts_Marker_Felt, menuFontSize, CC_CALLBACK_1(TitleScreen::OnMenuClick, this));
	this->exitLabel = new MenuLabel("Exit", Resources::Fonts_Marker_Felt, menuFontSize, CC_CALLBACK_1(TitleScreen::OnMenuClick, this));

	std::stringstream stream;
	stream << std::hex << (int)(&this->hackerMode);
	std::string hackerModeAddress(stream.str());

	this->hackerModeLabel = Label::create(hackerModeAddress, Resources::Fonts_arial, 14);
	this->hackerModeLabel->setColor(Color3B(172, 172, 172));

	this->mouse = new Mouse();
	this->clickableMenus = new vector<MenuLabel*>();

	this->hackerModeLabel->setPosition(Vec2(origin.x + visibleSize.width / 2 - 462.0f, origin.x + visibleSize.height / 2 + 320.0f));

	this->titleLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - this->titleLabel->getContentSize().height + menuOffset - spacing * 1.5));
	this->storyModeLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - this->storyModeLabel->getContentSize().height / 2 + menuOffset + spacing * 0));
	this->tutorialModeLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - this->tutorialModeLabel->getContentSize().height / 2 + menuOffset + spacing * 1));
	this->optionsLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - this->tutorialModeLabel->getContentSize().height / 2 + menuOffset + spacing * 2));
	this->exitLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - this->tutorialModeLabel->getContentSize().height / 2 + menuOffset + spacing * 3));
	this->background->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

	this->clickableMenus->push_back(this->storyModeLabel);
	this->clickableMenus->push_back(this->tutorialModeLabel);
	this->clickableMenus->push_back(this->optionsLabel);
	this->clickableMenus->push_back(this->exitLabel);

	this->addChild(this->background);
	this->addChild(this->hackerModeLabel);
	this->addChild(this->titleLabel);
	this->addChild(this->storyModeLabel);
	this->addChild(this->tutorialModeLabel);
	this->addChild(this->optionsLabel);
	this->addChild(this->exitLabel);
	this->addChild(this->mouse);

	this->InitializeListeners();
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
}

void TitleScreen::OnMenuClick(MenuLabel* menuLabel)
{
	if (menuLabel == storyModeLabel)
	{
		Director::getInstance()->replaceScene(new StoryMap());
	}
	else if (menuLabel == tutorialModeLabel)
	{
		Director::getInstance()->replaceScene(new TutorialMap());
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
