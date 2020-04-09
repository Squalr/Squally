#pragma once

#include "Engine/Deserializers/Objects/ObjectDeserializer.h"

class DropPoolDeserializer : public ObjectDeserializer
{
public:
	static DropPoolDeserializer* create();

	static const std::string MapKeyTypeDropPool;

protected:
	DropPoolDeserializer();
	virtual ~DropPoolDeserializer();
	
private:
	typedef ObjectDeserializer super;
};
