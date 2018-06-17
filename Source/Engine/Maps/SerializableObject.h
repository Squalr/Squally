#pragma once
#include "cocos2d.h"

#include "Utils/GameUtils.h"

using namespace cocos2d;

class SerializableObject : public Node
{
public:
	std::string serialize();

	static const std::string KeyType;
	static const std::string KeyName;
	static const std::string KeyWidth;
	static const std::string KeyHeight;
	static const std::string KeyXPosition;
	static const std::string KeyYPosition;
	static const std::string KeyRotation;

protected:
	SerializableObject(ValueMap* initProperties);
	~SerializableObject();

	ValueMap* properties;
};
