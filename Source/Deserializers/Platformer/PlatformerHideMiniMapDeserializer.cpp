#include "PlatformerHideMiniMapDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Engine/Save/SaveManager.h"
#include "Engine/Maps/GameObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

using namespace cocos2d;

const std::string PlatformerHideMiniMapDeserializer::PropertyHideMiniMap = "hide-mini-map";

PlatformerHideMiniMapDeserializer* PlatformerHideMiniMapDeserializer::create()
{
	PlatformerHideMiniMapDeserializer* instance = new PlatformerHideMiniMapDeserializer();

	instance->autorelease();

	return instance;
}

PlatformerHideMiniMapDeserializer::PlatformerHideMiniMapDeserializer() : super()
{
}

PlatformerHideMiniMapDeserializer::~PlatformerHideMiniMapDeserializer()
{
}

void PlatformerHideMiniMapDeserializer::deserializeProperties(GameObject* owner, ValueMap properties)
{
	SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyLevelHideMiniMap, GameUtils::getKeyOrDefault(properties, PlatformerHideMiniMapDeserializer::PropertyHideMiniMap, Value(false)));
}
