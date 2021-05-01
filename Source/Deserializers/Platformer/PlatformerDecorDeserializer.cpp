#include "PlatformerDecorDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Engine/Utils/GameUtils.h"
#include "Deserializers/Platformer/PlatformerComponentDeserializer.h"
#include "Deserializers/Platformer/PlatformerQuestDeserializer.h"
#include "Objects/Platformer/PlatformerDecorObject.h"

using namespace cocos2d;

const std::string PlatformerDecorDeserializer::MapKeyTypeDecor = "decor";

PlatformerDecorDeserializer* PlatformerDecorDeserializer::create()
{
	PlatformerDecorDeserializer* instance = new PlatformerDecorDeserializer();

	instance->autorelease();

	return instance;
}

PlatformerDecorDeserializer::PlatformerDecorDeserializer() : super(PlatformerDecorDeserializer::MapKeyTypeDecor, { (PropertyDeserializer*)PlatformerComponentDeserializer::create(), (PropertyDeserializer*)PlatformerQuestDeserializer::create() })
{
}

PlatformerDecorDeserializer::~PlatformerDecorDeserializer()
{
}

void PlatformerDecorDeserializer::deserialize(ObjectDeserializer::ObjectDeserializationRequestArgs* args)
{
	GameObject* newObject = PlatformerDecorObject::create(args->properties);

	this->deserializeProperties(newObject, args->properties);

	args->onDeserializeCallback(ObjectDeserializer::ObjectDeserializationArgs(newObject));
}
