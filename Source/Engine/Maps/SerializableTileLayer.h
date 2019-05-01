#pragma once
#include <string>

#include "cocos/math/CCGeometry.h"

#include "Engine/SmartNode.h"
#include "Engine/Maps/SerializableLayer.h"

namespace cocos2d
{
	namespace cocos_experimental
	{
		class TMXLayer;
	}
}

namespace tinyxml2
{
	class XMLDocument;
	class XMLElement;
}

class SerializableTileLayer : public SerializableLayer
{
public:
	static SerializableTileLayer* deserialize(cocos2d::cocos_experimental::TMXLayer* initTileLayer);

	void serialize(tinyxml2::XMLDocument* documentRoot, tinyxml2::XMLElement* parentElement,
			cocos2d::Size mapUnitSize, cocos2d::Size mapTileSize) override;
	std::string getType();
	std::vector<std::vector<int>> getGidMap();

	static const std::string MapKeyPropertyWidth;
	static const std::string MapKeyPropertyHeight;
	static const std::string MapKeyPropertyType;
	static const std::string MapKeyPropertyObjectify;
	static const std::string MapKeyPropertyEncoding;
	static const std::string MapKeyPropertyEncodingValue;

protected:
	SerializableTileLayer(cocos2d::cocos_experimental::TMXLayer* initTileLayer);
	virtual ~SerializableTileLayer();

private:
	typedef SerializableLayer super;
	cocos2d::cocos_experimental::TMXLayer* tileLayer;
};
