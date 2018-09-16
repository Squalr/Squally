#include "SaveSelectMenu.h"

const std::string SaveSelectMenu::StringKeyNewGame = "Menu_New_Game";
const std::string SaveSelectMenu::StringKeyContinueGame = "Menu_Continue_Game";

const float SaveSelectMenu::titleFontSize = 64.0f;
const float SaveSelectMenu::menuFontSize = 48.0f;
const float SaveSelectMenu::menuOffset = 128.0f;
const float SaveSelectMenu::spacing = -96.0f;

SaveSelectMenu * SaveSelectMenu::create()
{
	SaveSelectMenu* instance = new SaveSelectMenu();

	instance->autorelease();

	return instance;
}

SaveSelectMenu::SaveSelectMenu()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	const Size shadowSize = Size(-2.0f, -2.0f);
	const int shadowBlur = 2;
	const int hoverOutlineSize = 2;
	const Color3B textColor = Color3B::WHITE;
	const Color4B shadowColor = Color4B::BLACK;
	const Color3B highlightColor = Color3B::YELLOW;
	const Color4B glowColor = Color4B::ORANGE;
	const Vec2 labelOffset = Vec2(48.0f, 0.0f);

	this->background = Node::create();

	LayerColor* background = LayerColor::create(Color4B(0, 0, 0, 127), visibleSize.width, visibleSize.height * 2);

	Label* saveGame1Label = Label::create(Localization::resolveString(SaveSelectMenu::StringKeyContinueGame), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	Label* saveGame1LabelHover = Label::create(Localization::resolveString(SaveSelectMenu::StringKeyContinueGame), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	Label* saveGame1LabelClicked = Label::create(Localization::resolveString(SaveSelectMenu::StringKeyContinueGame), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));

	saveGame1Label->setColor(textColor);
	saveGame1Label->enableShadow(shadowColor, shadowSize, shadowBlur);
	saveGame1Label->enableGlow(shadowColor);

	saveGame1LabelHover->setColor(highlightColor);
	saveGame1LabelHover->enableShadow(shadowColor, shadowSize, shadowBlur);
	saveGame1LabelHover->enableGlow(glowColor);

	saveGame1LabelClicked->setColor(highlightColor);
	saveGame1LabelClicked->enableShadow(shadowColor, shadowSize, shadowBlur);
	saveGame1LabelClicked->enableGlow(glowColor);

	this->saveGame1 = TextMenuSprite::create(
		saveGame1Label,
		saveGame1LabelHover,
		saveGame1LabelClicked,
		Resources::Menus_MinigamesMenu_Banner,
		Resources::Menus_MinigamesMenu_BannerHover,
		Resources::Menus_MinigamesMenu_BannerClick);

	this->saveGame1->setTextOffset(labelOffset);

	Sprite* saveGame1Icon = Sprite::create(Resources::Menus_HackerModeMenu_Icons_BookSpellsArcane);

	saveGame1Icon->setAnchorPoint(Vec2(0.0f, 0.5f));
	saveGame1Icon->setPosition(Vec2(-this->saveGame1->getContentSize().width / 2.0f + 78.0f, 0.0f));

	this->saveGame1->addChild(saveGame1Icon);

	Label* saveGame2Label = Label::create(Localization::resolveString(SaveSelectMenu::StringKeyNewGame), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	Label* saveGame2LabelHover = Label::create(Localization::resolveString(SaveSelectMenu::StringKeyNewGame), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	Label* saveGame2LabelClicked = Label::create(Localization::resolveString(SaveSelectMenu::StringKeyNewGame), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));

	saveGame2Label->setColor(textColor);
	saveGame2Label->enableShadow(shadowColor, shadowSize, shadowBlur);
	saveGame2Label->enableGlow(shadowColor);

	saveGame2LabelHover->setColor(highlightColor);
	saveGame2LabelHover->enableShadow(shadowColor, shadowSize, shadowBlur);
	saveGame2LabelHover->enableGlow(glowColor);

	saveGame2LabelClicked->setColor(highlightColor);
	saveGame2LabelClicked->enableShadow(shadowColor, shadowSize, shadowBlur);
	saveGame2LabelClicked->enableGlow(glowColor);

	this->saveGame2 = TextMenuSprite::create(
		saveGame2Label,
		saveGame2LabelHover,
		saveGame2LabelClicked,
		Resources::Menus_MinigamesMenu_Banner,
		Resources::Menus_MinigamesMenu_BannerHover,
		Resources::Menus_MinigamesMenu_BannerClick);

	this->saveGame2->setTextOffset(labelOffset);

	Sprite* saveGame2Icon = Sprite::create(Resources::Menus_HackerModeMenu_Icons_Health);

	saveGame2Icon->setAnchorPoint(Vec2(0.0f, 0.5f));
	saveGame2Icon->setPosition(Vec2(-this->saveGame2->getContentSize().width / 2.0f + 78.0f, 0.0f));

	this->saveGame2->addChild(saveGame2Icon);

	Label* saveGame3Label = Label::create(Localization::resolveString(SaveSelectMenu::StringKeyNewGame), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	Label* saveGame3LabelHover = Label::create(Localization::resolveString(SaveSelectMenu::StringKeyNewGame), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	Label* saveGame3LabelClicked = Label::create(Localization::resolveString(SaveSelectMenu::StringKeyNewGame), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));

	saveGame3Label->setColor(textColor);
	saveGame3Label->enableShadow(shadowColor, shadowSize, shadowBlur);
	saveGame3Label->enableGlow(shadowColor);

	saveGame3LabelHover->setColor(highlightColor);
	saveGame3LabelHover->enableShadow(shadowColor, shadowSize, shadowBlur);
	saveGame3LabelHover->enableGlow(glowColor);

	saveGame3LabelClicked->setColor(highlightColor);
	saveGame3LabelClicked->enableShadow(shadowColor, shadowSize, shadowBlur);
	saveGame3LabelClicked->enableGlow(glowColor);

	this->saveGame3 = TextMenuSprite::create(
		saveGame3Label,
		saveGame3LabelHover,
		saveGame3LabelClicked,
		Resources::Menus_MinigamesMenu_Banner,
		Resources::Menus_MinigamesMenu_BannerHover,
		Resources::Menus_MinigamesMenu_BannerClick);

	this->saveGame3->setTextOffset(labelOffset);

	Sprite* saveGame3Icon = Sprite::create(Resources::Menus_HackerModeMenu_Icons_Health);

	saveGame3Icon->setAnchorPoint(Vec2(0.0f, 0.5f));
	saveGame3Icon->setPosition(Vec2(-this->saveGame3->getContentSize().width / 2.0f + 78.0f, 0.0f));

	this->saveGame3->addChild(saveGame3Icon);

	this->addChild(this->background);
	this->addChild(this->saveGame1);
	this->addChild(this->saveGame2);
	this->addChild(this->saveGame3);
	this->addChild(Mouse::create());
}

SaveSelectMenu::~SaveSelectMenu()
{
}

void SaveSelectMenu::onEnter()
{
	FadeScene::onEnter();

	this->background->addChild(MenuBackground::claimInstance());

	this->initializePositions();
	this->initializeListeners();

	const float delay = 0.5f;
	const float duration = 0.75f;

	GameUtils::fadeInObject(this->saveGame1, delay, duration);
	GameUtils::fadeInObject(this->saveGame2, delay, duration);
	GameUtils::fadeInObject(this->saveGame3, delay, duration);

	this->scheduleUpdate();
}

void SaveSelectMenu::initializeListeners()
{
	this->getEventDispatcher()->removeEventListenersForTarget(this);

	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = CC_CALLBACK_2(SaveSelectMenu::onKeyPressed, this);
	this->saveGame1->setClickCallback(CC_CALLBACK_1(SaveSelectMenu::onSaveGame1Click, this));
	this->saveGame2->setClickCallback(CC_CALLBACK_1(SaveSelectMenu::onSaveGame2Click, this));
	this->saveGame3->setClickCallback(CC_CALLBACK_1(SaveSelectMenu::onSaveGame3Click, this));

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

void SaveSelectMenu::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	MenuBackground::getInstance()->initializePositions();

	this->saveGame1->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 192.0f));
	this->saveGame2->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - 0.0f));
	this->saveGame3->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - 192.0f));
}

void SaveSelectMenu::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		event->stopPropagation();
		NavigationEvents::navigateBack();
		break;
	}
}

void SaveSelectMenu::onSaveGame1Click(MenuSprite* menuSprite)
{
	NavigationEvents::navigate(NavigationEvents::GameScreen::StoryMap);
}

void SaveSelectMenu::onSaveGame2Click(MenuSprite* menuSprite)
{
	NavigationEvents::loadCutscene(IntroCutscene::create([=]() { NavigationEvents::navigate(NavigationEvents::GameScreen::StoryMap); }));
}

void SaveSelectMenu::onSaveGame3Click(MenuSprite* menuSprite)
{
	NavigationEvents::loadCutscene(IntroCutscene::create([=]() { NavigationEvents::navigate(NavigationEvents::GameScreen::StoryMap); }));
}
