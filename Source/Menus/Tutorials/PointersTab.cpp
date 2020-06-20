#include "PointersTab.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Config/ConfigManager.h"
#include "Engine/Events/NavigationEvents.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Entities/Platformer/Helpers/BallmerPeaks/Snowman.h"
#include "Entities/Platformer/Helpers/EndianForest/Guano.h"
#include "Menus/Tutorials/TutorialEntry.h"
#include "Menus/Tutorials/TutorialSelectMenu.h"
#include "Scenes/Platformer/Level/PlatformerMap.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Tutorials/Save/TutorialSaveKeys.h"

#include "Resources/MapResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

PointersTab* PointersTab::create()
{
	PointersTab* instance = new PointersTab();

	instance->autorelease();

	return instance;
}

PointersTab::PointersTab()
{
}

PointersTab::~PointersTab()
{
}

void PointersTab::onEnter()
{
	super::onEnter();
}

void PointersTab::initializeListeners()
{
	super::initializeListeners();
}

void PointersTab::initializePositions()
{
	super::initializePositions();
}
