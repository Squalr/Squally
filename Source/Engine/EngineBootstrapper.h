#pragma once
#include "cocos2d.h"

#include "Engine/Analytics/Analytics.h"
#include "Engine/Input/Input.h"
#include "Engine/Input/MouseState.h"
#include "Engine/Maps/ObjectLayerDeserializer.h"
#include "Engine/Physics/CollisionDeserializer.h"
#include "Engine/Terrain/TerrainDeserializer.h"
#include "Scenes/SceneDirector.h"

using namespace cocos2d;

class EngineBootstrapper
{
public:
	static void initialize();
	static void shutDown();
};
