#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class SerializableObject : public Node
{
public:
	std::string serialize();

protected:
	SerializableObject();
	~SerializableObject();
};
