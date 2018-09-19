#include "MinigamesMenu.h"

const std::string MinigamesMenu::StringKeyHexus = "Menu_Hexus";
const std::string MinigamesMenu::StringKeyHexusPuzzles = "Menu_Hexus_Puzzles";
const std::string MinigamesMenu::StringKeyComingSoon = "Menu_Coming_Soon";

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
	const Size shadowSize = Size(-2.0f, -2.0f);
	const int shadowBlur = 2;
	const int hoverOutlineSize = 2;
	const Color3B textColor = Color3B::WHITE;
	const Color4B shadowColor = Color4B::BLACK;
	const Color3B highlightColor = Color3B::YELLOW;
	const Color4B glowColor = Color4B::ORANGE;
	const Vec2 labelOffset = Vec2(48.0f, 0.0f);

	this->background = Node::create();
	this->scrollPane = ScrollPane::create(Size(1152.0f, 768.0f), Color4B(0, 0, 0, 127));

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

	this->hexusButton->setTextOffset(labelOffset);

	Sprite* hexusIcon = Sprite::create(Resources::Menus_Icons_Banner);

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

	this->hexusPuzzlesButton->setTextOffset(labelOffset);

	Sprite* hexusPuzzlesIcon = Sprite::create(Resources::Menus_Icons_Gauntlet);

	hexusPuzzlesIcon->setAnchorPoint(Vec2(0.0f, 0.5f));
	hexusPuzzlesIcon->setPosition(Vec2(-this->hexusPuzzlesButton->getContentSize().width / 2.0f + 78.0f, 0.0f));

	this->hexusPuzzlesButton->addChild(hexusPuzzlesIcon);

	this->comingSoonButton1 = Node::create();
	this->comingSoonButton2 = Node::create();
	this->comingSoonButton3 = Node::create();
	this->comingSoonButton4 = Node::create();
	this->comingSoonButton5 = Node::create();
	this->comingSoonButton6 = Node::create();

	this->comingSoonButton1->addChild(Sprite::create(Resources::Menus_MinigamesMenu_BannerGray));
	this->comingSoonButton2->addChild(Sprite::create(Resources::Menus_MinigamesMenu_BannerGray));
	this->comingSoonButton3->addChild(Sprite::create(Resources::Menus_MinigamesMenu_BannerGray));
	this->comingSoonButton4->addChild(Sprite::create(Resources::Menus_MinigamesMenu_BannerGray));
	this->comingSoonButton5->addChild(Sprite::create(Resources::Menus_MinigamesMenu_BannerGray));
	this->comingSoonButton6->addChild(Sprite::create(Resources::Menus_MinigamesMenu_BannerGray));

	Label* comingSoon1 = Label::create(Localization::resolveString(MinigamesMenu::StringKeyComingSoon), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	Label* comingSoon2 = Label::create(Localization::resolveString(MinigamesMenu::StringKeyComingSoon), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	Label* comingSoon3 = Label::create(Localization::resolveString(MinigamesMenu::StringKeyComingSoon), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	Label* comingSoon4 = Label::create(Localization::resolveString(MinigamesMenu::StringKeyComingSoon), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	Label* comingSoon5 = Label::create(Localization::resolveString(MinigamesMenu::StringKeyComingSoon), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	Label* comingSoon6 = Label::create(Localization::resolveString(MinigamesMenu::StringKeyComingSoon), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));

	comingSoon1->setPosition(labelOffset);
	comingSoon2->setPosition(labelOffset);
	comingSoon3->setPosition(labelOffset);
	comingSoon4->setPosition(labelOffset);
	comingSoon5->setPosition(labelOffset);
	comingSoon6->setPosition(labelOffset);

	comingSoon1->setTextColor(Color4B::GRAY);
	comingSoon2->setTextColor(Color4B::GRAY);
	comingSoon3->setTextColor(Color4B::GRAY);
	comingSoon4->setTextColor(Color4B::GRAY);
	comingSoon5->setTextColor(Color4B::GRAY);
	comingSoon6->setTextColor(Color4B::GRAY);

	this->comingSoonButton1->addChild(comingSoon1);
	this->comingSoonButton2->addChild(comingSoon2);
	this->comingSoonButton3->addChild(comingSoon3);
	this->comingSoonButton4->addChild(comingSoon4);
	this->comingSoonButton5->addChild(comingSoon5);
	this->comingSoonButton6->addChild(comingSoon6);

	this->addChild(this->background);
	this->scrollPane->addChild(this->hexusButton);
	this->scrollPane->addChild(this->hexusPuzzlesButton);
	this->scrollPane->addChild(this->comingSoonButton1);
	this->scrollPane->addChild(this->comingSoonButton2);
	this->scrollPane->addChild(this->comingSoonButton3);
	this->scrollPane->addChild(this->comingSoonButton4);
	this->scrollPane->addChild(this->comingSoonButton5);
	this->scrollPane->addChild(this->comingSoonButton6);
	this->addChild(this->scrollPane);
	this->addChild(Mouse::create());
}

MinigamesMenu::~MinigamesMenu()
{
}

void MinigamesMenu::onEnter()
{
	FadeScene::onEnter();

	this->background->addChild(MenuBackground::claimInstance());

	const float delay = 0.5f;
	const float duration = 0.75f;

	GameUtils::fadeInObject(this->scrollPane, delay, duration);
	GameUtils::fadeInObject(this->hexusButton, delay, duration);
	GameUtils::fadeInObject(this->hexusPuzzlesButton, delay, duration);
	GameUtils::fadeInObject(this->comingSoonButton1, delay, duration);
	GameUtils::fadeInObject(this->comingSoonButton2, delay, duration);
	GameUtils::fadeInObject(this->comingSoonButton3, delay, duration);
	GameUtils::fadeInObject(this->comingSoonButton4, delay, duration);
	GameUtils::fadeInObject(this->comingSoonButton5, delay, duration);
	GameUtils::fadeInObject(this->comingSoonButton6, delay, duration);

	this->scheduleUpdate();
}

void MinigamesMenu::initializeListeners()
{
	FadeScene::initializeListeners();

	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = CC_CALLBACK_2(MinigamesMenu::onKeyPressed, this);
	this->hexusButton->setClickCallback(CC_CALLBACK_1(MinigamesMenu::onHexusClick, this));
	this->hexusPuzzlesButton->setClickCallback(CC_CALLBACK_1(MinigamesMenu::onHexusPuzzlesClick, this));

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

void MinigamesMenu::initializePositions()
{
	FadeScene::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Size paneSize = this->scrollPane->getPaneSize();
	MenuBackground::getInstance()->initializePositions();

	this->scrollPane->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));

	this->hexusButton->setPosition(Vec2(paneSize.width / 2.0f, 192.0f * 0 + 128.0f));
	this->hexusPuzzlesButton->setPosition(Vec2(paneSize.width / 2.0f, 192.0f * 1 + 128.0f));
	this->comingSoonButton1->setPosition(Vec2(paneSize.width / 2.0f, 192.0f * 2 + 128.0f));
	this->comingSoonButton2->setPosition(Vec2(paneSize.width / 2.0f, 192.0f * 3 + 128.0f));
	this->comingSoonButton3->setPosition(Vec2(paneSize.width / 2.0f, 192.0f * 4 + 128.0f));
	this->comingSoonButton4->setPosition(Vec2(paneSize.width / 2.0f, 192.0f * 5 + 128.0f));
	this->comingSoonButton5->setPosition(Vec2(paneSize.width / 2.0f, 192.0f * 6 + 128.0f));
	this->comingSoonButton6->setPosition(Vec2(paneSize.width / 2.0f, 192.0f * 7 + 128.0f));
	this->scrollPane->fitSizeToContent();
}

void MinigamesMenu::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
		case EventKeyboard::KeyCode::KEY_ESCAPE:
			event->stopPropagation();
			NavigationEvents::navigateBack();
			break;
		default:
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
