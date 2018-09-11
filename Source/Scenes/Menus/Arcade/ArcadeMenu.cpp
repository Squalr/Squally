#include "ArcadeMenu.h"

const std::string ArcadeMenu::StringKeyHexus = "Menu_Arcade_Hexus";
const std::string ArcadeMenu::StringKeyUnknown = "Menu_Arcade_Unknown";

const float ArcadeMenu::titleFontSize = 64.0f;
const float ArcadeMenu::menuFontSize = 48.0f;
const float ArcadeMenu::menuOffset = 128.0f;
const float ArcadeMenu::spacing = -96.0f;

ArcadeMenu * ArcadeMenu::create()
{
	ArcadeMenu* instance = new ArcadeMenu();

	instance->autorelease();

	return instance;
}

ArcadeMenu::ArcadeMenu()
{
	Size shadowSize = Size(-4.0f, -4.0f);
	int shadowBlur = 2;
	int hoverOutlineSize = 2;
	Color3B textColor = Color3B::WHITE;
	Color4B shadowColor = Color4B::BLACK;
	Color3B highlightColor = Color3B::YELLOW;
	Color4B glowColor = Color4B::ORANGE;

	this->nether = ParticleSystemQuad::create(Resources::Particles_BlueNether);

	Label* hexusLabel = Label::create(Localization::resolveString(ArcadeMenu::StringKeyHexus), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	Label* hexusLabelHover = Label::create(Localization::resolveString(ArcadeMenu::StringKeyHexus), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	Label* hexusLabelClicked = Label::create(Localization::resolveString(ArcadeMenu::StringKeyHexus), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));

	Label* unknown1Label = Label::create(Localization::resolveString(ArcadeMenu::StringKeyUnknown), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	Label* unknown1LabelHover = Label::create(Localization::resolveString(ArcadeMenu::StringKeyUnknown), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	Label* unknown1LabelClicked = Label::create(Localization::resolveString(ArcadeMenu::StringKeyUnknown), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));

	Label* unknown2Label = Label::create(Localization::resolveString(ArcadeMenu::StringKeyUnknown), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	Label* unknown2LabelHover = Label::create(Localization::resolveString(ArcadeMenu::StringKeyUnknown), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	Label* unknown2LabelClicked = Label::create(Localization::resolveString(ArcadeMenu::StringKeyUnknown), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));

	Label* unknown3Label = Label::create(Localization::resolveString(ArcadeMenu::StringKeyUnknown), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	Label* unknown3LabelHover = Label::create(Localization::resolveString(ArcadeMenu::StringKeyUnknown), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	Label* unknown3LabelClicked = Label::create(Localization::resolveString(ArcadeMenu::StringKeyUnknown), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));

	hexusLabel->setColor(textColor);
	hexusLabel->enableShadow(shadowColor, shadowSize, shadowBlur);
	hexusLabel->enableGlow(shadowColor);
	unknown1Label->setColor(textColor);
	unknown1Label->enableShadow(shadowColor, shadowSize, shadowBlur);
	unknown1Label->enableGlow(shadowColor);
	unknown2Label->setColor(textColor);
	unknown2Label->enableShadow(shadowColor, shadowSize, shadowBlur);
	unknown2Label->enableGlow(shadowColor);
	unknown3Label->setColor(textColor);
	unknown3Label->enableShadow(shadowColor, shadowSize, shadowBlur);
	unknown3Label->enableGlow(shadowColor);

	hexusLabelHover->setColor(highlightColor);
	hexusLabelHover->enableShadow(shadowColor, shadowSize, shadowBlur);
	hexusLabelHover->enableGlow(glowColor);
	unknown1LabelHover->setColor(highlightColor);
	unknown1LabelHover->enableShadow(shadowColor, shadowSize, shadowBlur);
	unknown1LabelHover->enableGlow(glowColor);
	unknown2LabelHover->setColor(highlightColor);
	unknown2LabelHover->enableShadow(shadowColor, shadowSize, shadowBlur);
	unknown2LabelHover->enableGlow(glowColor);
	unknown3LabelHover->setColor(highlightColor);
	unknown3LabelHover->enableShadow(shadowColor, shadowSize, shadowBlur);
	unknown3LabelHover->enableGlow(glowColor);

	hexusLabelClicked->setColor(highlightColor);
	hexusLabelClicked->enableShadow(shadowColor, shadowSize, shadowBlur);
	hexusLabelClicked->enableGlow(glowColor);
	unknown1LabelClicked->setColor(highlightColor);
	unknown1LabelClicked->enableShadow(shadowColor, shadowSize, shadowBlur);
	unknown1LabelClicked->enableGlow(glowColor);
	unknown2LabelClicked->setColor(highlightColor);
	unknown2LabelClicked->enableShadow(shadowColor, shadowSize, shadowBlur);
	unknown2LabelClicked->enableGlow(glowColor);
	unknown3LabelClicked->setColor(highlightColor);
	unknown3LabelClicked->enableShadow(shadowColor, shadowSize, shadowBlur);
	unknown3LabelClicked->enableGlow(glowColor);

	this->hexusButton = TextMenuSprite::create(
		hexusLabel,
		hexusLabelHover,
		hexusLabelClicked,
		Resources::Menus_ArcadeMenu_Banner,
		Resources::Menus_ArcadeMenu_BannerHover,
		Resources::Menus_ArcadeMenu_BannerClick);

	this->unknownButton1 = TextMenuSprite::create(
		unknown1Label,
		unknown1LabelHover,
		unknown1LabelClicked,
		Resources::Menus_ArcadeMenu_Banner,
		Resources::Menus_ArcadeMenu_BannerHover,
		Resources::Menus_ArcadeMenu_BannerClick);

	this->unknownButton2 = TextMenuSprite::create(
		unknown2Label,
		unknown2LabelHover,
		unknown2LabelClicked,
		Resources::Menus_ArcadeMenu_Banner,
		Resources::Menus_ArcadeMenu_BannerHover,
		Resources::Menus_ArcadeMenu_BannerClick);

	this->unknownButton3 = TextMenuSprite::create(
		unknown3Label,
		unknown3LabelHover,
		unknown3LabelClicked,
		Resources::Menus_ArcadeMenu_Banner,
		Resources::Menus_ArcadeMenu_BannerHover,
		Resources::Menus_ArcadeMenu_BannerClick);

	this->addChild(this->nether);
	this->addChild(this->hexusButton);
	this->addChild(this->unknownButton1);
	this->addChild(this->unknownButton2);
	this->addChild(this->unknownButton3);
	this->addChild(Mouse::create());
}

ArcadeMenu::~ArcadeMenu()
{
}

void ArcadeMenu::onEnter()
{
	FadeScene::onEnter();

	SoundManager::playMusicResource(Resources::Music_WeWillGetThereTogether);

	this->initializePositions();

	GameUtils::accelerateParticles(this->nether, 1.0f);

	const float delay = 0.5f;
	const float duration = 0.75f;

	GameUtils::fadeInObject(this->hexusButton, delay, duration);
	GameUtils::fadeInObject(this->unknownButton1, delay, duration);
	GameUtils::fadeInObject(this->unknownButton2, delay, duration);
	GameUtils::fadeInObject(this->unknownButton3, delay, duration);

	this->scheduleUpdate();
}

void ArcadeMenu::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->nether->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->hexusButton->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 256.0f));
	this->unknownButton1->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 128.0f));
	this->unknownButton2->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 128.0f));
	this->unknownButton3->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 256.0f));
}

void ArcadeMenu::onHexusClick(MenuSprite* menuSprite)
{
	NavigationEvents::navigate(NavigationEvents::GameScreen::StoryMap);
	////NavigationEvents::loadCutscene(NavigationEvents::CutsceneEnum::CutsceneNeonCity);
}
