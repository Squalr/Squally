#include "BackgroundDeserializer.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/GlobalDirector.h"
#include "Engine/Utils/GameUtils.h"

#include "Engine/Maps/Backgrounds/Background.h"

using namespace cocos2d;

const std::string BackgroundDeserializer::MapKeyBackgroundLayer = "background";

BackgroundDeserializer* BackgroundDeserializer::create()
{
	BackgroundDeserializer* instance = new BackgroundDeserializer();

	instance->autorelease();

	return instance;
}

BackgroundDeserializer::BackgroundDeserializer() : super(BackgroundDeserializer::MapKeyBackgroundLayer)
{
}

BackgroundDeserializer::~BackgroundDeserializer()
{
}

void BackgroundDeserializer::deserialize(LayerDeserializer::LayerDeserializationRequestArgs* args)
{
	std::string name = args->name;

	if (GameUtils::getKeyOrDefault(args->properties, MapLayer::KeyType, Value("")).asString() != BackgroundDeserializer::MapKeyBackgroundLayer)
	{
		return;
	}

	args->handled = true;

	if (!GameUtils::keyExists(args->properties, BackgroundDeserializer::MapKeyBackgroundLayer))
	{
		CCLOG("No background property on background layer");
		return;
	}

	std::string background = args->properties.at(BackgroundDeserializer::MapKeyBackgroundLayer).asString();

	// For decor, simply grab the resource of the same name of the object type
	Sprite* sprite = Sprite::create("Platformer/Backgrounds/" + background + ".png");

	if (sprite == nullptr)
	{
		CCLOG("Non-existant background");
		return;
	}

	args->onDeserializeCallback(DeserializationEvents::LayerDeserializationArgs(Background::create(args->properties, name, sprite), args->objectGroup->layerIndex));
}
