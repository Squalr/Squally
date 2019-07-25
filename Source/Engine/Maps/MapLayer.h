#pragma once

#include <string>

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Value;
	typedef std::map<std::string, Value> ValueMap;
}

class GameObject;

class MapLayer : public SmartNode
{
public:
	static MapLayer* create(const cocos2d::ValueMap& initProperties, std::string name, std::string type = "", const std::vector<GameObject*>& objects = { });

	std::string getLayerType();
	bool isHackable();
	bool isElevateTarget();

	static const std::string MapKeyType;
	static const std::string MapKeyPropertyName;
	static const std::string MapKeyPropertyValue;
	static const std::string MapKeyPropertyDepth;
	static const std::string MapKeyPropertyIsHackable;
	static const std::string MapKeyPropertyIsElevateTarget;

protected:
	MapLayer(const cocos2d::ValueMap& initProperties, std::string name, std::string type);
	MapLayer(const cocos2d::ValueMap& initProperties, std::string name, std::string type, const std::vector<GameObject*>& objects);
	MapLayer();
	~MapLayer();

	void initializeListeners() override;

	std::string layerName;
	std::string layerType;
	cocos2d::ValueMap properties;

private:
	typedef SmartNode super;
};
