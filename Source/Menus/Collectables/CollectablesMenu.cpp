#include "CollectablesMenu.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventListenerKeyboard.h"
#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Menus/Collectables/Collectables.h"
#include "Strings/Menus/Return.h"

using namespace cocos2d;

CollectablesMenu* CollectablesMenu::create()
{
	CollectablesMenu* instance = new CollectablesMenu();

	instance->autorelease();

	return instance;
}

CollectablesMenu::CollectablesMenu()
{
	this->collectablesWindow = Sprite::create(UIResources::Menus_Generic_LargeMenu);
	this->saveKeys = std::vector<std::string>();
	this->sprites = std::vector<Sprite*>();
	this->lockedSprites = std::vector<Sprite*>();
	this->contentPane = ScrollPane::create(Size(1024.0f, 612.0f), UIResources::Menus_Buttons_SliderButton, UIResources::Menus_Buttons_SliderButtonSelected);
	this->closeButton = ClickableNode::create(UIResources::Menus_IngameMenu_CloseButton, UIResources::Menus_IngameMenu_CloseButtonSelected);
	this->collectablesLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Menus_Collectables_Collectables::create());
	this->returnClickCallback = nullptr;

	this->contentPane->setBackgroundColor(Color4B(0, 0, 0, 0));

	LocalizedLabel*	returnLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Return::create());
	LocalizedLabel*	returnLabelHover = returnLabel->clone();

	returnLabel->enableOutline(Color4B::BLACK, 2);
	returnLabel->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	returnLabel->enableGlow(Color4B::BLACK);
	returnLabelHover->enableOutline(Color4B::BLACK, 2);
	returnLabelHover->setTextColor(Color4B::YELLOW);
	returnLabelHover->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	returnLabelHover->enableGlow(Color4B::ORANGE);

	this->returnButton = ClickableTextNode::create(
		returnLabel,
		returnLabelHover,
		UIResources::Menus_Buttons_WoodButton,
		UIResources::Menus_Buttons_WoodButtonSelected);

	this->collectablesLabel->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	this->collectablesLabel->enableGlow(Color4B::BLACK);

	this->registerCollectableAnimal(ObjectResources::Collectables_Animals_Bat, ObjectResources::Collectables_Animals_Bat_Locked, SaveKeys::SaveKeyCollectableAnimalBat);
	this->registerCollectableAnimal(ObjectResources::Collectables_Animals_Bear, ObjectResources::Collectables_Animals_Bear_Locked, SaveKeys::SaveKeyCollectableAnimalBear);
	this->registerCollectableAnimal(ObjectResources::Collectables_Animals_Beaver, ObjectResources::Collectables_Animals_Beaver_Locked, SaveKeys::SaveKeyCollectableAnimalBeaver);
	this->registerCollectableAnimal(ObjectResources::Collectables_Animals_Bee, ObjectResources::Collectables_Animals_Bee_Locked, SaveKeys::SaveKeyCollectableAnimalBee);
	this->registerCollectableAnimal(ObjectResources::Collectables_Animals_Bird, ObjectResources::Collectables_Animals_Bird_Locked, SaveKeys::SaveKeyCollectableAnimalBird);
	this->registerCollectableAnimal(ObjectResources::Collectables_Animals_Blowfish, ObjectResources::Collectables_Animals_Blowfish_Locked, SaveKeys::SaveKeyCollectableAnimalBlowfish);
	this->registerCollectableAnimal(ObjectResources::Collectables_Animals_Bull, ObjectResources::Collectables_Animals_Bull_Locked, SaveKeys::SaveKeyCollectableAnimalBull);
	this->registerCollectableAnimal(ObjectResources::Collectables_Animals_Bunny, ObjectResources::Collectables_Animals_Bunny_Locked, SaveKeys::SaveKeyCollectableAnimalBunny);
	this->registerCollectableAnimal(ObjectResources::Collectables_Animals_Cat, ObjectResources::Collectables_Animals_Cat_Locked, SaveKeys::SaveKeyCollectableAnimalCat);
	this->registerCollectableAnimal(ObjectResources::Collectables_Animals_Chicken, ObjectResources::Collectables_Animals_Chicken_Locked, SaveKeys::SaveKeyCollectableAnimalChicken);
	this->registerCollectableAnimal(ObjectResources::Collectables_Animals_Cow, ObjectResources::Collectables_Animals_Cow_Locked, SaveKeys::SaveKeyCollectableAnimalCow);
	this->registerCollectableAnimal(ObjectResources::Collectables_Animals_Crocodile, ObjectResources::Collectables_Animals_Crocodile_Locked, SaveKeys::SaveKeyCollectableAnimalCrocodile);
	this->registerCollectableAnimal(ObjectResources::Collectables_Animals_Dinosaur, ObjectResources::Collectables_Animals_Dinosaur_Locked, SaveKeys::SaveKeyCollectableAnimalDinosaur);
	this->registerCollectableAnimal(ObjectResources::Collectables_Animals_Dog, ObjectResources::Collectables_Animals_Dog_Locked, SaveKeys::SaveKeyCollectableAnimalDog);
	this->registerCollectableAnimal(ObjectResources::Collectables_Animals_Duck, ObjectResources::Collectables_Animals_Duck_Locked, SaveKeys::SaveKeyCollectableAnimalDuck);
	this->registerCollectableAnimal(ObjectResources::Collectables_Animals_Fox, ObjectResources::Collectables_Animals_Fox_Locked, SaveKeys::SaveKeyCollectableAnimalFox);
	this->registerCollectableAnimal(ObjectResources::Collectables_Animals_Giraffe, ObjectResources::Collectables_Animals_Giraffe_Locked, SaveKeys::SaveKeyCollectableAnimalGiraffe);
	this->registerCollectableAnimal(ObjectResources::Collectables_Animals_Goat, ObjectResources::Collectables_Animals_Goat_Locked, SaveKeys::SaveKeyCollectableAnimalGoat);
	this->registerCollectableAnimal(ObjectResources::Collectables_Animals_Hedgehog, ObjectResources::Collectables_Animals_Hedgehog_Locked, SaveKeys::SaveKeyCollectableAnimalHedgehog);
	this->registerCollectableAnimal(ObjectResources::Collectables_Animals_Hippo, ObjectResources::Collectables_Animals_Hippo_Locked, SaveKeys::SaveKeyCollectableAnimalHippo);
	this->registerCollectableAnimal(ObjectResources::Collectables_Animals_Horse, ObjectResources::Collectables_Animals_Horse_Locked, SaveKeys::SaveKeyCollectableAnimalHorse);
	this->registerCollectableAnimal(ObjectResources::Collectables_Animals_KillerWhale, ObjectResources::Collectables_Animals_KillerWhale_Locked, SaveKeys::SaveKeyCollectableAnimalKillerWhale);
	this->registerCollectableAnimal(ObjectResources::Collectables_Animals_Koala, ObjectResources::Collectables_Animals_Koala_Locked, SaveKeys::SaveKeyCollectableAnimalKoala);
	this->registerCollectableAnimal(ObjectResources::Collectables_Animals_Ladybug, ObjectResources::Collectables_Animals_Ladybug_Locked, SaveKeys::SaveKeyCollectableAnimalLadybug);
	this->registerCollectableAnimal(ObjectResources::Collectables_Animals_Lion, ObjectResources::Collectables_Animals_Lion_Locked, SaveKeys::SaveKeyCollectableAnimalLion);
	this->registerCollectableAnimal(ObjectResources::Collectables_Animals_Lizard, ObjectResources::Collectables_Animals_Lizard_Locked, SaveKeys::SaveKeyCollectableAnimalLizard);
	this->registerCollectableAnimal(ObjectResources::Collectables_Animals_Monkey, ObjectResources::Collectables_Animals_Monkey_Locked, SaveKeys::SaveKeyCollectableAnimalMonkey);
	this->registerCollectableAnimal(ObjectResources::Collectables_Animals_MountainLion, ObjectResources::Collectables_Animals_MountainLion_Locked, SaveKeys::SaveKeyCollectableAnimalMountainLion);
	this->registerCollectableAnimal(ObjectResources::Collectables_Animals_Mouse, ObjectResources::Collectables_Animals_Mouse_Locked, SaveKeys::SaveKeyCollectableAnimalMouse);
	this->registerCollectableAnimal(ObjectResources::Collectables_Animals_Panda, ObjectResources::Collectables_Animals_Panda_Locked, SaveKeys::SaveKeyCollectableAnimalPanda);
	this->registerCollectableAnimal(ObjectResources::Collectables_Animals_Parrot, ObjectResources::Collectables_Animals_Parrot_Locked, SaveKeys::SaveKeyCollectableAnimalParrot);
	this->registerCollectableAnimal(ObjectResources::Collectables_Animals_Penguin, ObjectResources::Collectables_Animals_Penguin_Locked, SaveKeys::SaveKeyCollectableAnimalPenguin);
	this->registerCollectableAnimal(ObjectResources::Collectables_Animals_Pig, ObjectResources::Collectables_Animals_Pig_Locked, SaveKeys::SaveKeyCollectableAnimalPig);
	this->registerCollectableAnimal(ObjectResources::Collectables_Animals_Raccoon, ObjectResources::Collectables_Animals_Raccoon_Locked, SaveKeys::SaveKeyCollectableAnimalRaccoon);
	this->registerCollectableAnimal(ObjectResources::Collectables_Animals_Reindeer, ObjectResources::Collectables_Animals_Reindeer_Locked, SaveKeys::SaveKeyCollectableAnimalReindeer);
	this->registerCollectableAnimal(ObjectResources::Collectables_Animals_Rhino, ObjectResources::Collectables_Animals_Rhino_Locked, SaveKeys::SaveKeyCollectableAnimalRhino);
	this->registerCollectableAnimal(ObjectResources::Collectables_Animals_Sheep, ObjectResources::Collectables_Animals_Sheep_Locked, SaveKeys::SaveKeyCollectableAnimalSheep);
	this->registerCollectableAnimal(ObjectResources::Collectables_Animals_Skunk, ObjectResources::Collectables_Animals_Skunk_Locked, SaveKeys::SaveKeyCollectableAnimalSkunk);
	this->registerCollectableAnimal(ObjectResources::Collectables_Animals_Snail, ObjectResources::Collectables_Animals_Snail_Locked, SaveKeys::SaveKeyCollectableAnimalSnail);
	this->registerCollectableAnimal(ObjectResources::Collectables_Animals_Snake, ObjectResources::Collectables_Animals_Snake_Locked, SaveKeys::SaveKeyCollectableAnimalSnake);
	this->registerCollectableAnimal(ObjectResources::Collectables_Animals_Squid, ObjectResources::Collectables_Animals_Squid_Locked, SaveKeys::SaveKeyCollectableAnimalSquid);
	this->registerCollectableAnimal(ObjectResources::Collectables_Animals_Squirrel, ObjectResources::Collectables_Animals_Squirrel_Locked, SaveKeys::SaveKeyCollectableAnimalSquirrel);
	this->registerCollectableAnimal(ObjectResources::Collectables_Animals_Tiger, ObjectResources::Collectables_Animals_Tiger_Locked, SaveKeys::SaveKeyCollectableAnimalTiger);
	this->registerCollectableAnimal(ObjectResources::Collectables_Animals_Tucan, ObjectResources::Collectables_Animals_Tucan_Locked, SaveKeys::SaveKeyCollectableAnimalTucan);
	this->registerCollectableAnimal(ObjectResources::Collectables_Animals_Turtle, ObjectResources::Collectables_Animals_Turtle_Locked, SaveKeys::SaveKeyCollectableAnimalTurtle);
	this->registerCollectableAnimal(ObjectResources::Collectables_Animals_Whale, ObjectResources::Collectables_Animals_Whale_Locked, SaveKeys::SaveKeyCollectableAnimalWhale);
	this->registerCollectableAnimal(ObjectResources::Collectables_Animals_Wolf, ObjectResources::Collectables_Animals_Wolf_Locked, SaveKeys::SaveKeyCollectableAnimalWolf);
	this->registerCollectableAnimal(ObjectResources::Collectables_Animals_Worm, ObjectResources::Collectables_Animals_Worm_Locked, SaveKeys::SaveKeyCollectableAnimalWorm);
	this->registerCollectableAnimal(ObjectResources::Collectables_Animals_Yeti, ObjectResources::Collectables_Animals_Yeti_Locked, SaveKeys::SaveKeyCollectableAnimalYeti);
	this->registerCollectableAnimal(ObjectResources::Collectables_Animals_Zebra, ObjectResources::Collectables_Animals_Zebra_Locked, SaveKeys::SaveKeyCollectableAnimalZebra);

	this->addChild(this->collectablesWindow);
	this->addChild(this->contentPane);
	this->addChild(this->collectablesLabel);
	this->addChild(this->closeButton);
	this->addChild(this->returnButton);
}

