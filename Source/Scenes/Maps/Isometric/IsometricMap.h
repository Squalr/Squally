#pragma once
#include "cocos2d.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/Maps/SerializableMap.h"
#include "Engine/UI/Mouse.h"
#include "Engine/UI/InfiniteParallaxNode.h"
#include "Engine/UI/HUD/DeveloperHud.h"
#include "Engine/UI/HUD/HackerModeHud.h"
#include "Engine/UI/HUD/Hud.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Isometric/Squally/IsometricSqually.h"
#include "Events/NavigationEvents.h"
#include "Menus/Dialog/DialogMenu.h"
#include "Menus/Pause/PauseMenu.h"
#include "Resources/BackgroundResources.h"
#include "Resources/ShaderResources.h"
#include "Scenes/Maps/MapBase.h"
#include "Scenes/Maps/Platformer/Backgrounds/MatrixRain/MatrixRain.h"

using namespace cocos2d;

// Forward declarations
class SerializableMap;

class IsometricMap : public MapBase
{
public:
	static IsometricMap* create();

protected:
	IsometricMap();
	~IsometricMap();

private:
	void initializePositions() override;
	void initializeListeners() override;
	void onEnter() override;
};
