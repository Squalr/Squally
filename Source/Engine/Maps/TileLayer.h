#pragma once
#include <string>

#include "Engine/SmartNode.h"
#include "Engine/Maps/MapLayer.h"

namespace cocos2d
{
	namespace cocos_experimental
	{
		class TMXLayer;
	}
}

class TileLayer : public MapLayer
{
public:
	static TileLayer* deserialize(cocos2d::cocos_experimental::TMXLayer* initTileLayer);

	std::string getType();
	std::vector<std::vector<int>> getGidMap();
	bool isObjectified();

	static const std::string MapKeyTilemapType;
	static const std::string PropertyWidth;
	static const std::string PropertyHeight;
	static const std::string PropertyType;
	static const std::string PropertyObjectify;
	static const std::string PropertyEncoding;
	static const std::string PropertyEncodingValue;

protected:
	TileLayer(cocos2d::cocos_experimental::TMXLayer* initTileLayer);
	virtual ~TileLayer();

private:
	typedef MapLayer super;
	cocos2d::cocos_experimental::TMXLayer* tileLayer;

	bool objectified;
};
