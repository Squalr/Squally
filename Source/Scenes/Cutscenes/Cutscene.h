#pragma once
#include "cocos2d.h"

#include "Engine/Input/InputManager.h"
#include "Engine/Rendering/Components/FadeScene.h"
#include "Engine/Rendering/Components/Mouse.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntities.h"
#include "Resources.h"

using namespace cocos2d;

class Cutscene : public FadeScene
{
protected:
	Cutscene();
	~Cutscene();

private:
};