CollectablesMenu::~CollectablesMenu()
{
}

void CollectablesMenu::onEnter()
{
	super::onEnter();

	float delay = 0.1f;
	float duration = 0.25f;

	GameUtils::fadeInObject(this->collectablesWindow, delay, duration);
	GameUtils::fadeInObject(this->collectablesLabel, delay, duration);
	GameUtils::fadeInObject(this->closeButton, delay, duration);
	GameUtils::fadeInObject(this->returnButton, delay, duration);

	this->updateCollectedVisualState();
}

void CollectablesMenu::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->collectablesWindow->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->contentPane->setPosition(Vec2(visibleSize.width / 2.0f + 24.0f, visibleSize.height / 2.0f - 44.0f));
	this->collectablesLabel->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 380.0f));
	this->closeButton->setPosition(Vec2(visibleSize.width / 2.0f + 580.0f, visibleSize.height / 2.0f + 368.0f));
	this->returnButton->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - 472.0f));
}

void CollectablesMenu::initializeListeners()
{
	super::initializeListeners();

	this->returnButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		if (this->returnClickCallback != nullptr)
		{
			this->returnClickCallback();
		}
	});

	this->closeButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		if (this->returnClickCallback != nullptr)
		{
			this->returnClickCallback();
		}
	});
	this->closeButton->setClickSound(SoundResources::ClickBack1);

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_ESCAPE }, [=](InputEvents::InputArgs* args)
	{
		if (!GameUtils::isVisible(this))
		{
			return;
		}
		
		args->handle();

		if (this->returnClickCallback != nullptr)
		{
			this->returnClickCallback();
		}
	});
}

