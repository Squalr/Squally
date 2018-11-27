#pragma once
#include "cocos2d.h"

#include "Engine/GlobalNode.h"

using namespace cocos2d;

class PlatformerEntityDeserializer : public GlobalNode
{
protected:
	PlatformerEntityDeserializer();
	~PlatformerEntityDeserializer();

	static const std::string KeyTypeEntity;
};
