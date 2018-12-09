#pragma once

#include "Engine/UI/FadeScene.h"

// Forward declarations
class SerializableMap;

class IMap : public FadeScene
{
public:
	virtual void loadMap(SerializableMap* levelMap) = 0;
};
