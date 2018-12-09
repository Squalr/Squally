#pragma once

#include "Engine/GlobalScene.h"
#include "Engine/Maps/SerializableMap.h"

// Forward declarations
class SerializableMap;

class IMap : public GlobalScene
{
public:
	virtual void loadMap(SerializableMap* levelMap) = 0;
};
