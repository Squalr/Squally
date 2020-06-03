#pragma once

#include <string>

#include "Engine/Maps/GameObject.h"

namespace cocos2d
{
	class Value;
	typedef std::map<std::string, Value> ValueMap;
}

class MapLayer : public GameObject
{
public:
	static MapLayer* create(const cocos2d::ValueMap& properties, std::string name, std::string type = "", const std::vector<GameObject*>& objects = { });

	std::string getLayerType();
	bool isHackable();
	bool isElevateTarget();

	static const std::string MapKeyType;
	static const std::string PropertyName;
	static const std::string PropertyValue;
	static const std::string PropertyDepth;
	static const std::string PropertyIsHackable;
	static const std::string PropertyIsElevateTarget;
	static const std::string PropertyZSort;

protected:
	MapLayer(const cocos2d::ValueMap& properties, std::string name, std::string type);
	MapLayer(const cocos2d::ValueMap& properties, std::string name, std::string type, const std::vector<GameObject*>& objects);
	MapLayer();
	virtual ~MapLayer();

	void initializeListeners() override;
	void update(float dt) override;

	std::string layerName;
	std::string layerType;

private:
	typedef GameObject super;

	bool autoZSort;
};
