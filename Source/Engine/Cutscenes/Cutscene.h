#pragma once
#include "cocos2d.h"

#include "Engine/Input/InputManager.h"
#include "Engine/UI/FadeScene.h"
#include "Engine/Utils/GameUtils.h"
#include "Resources.h"

using namespace cocos2d;

class Cutscene : public FadeScene
{
public:
	void setCutsceneCompleteCallback(std::function<void()> callback);

protected:
	Cutscene();
	~Cutscene();

	void endCutscene();

private:
	std::function<void()> cutsceneCompleteCallback;
};
