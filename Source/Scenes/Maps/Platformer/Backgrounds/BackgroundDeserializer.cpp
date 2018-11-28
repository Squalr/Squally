#include "BackgroundDeserializer.h"

BackgroundDeserializer* BackgroundDeserializer::instance = nullptr;
const std::string BackgroundDeserializer::MapKeyBackgroundLayer = "background";

void BackgroundDeserializer::registerGlobalNode()
{
	if (BackgroundDeserializer::instance == nullptr)
	{
		BackgroundDeserializer::instance = new BackgroundDeserializer();

		instance->autorelease();

		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(BackgroundDeserializer::instance);
	}
}

void BackgroundDeserializer::initializeListeners()
{
	GlobalNode::initializeListeners();

	EventListenerCustom* deserializationRequestListener = EventListenerCustom::create(
		DeserializationEvents::RequestLayerDeserializeEvent,
		[=](EventCustom* args) { this->onDeserializationRequest((DeserializationEvents::LayerDeserializationRequestArgs*)args->getUserData()); }
	);

	this->addEventListener(deserializationRequestListener);
}

void BackgroundDeserializer::onDeserializationRequest(DeserializationEvents::LayerDeserializationRequestArgs* args)
{
	std::string name = args->objectGroup->getGroupName();
	ValueMap properties = args->objectGroup->getProperties();

	if (!GameUtils::keyExists(&properties, SerializableLayer::KeyType))
	{
		return;
	}

	std::string type = properties.at(SerializableLayer::KeyType).asString();

	if (type != BackgroundDeserializer::MapKeyBackgroundLayer)
	{
		return;
	}

	args->handled = true;

	if (!GameUtils::keyExists(&properties, BackgroundDeserializer::MapKeyBackgroundLayer))
	{
		CCLOG("No background property on background layer");
		return;
	}

	std::string background = properties.at(BackgroundDeserializer::MapKeyBackgroundLayer).asString();

	// For decor, simply grab the resource of the same name of the object type
	Sprite* sprite = Sprite::create("GamePlay/Platformer/Backgrounds/" + background + ".png");

	if (sprite == nullptr)
	{
		CCLOG("Non-existant background");
		return;
	}

	args->onDeserializeCallback(DeserializationEvents::LayerDeserializationArgs(Background::create(&properties, name, sprite), args->objectGroup->layerIndex));
}
