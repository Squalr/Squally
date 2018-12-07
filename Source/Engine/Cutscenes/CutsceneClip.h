#pragma once
#include "cocos2d.h"

#include "Engine/SmartScene.h"
#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

class CutsceneClip : public SmartScene
{
public:
	void setCutsceneClipCompleteCallback(std::function<void()> callback);

protected:
	CutsceneClip();
	~CutsceneClip();

	void endCutsceneClip();

private:
	std::function<void()> cutsceneClipCompleteCallback;
};
