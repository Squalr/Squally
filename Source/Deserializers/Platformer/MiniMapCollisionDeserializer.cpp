#include "MiniMapCollisionDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Deserializers/Platformer/PlatformerComponentDeserializer.h"
#include "Deserializers/Platformer/PlatformerQuestDeserializer.h"
#include "Engine/Maps/GameObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Quests/QuestTask.h"
#include "Objects/Platformer/MiniMap/MiniMapObject.h"

using namespace cocos2d;

const std::string MiniMapCollisionDeserializer::MapKeyTypeCollision = "collision";
const std::string MiniMapCollisionDeserializer::PropertyMiniMapVisible = "mini-map-visible";
const Color4B MiniMapCollisionDeserializer::PassThroughColor = Color4B(164, 164, 164, 255);
const Color4B MiniMapCollisionDeserializer::SolidColor = Color4B(126, 126, 126, 255);

MiniMapCollisionDeserializer* MiniMapCollisionDeserializer::create()
{
	MiniMapCollisionDeserializer* instance = new MiniMapCollisionDeserializer();

	instance->autorelease();

	return instance;
}

MiniMapCollisionDeserializer::MiniMapCollisionDeserializer() : super(MiniMapCollisionDeserializer::MapKeyTypeCollision)
{
}

MiniMapCollisionDeserializer::~MiniMapCollisionDeserializer()
{
}

void MiniMapCollisionDeserializer::deserialize(ObjectDeserializer::ObjectDeserializationRequestArgs* args)
{
	if (GameUtils::getKeyOrDefault(args->properties, MiniMapCollisionDeserializer::PropertyMiniMapVisible, Value(false)).asBool())
	{
		args->onDeserializeCallback(ObjectDeserializationArgs((GameObject*)MiniMapObject::create(args->properties, MiniMapCollisionDeserializer::SolidColor)));
	}
}
