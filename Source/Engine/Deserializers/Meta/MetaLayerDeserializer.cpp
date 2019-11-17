#include "MetaLayerDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Engine/Deserializers/Properties/PropertyDeserializer.h"
#include "Engine/Maps/MapLayer.h"
#include "Engine/Maps/GameObject.h"
#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

const std::string MetaLayerDeserializer::MapKeyMetaLayer = "meta";

MetaLayerDeserializer* MetaLayerDeserializer::create(std::vector<PropertyDeserializer*> propertyDeserializers)
{
	MetaLayerDeserializer* instance = new MetaLayerDeserializer(propertyDeserializers);

	instance->autorelease();

	return instance;
}

MetaLayerDeserializer::MetaLayerDeserializer(std::vector<PropertyDeserializer*> propertyDeserializers) : super(MetaLayerDeserializer::MapKeyMetaLayer)
{
	this->propertyDeserializers = propertyDeserializers;
}

MetaLayerDeserializer::~MetaLayerDeserializer()
{
}

void MetaLayerDeserializer::deserialize(LayerDeserializer::LayerDeserializationRequestArgs* args)
{
	ValueMap properties = args->properties;
	std::string name = GameUtils::getKeyOrDefault(properties, GameObject::MapKeyName, Value("")).asString();
	std::string type = GameUtils::getKeyOrDefault(properties, GameObject::MapKeyType, Value("")).asString();

	MapLayer* layer = MapLayer::create(properties, name, type, { });

	for (auto it = this->propertyDeserializers.begin(); it != this->propertyDeserializers.end(); it++)
	{
		(*it)->deserializeProperties(layer, properties);
	}

	args->onDeserializeCallback(LayerDeserializer::LayerDeserializationArgs(layer, args->layerIndex));
}
