#pragma once
#include "cocos2d.h"

#include "Engine/Input/InputManager.h"
#include "Engine/Rendering/Components/FadeScene.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/NavigationEvents.h"
#include "Resources.h"

using namespace cocos2d;

class Cutscene : public FadeScene
{
protected:
	Cutscene();
	~Cutscene();

private:
};
