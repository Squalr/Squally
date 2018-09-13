#include "MinigamesMenu.h"

const std::string MinigamesMenu::StringKeyHexus = "Menu_Minigame_Hexus";
const std::string MinigamesMenu::StringKeyHexusPuzzles = "Menu_Minigame_Hexus_Puzzles";
const std::string MinigamesMenu::StringKeyUnknown = "Menu_Minigame_Unknown";

const float MinigamesMenu::titleFontSize = 64.0f;
const float MinigamesMenu::menuFontSize = 48.0f;
const float MinigamesMenu::menuOffset = 128.0f;
const float MinigamesMenu::spacing = -96.0f;

MinigamesMenu * MinigamesMenu::create()
{
	MinigamesMenu* instance = new MinigamesMenu();

	instance->autorelease();

	return instance;
}

MinigamesMenu::MinigamesMenu()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	Size shadowSize = Size(-4.0f, -4.0f);
	int shadowBlur = 2;
	int hoverOutlineSize = 2;
	Color3B textColor = Color3B::WHITE;
	Color4B shadowColor = Color4B::BLACK;
	Color3B highlightColor = Color3B::YELLOW;
	Color4B glowColor = Color4B::ORANGE;

	this->background = MenuBackground::claimInstance();

	this->scrollView = ScrollView::create();
	this->scrollView->setCascadeOpacityEnabled(true);

	LayerColor* background = LayerColor::create(Color4B(0, 0, 0, 127), visibleSize.width, visibleSize.height * 2);

	Label* hexusLabel = Label::create(Localization::resolveString(MinigamesMenu::StringKeyHexus), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	Label* hexusLabelHover = Label::create(Localization::resolveString(MinigamesMenu::StringKeyHexus), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	Label* hexusLabelClicked = Label::create(Localization::resolveString(MinigamesMenu::StringKeyHexus), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));

	hexusLabel->setColor(textColor);
	hexusLabel->enableShadow(shadowColor, shadowSize, shadowBlur);
	hexusLabel->enableGlow(shadowColor);

	hexusLabelHover->setColor(highlightColor);
	hexusLabelHover->enableShadow(shadowColor, shadowSize, shadowBlur);
	hexusLabelHover->enableGlow(glowColor);

	hexusLabelClicked->setColor(highlightColor);
	hexusLabelClicked->enableShadow(shadowColor, shadowSize, shadowBlur);
	hexusLabelClicked->enableGlow(glowColor);

	this->hexusButton = TextMenuSprite::create(
		hexusLabel,
		hexusLabelHover,
		hexusLabelClicked,
		Resources::Menus_MinigamesMenu_Banner,
		Resources::Menus_MinigamesMenu_BannerHover,
		Resources::Menus_MinigamesMenu_BannerClick);

	Sprite* hexusIcon = Sprite::create(Resources::Menus_HackerModeMenu_Icons_Banner);

	hexusIcon->setAnchorPoint(Vec2(0.0f, 0.5f));
	hexusIcon->setPosition(Vec2(-this->hexusButton->getContentSize().width / 2.0f + 78.0f, 0.0f));

	this->hexusButton->addChild(hexusIcon);

	Label* hexusPuzzlesLabel = Label::create(Localization::resolveString(MinigamesMenu::StringKeyHexusPuzzles), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	Label* hexusPuzzlesLabelHover = Label::create(Localization::resolveString(MinigamesMenu::StringKeyHexusPuzzles), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	Label* hexusPuzzlesLabelClicked = Label::create(Localization::resolveString(MinigamesMenu::StringKeyHexusPuzzles), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));

	hexusPuzzlesLabel->setColor(textColor);
	hexusPuzzlesLabel->enableShadow(shadowColor, shadowSize, shadowBlur);
	hexusPuzzlesLabel->enableGlow(shadowColor);

	hexusPuzzlesLabelHover->setColor(highlightColor);
	hexusPuzzlesLabelHover->enableShadow(shadowColor, shadowSize, shadowBlur);
	hexusPuzzlesLabelHover->enableGlow(glowColor);

	hexusPuzzlesLabelClicked->setColor(highlightColor);
	hexusPuzzlesLabelClicked->enableShadow(shadowColor, shadowSize, shadowBlur);
	hexusPuzzlesLabelClicked->enableGlow(glowColor);

	this->hexusPuzzlesButton = TextMenuSprite::create(
		hexusPuzzlesLabel,
		hexusPuzzlesLabelHover,
		hexusPuzzlesLabelClicked,
		Resources::Menus_MinigamesMenu_Banner,
		Resources::Menus_MinigamesMenu_BannerHover,
		Resources::Menus_MinigamesMenu_BannerClick);

	Sprite* hexusPuzzlesIcon = Sprite::create(Resources::Menus_HackerModeMenu_Icons_Gauntlet);

	hexusPuzzlesIcon->setAnchorPoint(Vec2(0.0f, 0.5f));
	hexusPuzzlesIcon->setPosition(Vec2(-this->hexusPuzzlesButton->getContentSize().width / 2.0f + 78.0f, 0.0f));

	this->hexusPuzzlesButton->addChild(hexusPuzzlesIcon);

	this->unknownButton1 = Node::create();
	this->unknownButton2 = Node::create();
	this->unknownButton3 = Node::create();
	this->unknownButton4 = Node::create();
	this->unknownButton5 = Node::create();
	this->unknownButton6 = Node::create();

	this->unknownButton1->addChild(Sprite::create(Resources::Menus_MinigamesMenu_BannerGray));
	this->unknownButton2->addChild(Sprite::create(Resources::Menus_MinigamesMenu_BannerGray));
	this->unknownButton3->addChild(Sprite::create(Resources::Menus_MinigamesMenu_BannerGray));
	this->unknownButton4->addChild(Sprite::create(Resources::Menus_MinigamesMenu_BannerGray));
	this->unknownButton5->addChild(Sprite::create(Resources::Menus_MinigamesMenu_BannerGray));
	this->unknownButton6->addChild(Sprite::create(Resources::Menus_MinigamesMenu_BannerGray));

	Label* comingSoon1 = Label::create(Localization::resolveString(MinigamesMenu::StringKeyUnknown), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	Label* comingSoon2 = Label::create(Localization::resolveString(MinigamesMenu::StringKeyUnknown), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	Label* comingSoon3 = Label::create(Localization::resolveString(MinigamesMenu::StringKeyUnknown), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	Label* comingSoon4 = Label::create(Localization::resolveString(MinigamesMenu::StringKeyUnknown), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	Label* comingSoon5 = Label::create(Localization::resolveString(MinigamesMenu::StringKeyUnknown), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	Label* comingSoon6 = Label::create(Localization::resolveString(MinigamesMenu::StringKeyUnknown), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));

	comingSoon1->setTextColor(Color4B::GRAY);
	comingSoon2->setTextColor(Color4B::GRAY);
	comingSoon3->setTextColor(Color4B::GRAY);
	comingSoon4->setTextColor(Color4B::GRAY);
	comingSoon5->setTextColor(Color4B::GRAY);
	comingSoon6->setTextColor(Color4B::GRAY);

	this->unknownButton1->addChild(comingSoon1);
	this->unknownButton2->addChild(comingSoon2);
	this->unknownButton3->addChild(comingSoon3);
	this->unknownButton4->addChild(comingSoon4);
	this->unknownButton5->addChild(comingSoon5);
	this->unknownButton6->addChild(comingSoon6);

	this->scrollView->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->scrollView->setDirection(SCROLLVIEW_DIR_VERTICAL);

	this->addChild(this->background);
	this->scrollView->addChild(background);
	this->scrollView->addChild(this->hexusButton);
	this->scrollView->addChild(this->hexusPuzzlesButton);
	this->scrollView->addChild(this->unknownButton1);
	this->scrollView->addChild(this->unknownButton2);
	this->scrollView->addChild(this->unknownButton3);
	this->scrollView->addChild(this->unknownButton4);
	this->scrollView->addChild(this->unknownButton5);
	this->scrollView->addChild(this->unknownButton6);
	this->addChild(this->scrollView);
	this->addChild(Mouse::create());
}

MinigamesMenu::~MinigamesMenu()
{
}

void MinigamesMenu::onEnter()
{
	FadeScene::onEnter();

	this->initializePositions();
	this->initializeListeners();

	const float delay = 0.5f;
	const float duration = 0.75f;

	GameUtils::fadeInObject(this->scrollView, delay, duration);
	GameUtils::fadeInObject(this->hexusButton, delay, duration);
	GameUtils::fadeInObject(this->hexusPuzzlesButton, delay, duration);
	GameUtils::fadeInObject(this->unknownButton1, delay, duration);
	GameUtils::fadeInObject(this->unknownButton2, delay, duration);
	GameUtils::fadeInObject(this->unknownButton3, delay, duration);
	GameUtils::fadeInObject(this->unknownButton4, delay, duration);
	GameUtils::fadeInObject(this->unknownButton5, delay, duration);
	GameUtils::fadeInObject(this->unknownButton6, delay, duration);

	this->scheduleUpdate();
}

void MinigamesMenu::initializeListeners()
{
	this->getEventDispatcher()->removeEventListenersForTarget(this);

	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = CC_CALLBACK_2(MinigamesMenu::onKeyPressed, this);
	this->hexusButton->setClickCallback(CC_CALLBACK_1(MinigamesMenu::onHexusClick, this));
	this->hexusPuzzlesButton->setClickCallback(CC_CALLBACK_1(MinigamesMenu::onHexusPuzzlesClick, this));

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

void MinigamesMenu::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Size innerSize = Size(visibleSize.width / 2.0f + 256.0f, visibleSize.height / 2.0f + 896.0f);

	MenuBackground::getInstance()->initializePositions();

	this->scrollView->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->scrollView->setSize(Size(innerSize.width, visibleSize.height / 2.0f));
	this->scrollView->setInnerContainerSize(innerSize);

	this->hexusButton->setPosition(Vec2(innerSize.width / 2.0f, innerSize.height - 192.0f * 1 + 64.0f));
	this->hexusPuzzlesButton->setPosition(Vec2(innerSize.width / 2.0f, innerSize.height - 192.0f * 2 + 64.0f));
	this->unknownButton1->setPosition(Vec2(innerSize.width / 2.0f, innerSize.height - 192.0f * 3 + 64.0f));
	this->unknownButton2->setPosition(Vec2(innerSize.width / 2.0f, innerSize.height - 192.0f * 4 + 64.0f));
	this->unknownButton3->setPosition(Vec2(innerSize.width / 2.0f, innerSize.height - 192.0f * 5 + 64.0f));
	this->unknownButton4->setPosition(Vec2(innerSize.width / 2.0f, innerSize.height - 192.0f * 6 + 64.0f));
	this->unknownButton5->setPosition(Vec2(innerSize.width / 2.0f, innerSize.height - 192.0f * 7 + 64.0f));
	this->unknownButton6->setPosition(Vec2(innerSize.width / 2.0f, innerSize.height - 192.0f * 8 + 64.0f));
}

void MinigamesMenu::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		event->stopPropagation();
		NavigationEvents::navigateBack();
		break;
	}
}

void MinigamesMenu::onHexusClick(MenuSprite* menuSprite)
{
	NavigationEvents::navigate(NavigationEvents::GameScreen::Minigames_Hexus);
}

void MinigamesMenu::onHexusPuzzlesClick(MenuSprite* menuSprite)
{
	NavigationEvents::navigate(NavigationEvents::GameScreen::Minigames_Hexus_Puzzles);
}
