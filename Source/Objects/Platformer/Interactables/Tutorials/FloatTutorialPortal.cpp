#include "FloatTutorialPortal.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/NavigationEvents.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/StrUtils.h"
#include "Menus/Tutorials/TutorialSelectMenu.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Scenes/Platformer/Level/PlatformerMap.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"
#include "Scenes/Tutorials/Save/TutorialSaveKeys.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string FloatTutorialPortal::MapKey = "float-tutorial-portal";

FloatTutorialPortal* FloatTutorialPortal::create(ValueMap& properties)
{
	FloatTutorialPortal* instance = new FloatTutorialPortal(properties);

	instance->autorelease();

	return instance;
}

FloatTutorialPortal::FloatTutorialPortal(ValueMap& properties) : super(properties, Size(properties.at(GameObject::MapKeyWidth).asFloat(), properties.at(GameObject::MapKeyHeight).asFloat()))
{
	this->setInteractType(InteractType::Input);
}

FloatTutorialPortal::~FloatTutorialPortal()
{
}
	
void FloatTutorialPortal::loadMap()
{
	SaveManager::saveGlobalData(TutorialSaveKeys::SaveKeyKnownValueFloatAdvanced, Value(true));

	NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs([=]()
	{
		return TutorialSelectMenu::getInstance();
	}));
}
