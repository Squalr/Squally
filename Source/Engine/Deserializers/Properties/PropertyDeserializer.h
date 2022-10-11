#pragma once

#include "cocos/base/CCValue.h"

#include "Engine/SmartNode.h"

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
