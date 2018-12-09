#pragma once
#include "Engine/GlobalNode.h"

class PlatformerEntityDeserializer : public GlobalNode
{
protected:
	PlatformerEntityDeserializer();
	virtual ~PlatformerEntityDeserializer();

	static const std::string KeyTypeEntity;
};
