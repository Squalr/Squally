#pragma once
#include "cocos2d.h"

#include "Engine/Maps/ObjectifiedTile.h"
#include "Engine/Utils/StrUtils.h"
#include "SerializableLayer.h"

using namespace cocos2d;

class SerializableTileLayer : public SerializableLayer
{
public:
	static SerializableTileLayer * deserialize(cocos_experimental::TMXLayer* initTileLayer);

	void serialize(tinyxml2::XMLDocument* documentRoot, tinyxml2::XMLElement* parentElement, Size mapUnitSize, Size mapTileSize) override;
	std::string getType();

	static const std::string KeyPropertyWidth;
	static const std::string KeyPropertyHeight;
	static const std::string KeyPropertyType;
	static const std::string KeyPropertyObjectify;
	static const std::string KeyPropertyEncoding;
	static const std::string KeyPropertyEncodingValue;

protected:
	SerializableTileLayer(cocos_experimental::TMXLayer* initTileLayer);
	~SerializableTileLayer();

private:
	cocos_experimental::TMXLayer* tileLayer;
};
