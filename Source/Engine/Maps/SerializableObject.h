#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class SerializableObject : public Node
{
public:
	static SerializableObject* deserialize(ValueMap object);

	std::string serialize();

protected:
	SerializableObject();
	~SerializableObject();
};
