#include "WorldMap.h"

const std::string WorldMap::StringKeySelectLevel = "Menu_Story_Select_Level";
const std::string WorldMap::StringKeyLevelNameJungle = "Menu_Story_Level_Name_Jungle";
const std::string WorldMap::StringKeyLevelNameAquaticRuins = "Menu_Story_Level_Name_Aquatic_Ruins";
const std::string WorldMap::StringKeyLevelNameForest = "Menu_Story_Level_Name_Forest";
const std::string WorldMap::StringKeyLevelNameCaverns = "Menu_Story_Level_Name_Caverns";
const std::string WorldMap::StringKeyLevelNameCastle = "Menu_Story_Level_Name_Castle";
const std::string WorldMap::StringKeyLevelNameIceCaps = "Menu_Story_Level_Name_Ice_Caps";
const std::string WorldMap::StringKeyLevelNameObelisk = "Menu_Story_Level_Name_Obelisk";
const std::string WorldMap::StringKeyLevelNameVolcano = "Menu_Story_Level_Name_Volcano";
const std::string WorldMap::StringKeyLevelNameMech = "Menu_Story_Level_Name_Mech";

WorldMap * WorldMap::create()
{
	WorldMap* instance = new WorldMap();

	instance->autorelease();

	return instance;
}

WorldMap::WorldMap()
{
	this->mapNodes = std::vector<MapNode*>();
	this->background = Sprite::create(UIResources::Menus_WorldMap_WorldMap);
	this->foreground = Sprite::create(UIResources::Menus_WorldMap_WorldMapFront);
	this->fogA = InfiniteParallaxNode::create(UIResources::Menus_Backgrounds_Fog);
	this->fogB = InfiniteParallaxNode::create(UIResources::Menus_Backgrounds_Fog);
	this->fogC = InfiniteParallaxNode::create(UIResources::Menus_Backgrounds_Fog);
	this->titleLabel = Label::create(Localization::resolveString(WorldMap::StringKeySelectLevel), Localization::getMainFont(), this->titleFontSize);
	this->infoLabel = Label::create("", Localization::getMainFont(), this->infoFontSize);

	this->titleLabel->enableOutline(Color4B::BLACK, 2);
	this->infoLabel->enableOutline(Color4B::BLACK, 2);

	this->jungle = MapNode::create(
		UIResources::Menus_WorldMap_Jungle,
		UIResources::Menus_WorldMap_JungleSelected,
		UIResources::Menus_WorldMap_JungleLocked,
		Localization::resolveString(WorldMap::StringKeyLevelNameJungle),
		MapResources::Platformer_Jungle_Jungle
	);

	this->waterRuins = MapNode::create(
		UIResources::Menus_WorldMap_WaterRuins,
		UIResources::Menus_WorldMap_WaterRuinsSelected,
		UIResources::Menus_WorldMap_WaterRuinsLocked,
		Localization::resolveString(WorldMap::StringKeyLevelNameAquaticRuins),
		MapResources::Platformer_AquaticRuins_AquaticRuins
	);

	this->forest = MapNode::create(
		UIResources::Menus_WorldMap_Forest,
		UIResources::Menus_WorldMap_ForestSelected,
		UIResources::Menus_WorldMap_ForestLocked,
		Localization::resolveString(WorldMap::StringKeyLevelNameForest),
		MapResources::Platformer_Forest_Forest
	);

	this->caverns = MapNode::create(
		UIResources::Menus_WorldMap_Mountain,
		UIResources::Menus_WorldMap_MountainSelected,
		UIResources::Menus_WorldMap_MountainLocked,
		Localization::resolveString(WorldMap::StringKeyLevelNameCaverns),
		MapResources::Platformer_Caverns_Caverns
	);

	this->castle = MapNode::create(
		UIResources::Menus_WorldMap_Castle,
		UIResources::Menus_WorldMap_CastleSelected,
		UIResources::Menus_WorldMap_CastleLocked,
		Localization::resolveString(WorldMap::StringKeyLevelNameCastle),
		MapResources::Platformer_Castle_Castle
	);

	this->iceCaps = MapNode::create(
		UIResources::Menus_WorldMap_IceMountain,
		UIResources::Menus_WorldMap_IceMountainSelected,
		UIResources::Menus_WorldMap_IceMountainLocked,
		Localization::resolveString(WorldMap::StringKeyLevelNameIceCaps),
		MapResources::Platformer_IceCaps_IceCaps
	);

	this->obelisk = MapNode::create(
		UIResources::Menus_WorldMap_Obelisk,
		UIResources::Menus_WorldMap_ObeliskSelected,
		UIResources::Menus_WorldMap_ObeliskLocked,
		Localization::resolveString(WorldMap::StringKeyLevelNameObelisk),
		MapResources::Platformer_Obelisk_Obelisk
	);

	this->volcano = MapNode::create(
		UIResources::Menus_WorldMap_Volcano,
		UIResources::Menus_WorldMap_VolcanoSelected,
		UIResources::Menus_WorldMap_VolcanoLocked,
		Localization::resolveString(WorldMap::StringKeyLevelNameVolcano),
		MapResources::Platformer_Volcano_Volcano
	);

	this->mecha = MapNode::create(
		UIResources::Menus_WorldMap_Mech,
		UIResources::Menus_WorldMap_MechSelected,
		UIResources::Menus_WorldMap_MechLocked,
		Localization::resolveString(WorldMap::StringKeyLevelNameMech),
		MapResources::Platformer_Mech_Mech
	);

	this->fogA->runAction(RepeatForever::create(MoveBy::create(2.0f, Vec2(-40.0f, 0))));
	this->fogA->setOpacity(127);
	this->fogA->setCascadeOpacityEnabled(true);
	this->fogB->runAction(RepeatForever::create(MoveBy::create(2.0f, Vec2(-32.0f, 0))));
	this->fogB->setOpacity(127);
	this->fogB->setCascadeOpacityEnabled(true);
	this->fogC->runAction(RepeatForever::create(MoveBy::create(2.0f, Vec2(-24.0f, 0))));
	this->fogC->setOpacity(127);
	this->fogC->setCascadeOpacityEnabled(true);

	this->mapNodes.push_back(this->jungle);
	this->mapNodes.push_back(this->waterRuins);
	this->mapNodes.push_back(this->forest);
	this->mapNodes.push_back(this->caverns);
	this->mapNodes.push_back(this->castle);
	this->mapNodes.push_back(this->iceCaps);
	this->mapNodes.push_back(this->obelisk);
	this->mapNodes.push_back(this->volcano);
	this->mapNodes.push_back(this->mecha);

	this->addChild(this->background);
	this->addChild(this->jungle);
	this->addChild(this->waterRuins);
	this->addChild(this->forest);
	this->addChild(this->caverns);
	this->addChild(this->castle);
	this->addChild(this->iceCaps);
	this->addChild(this->obelisk);
	this->addChild(this->volcano);
	this->addChild(this->mecha);
	this->addChild(this->foreground);
	this->addChild(this->fogA);
	this->addChild(this->fogB);
	this->addChild(this->fogC);
	this->addChild(this->titleLabel);
	this->addChild(this->infoLabel);
	this->addChild(Mouse::create());
}

