#pragma once

#include "Engine/Deserializers/Objects/ObjectDeserializer.h"

class RecipePoolDeserializer : public ObjectDeserializer
{
public:
	static RecipePoolDeserializer* create();

	static const std::string MapKeyTypeRecipePool;

protected:
	RecipePoolDeserializer();
	virtual ~RecipePoolDeserializer();

private:
	typedef ObjectDeserializer super;
};
