#pragma once
#include "cocos2d.h"

#include "Engine/Maps/SerializableMap.h"
#include "Engine/SmartScene.h"

using namespace cocos2d;

// Forward declarations
class SerializableMap;

class IMap : public SmartScene
{
public:
	virtual void loadMap(SerializableMap* levelMap) = 0;
};
