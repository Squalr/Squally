#include "LayerDeserializer.h"

using namespace cocos2d;

LayerDeserializer::LayerDeserializer(std::string layerType)
{
	this->layerType = layerType;
}

LayerDeserializer::~LayerDeserializer()
{
}

std::string LayerDeserializer::getLayerType()
{
	return this->layerType;
}
