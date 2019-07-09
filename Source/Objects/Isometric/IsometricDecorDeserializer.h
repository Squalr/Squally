#pragma once

#include "Engine/Maps/ObjectDeserializer.h"

class IsometricDecorDeserializer : public ObjectDeserializer
{
public:
	static void registerGlobalNode();

private:
	typedef ObjectDeserializer super;
	IsometricDecorDeserializer();
	~IsometricDecorDeserializer();

	void deserialize(ObjectDeserializer::ObjectDeserializationRequestArgs* args) override;

	static const std::string KeyTypeDecor;
};
