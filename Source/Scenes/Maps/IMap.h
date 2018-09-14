#pragma once
#include "cocos2d.h"

#include "Engine/Maps/SerializableMap.h"
#include "Engine/UI/FadeScene.h"

using namespace cocos2d;

// Forward declarations
class SerializableMap;

class IMap : public FadeScene
{
public:
	virtual void loadMap(SerializableMap* levelMap) = 0;

};
