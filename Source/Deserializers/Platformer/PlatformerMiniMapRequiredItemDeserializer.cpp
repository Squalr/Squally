#include "PlatformerMiniMapRequiredItemDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Engine/Save/SaveManager.h"
#include "Engine/Maps/GameObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

using namespace cocos2d;

const std::string PlatformerMiniMapRequiredItemDeserializer::PropertyMiniMapRequiredItem = "mini-map-item";

PlatformerMiniMapRequiredItemDeserializer* PlatformerMiniMapRequiredItemDeserializer::create()
{
	PlatformerMiniMapRequiredItemDeserializer* instance = new PlatformerMiniMapRequiredItemDeserializer();

	instance->autorelease();

	return instance;
}

PlatformerMiniMapRequiredItemDeserializer::PlatformerMiniMapRequiredItemDeserializer() : super()
{
}

PlatformerMiniMapRequiredItemDeserializer::~PlatformerMiniMapRequiredItemDeserializer()
{
}

void PlatformerMiniMapRequiredItemDeserializer::deserializeProperties(GameObject* owner, ValueMap properties)
{
	SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyLevelMiniMapRequiredItem, GameUtils::getKeyOrDefault(properties, PlatformerMiniMapRequiredItemDeserializer::PropertyMiniMapRequiredItem, Value("")));
}
