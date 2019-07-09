#pragma once
#include <string>

#include "cocos/math/CCGeometry.h"

#include "Engine/SmartNode.h"
#include "Engine/Maps/MapLayer.h"

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

class TileLayer : public MapLayer
{
public:
	static TileLayer* deserialize(cocos2d::cocos_experimental::TMXLayer* initTileLayer);

	std::string getType();
	std::vector<std::vector<int>> getGidMap();

	static const std::string MapKeyPropertyWidth;
	static const std::string MapKeyPropertyHeight;
	static const std::string MapKeyPropertyType;
	static const std::string MapKeyPropertyObjectify;
	static const std::string MapKeyPropertyEncoding;
	static const std::string MapKeyPropertyEncodingValue;

protected:
	TileLayer(cocos2d::cocos_experimental::TMXLayer* initTileLayer);
	virtual ~TileLayer();

private:
	typedef MapLayer super;
	cocos2d::cocos_experimental::TMXLayer* tileLayer;
};
