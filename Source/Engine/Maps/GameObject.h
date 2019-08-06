#pragma once
#include <string>

#include "cocos/math/CCGeometry.h"

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Value;
	typedef std::map<std::string, Value> ValueMap;
}

class GameObject : public SmartNode
{
public:
	static void saveObjectState(std::string uniqueIdentifier, std::string key, cocos2d::Value value);
	std::string getUniqueIdentifier();
	void setZSorted(bool zSorted);
	bool isZSorted();

	static const std::string MapKeyId;
	static const std::string MapKeyName;
	static const std::string MapKeyPoints;
	static const std::string MapKeyPolyLinePoints;
	static const std::string MapKeyRotation;
	static const std::string MapKeyType;
	static const std::string MapKeyWidth;
	static const std::string MapKeyHeight;
	static const std::string MapKeyXPosition;
	static const std::string MapKeyYPosition;
	static const std::string MapKeyScale;
	static const std::string MapKeyScaleX;
	static const std::string MapKeyScaleY;
	static const std::string MapKeyAutoScale;
	static const std::string MapKeyFlipX;
	static const std::string MapKeyFlipY;
	static const std::string MapKeyRepeatX;
	static const std::string MapKeyRepeatY;
	static const std::string MapKeyEvent;
	static const std::string MapKeyState;
	static const std::string MapKeyQuest;
	static const std::string MapKeyQuestLine;
	static const std::string MapKeyQuestTag;
	static const std::string MapKeyAttachedBehavior;
	static const std::string MapKeyAttachedBehaviorArgs;
	static const std::string MapKeyArgs;

	static const std::string MapKeyGid;

	static const std::string MapKeyMetaIsIsometric;
	static const std::string MapKeyMetaMapHeight;
	static const std::string MapKeyMetaMapWidth;
	static const std::string MapKeyMetaMapIdentifier;

	static const std::vector<std::string> AttributeKeys;

	static const std::string MapKeyPropertyName;
	static const std::string MapKeyPropertyType;
	static const std::string MapKeyPropertyValue;

protected:
	GameObject();
	GameObject(const cocos2d::ValueMap& initProperties);
	virtual ~GameObject();
	
	void onEnter() override;
	void initializeListeners() override;
	bool isMapObject();
	void saveObjectState(std::string key, cocos2d::Value value);
	const cocos2d::Value& getObjectStateOrDefault(std::string key, const cocos2d::Value& defaultValue);
	void loadObjectState();
	void broadcastMapEvent(std::string eventName, cocos2d::ValueMap args);
	void listenForMapEvent(std::string eventName, std::function<void(cocos2d::ValueMap args)> callback);
	virtual void onObjectStateLoaded();

	cocos2d::ValueMap properties;
	std::string mapEvent;
	std::vector<cocos2d::Vec2> polylinePoints;

private:
	typedef SmartNode super;
	bool isAttributeOrHiddenProperty(std::string propertyName);
	bool containsAttributes();
	bool containsProperties();

	bool zSorted;
	std::string uniqueIdentifier;
	cocos2d::ValueMap saveProperties;
};
