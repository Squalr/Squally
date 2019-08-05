#include "BackgroundDeserializer.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/GlobalDirector.h"
#include "Engine/Maps/GameObject.h"
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
	ValueMap properties = args->properties;
	std::string name = GameUtils::getKeyOrDefault(properties, GameObject::MapKeyName, Value("")).asString();

	if (GameUtils::getKeyOrDefault(properties, MapLayer::MapKeyType, Value("")).asString() != BackgroundDeserializer::MapKeyBackgroundLayer)
	{
		return;
	}

	args->handle();

	if (!GameUtils::keyExists(properties, BackgroundDeserializer::MapKeyBackgroundLayer))
	{
		CCLOG("No background property on background layer");
		return;
	}

	std::string background = properties.at(BackgroundDeserializer::MapKeyBackgroundLayer).asString();

	// For decor, simply grab the resource of the same name of the object type
	Sprite* sprite = Sprite::create("Platformer/Backgrounds/" + background + ".png");

	if (sprite == nullptr)
	{
		CCLOG("Non-existant background");
		return;
	}

	args->onDeserializeCallback(LayerDeserializer::LayerDeserializationArgs(Background::create(properties, name, sprite), args->layerIndex));
}
