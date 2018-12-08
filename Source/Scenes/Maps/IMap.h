#pragma once
#include "cocos2d.h"

#include "Engine/GlobalScene.h"
#include "Engine/Maps/SerializableMap.h"

using namespace cocos2d;

// Forward declarations
class SerializableMap;

class IMap : public GlobalScene
{
public:
	virtual void loadMap(SerializableMap* levelMap) = 0;
};
