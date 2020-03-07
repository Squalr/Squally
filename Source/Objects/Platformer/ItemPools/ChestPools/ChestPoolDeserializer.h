#pragma once

#include "Engine/Deserializers/Objects/ObjectDeserializer.h"

class ChestPoolDeserializer : public ObjectDeserializer
{
public:
	static ChestPoolDeserializer* create();

	static const std::string MapKeyTypeChestPool;

protected:
	ChestPoolDeserializer();
	virtual ~ChestPoolDeserializer();

private:
	typedef ObjectDeserializer super;
};