WorldMap::~WorldMap()
{
}

void WorldMap::onEnter()
{
	FadeScene::onEnter();

	const float delay = 0.5f;
	const float duration = 0.75f;

	GameUtils::fadeInObject(this->titleLabel, delay, duration);
	GameUtils::fadeInObject(this->infoLabel, delay, duration);
}

void WorldMap::initializePositions()
{
	FadeScene::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->titleLabel->setPosition(Vec2(visibleSize.width / 2.0f - 616.0f, visibleSize.height - this->titleLabel->getContentSize().height / 2.0f - 64.0f));
	this->infoLabel->setPosition(Vec2(visibleSize.width / 2.0f - 616.0f, visibleSize.height - 48.0f - 64.0f - 48.0f));
	this->background->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->jungle->setPosition(Vec2(visibleSize.width / 2.0f + 624.0f, visibleSize.height / 2.0f - 292.0f));
	this->waterRuins->setPosition(Vec2(visibleSize.width / 2.0f - 104.0f, visibleSize.height / 2.0f - 340.0f));
	this->forest->setPosition(Vec2(visibleSize.width / 2.0f - 704.0f, visibleSize.height / 2.0f - 308.0f));
	this->caverns->setPosition(Vec2(visibleSize.width / 2.0f - 668.0f, visibleSize.height / 2.0f + 32.0f));
	this->castle->setPosition(Vec2(visibleSize.width / 2.0f - 388.0f, visibleSize.height / 2.0f + 344.0f));
	this->iceCaps->setPosition(Vec2(visibleSize.width / 2.0f + 112.0f, visibleSize.height / 2.0f + 496.0f));
	this->obelisk->setPosition(Vec2(visibleSize.width / 2.0f + 720.0f, visibleSize.height / 2.0f + 420.0f));
	this->volcano->setPosition(Vec2(visibleSize.width / 2.0f + 196.0f, visibleSize.height / 2.0f + 64.0f));
	this->mecha->setPosition(Vec2(visibleSize.width / 2.0f + 696.0f, visibleSize.height / 2.0f - 38.0f));
	this->foreground->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));

	this->fogA->setPosition(Vec2(visibleSize.width / 2.0f - 256.0f, visibleSize.height / 2.0f + 420.0f));
	this->fogB->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->fogC->setPosition(Vec2(visibleSize.width / 2.0f - 420.0f, visibleSize.height / 2.0f - 420.0f));

	this->initializedLocked();
}

void WorldMap::initializeListeners()
{
	FadeScene::initializeListeners();

	EventListenerCustom* mouseListener = EventListenerCustom::create(MouseEvents::MouseMoveEvent, CC_CALLBACK_1(WorldMap::onMouseMove, this));
	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = CC_CALLBACK_2(WorldMap::onKeyPressed, this);

	this->addEventListener(mouseListener);
	this->addEventListener(keyboardListener);
}

void WorldMap::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (!GameUtils::isFocused(this))
	{
		return;
	}

	switch (keyCode)
	{
		case EventKeyboard::KeyCode::KEY_ESCAPE:
		{
			event->stopPropagation();
			NavigationEvents::navigateBack();
			break;
		}
		default:
		{
			break;
		}
	}
}

void WorldMap::initializedLocked()
{
	this->jungle->setLocked(false);
	this->waterRuins->setLocked(false);
	this->forest->setLocked(false);
	this->caverns->setLocked(false);
	this->castle->setLocked(false);
	this->iceCaps->setLocked(false);
	this->obelisk->setLocked(false);
	this->volcano->setLocked(false);
	this->mecha->setLocked(false);
}

void WorldMap::onMouseMove(EventCustom* event)
{
	MouseEvents::MouseEventArgs* args = static_cast<MouseEvents::MouseEventArgs*>(event->getUserData());

	for (auto it = this->mapNodes.begin(); it != this->mapNodes.end(); it++)
	{
		MapNode* node = *it;

		if (GameUtils::intersects(node, args->mouseCoords) && !node->isLocked())
		{
			this->infoLabel->setString(node->nodeMapName);
			return;
		}
	}

	this->infoLabel->setString("");
}