void CollectablesMenu::setReturnClickCallback(std::function<void()> returnClickCallback)
{
	this->returnClickCallback = returnClickCallback;
}

void CollectablesMenu::open()
{
	this->updateCollectedVisualState();
}

void CollectablesMenu::updateCollectedVisualState()
{
	int collectedCount = 0;

	for (int index = 0; index < int(this->saveKeys.size()); index++)
	{
		if (SaveManager::getProfileDataOrDefault(this->saveKeys[index], Value(false)).asBool())
		{
			collectedCount++;
			this->sprites[index]->setVisible(true);
			this->lockedSprites[index]->setVisible(false);
		}
		else
		{
			this->sprites[index]->setVisible(false);
			this->lockedSprites[index]->setVisible(true);
		}
	}
}

void CollectablesMenu::registerCollectableAnimal(std::string resource, std::string resourceLocked, std::string saveKey)
{
	Sprite* next = Sprite::create(resource);
	Sprite* nextLocked = Sprite::create(resourceLocked);

	next->setScale(0.75f);
	nextLocked->setScale(0.75f);

	this->contentPane->addChild(next);
	this->contentPane->addChild(nextLocked);

	int x = this->sprites.size() % 5;
	int y = this->sprites.size() / 5;

	Vec2 position = Vec2((float(x) + 0.5f) * 192.0f + 16.0f - this->contentPane->getPaneSize().width / 2.0f, float(y) * -212.0f - 128.0f);

	next->setPosition(position);
	nextLocked->setPosition(position);

	this->saveKeys.push_back(saveKey);
	this->sprites.push_back(next);
	this->lockedSprites.push_back(nextLocked);
}
