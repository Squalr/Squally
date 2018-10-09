#pragma once
#include "cocos2d.h"

#include "Engine/EngineBootstrapper.h"
#include "Entities/Platformer/PlatformerCollisionMapping.h"
#include "Scenes/SceneDirector.h"

using namespace cocos2d;

class Bootstrapper 
{
public:
	static void initialize();
	static void shutDown();
};
