#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Value;
	typedef std::map<std::string, Value> ValueMap;
}

class GameObject;

class PropertyDeserializer : public SmartNode
{
public:
	virtual void deserializeProperties(GameObject* owner, cocos2d::ValueMap properties) = 0;
	virtual std::string getPropertyDeserializerKey();

protected:
	PropertyDeserializer();
	virtual ~PropertyDeserializer();

private:
	typedef SmartNode super;
};
