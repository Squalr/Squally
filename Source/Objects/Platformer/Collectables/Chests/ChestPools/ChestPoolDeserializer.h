#pragma once

#include "Engine/Deserializers/ObjectDeserializer.h"

class ChestPoolDeserializer : public ObjectDeserializer
{
public:
	static ChestPoolDeserializer* create();

	static const std::string MapKeyTypeChestPool;

private:
	typedef ObjectDeserializer super;

	ChestPoolDeserializer();
	~ChestPoolDeserializer();
};
