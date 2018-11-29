#pragma once
#include "cocos2d.h"

#include "Engine/UI/FadeScene.h"
#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

class CutsceneClip : public FadeScene
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
