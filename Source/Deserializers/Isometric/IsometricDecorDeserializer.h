#pragma once

#include "Engine/Deserializers/Objects/ObjectDeserializer.h"

class IsometricDecorDeserializer : public ObjectDeserializer
{
public:
	static IsometricDecorDeserializer* create();

	static const std::string MapKeyTypeDecor;
	
protected:
	IsometricDecorDeserializer();
	virtual ~IsometricDecorDeserializer();

private:
	typedef ObjectDeserializer super;

	void deserialize(ObjectDeserializer::ObjectDeserializationRequestArgs* args) override;
};
