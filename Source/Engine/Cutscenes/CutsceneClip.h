#pragma once
#include <functional>

#include "Engine/UI/FadeScene.h"

class CutsceneClip : public FadeScene
{
public:
	void setCutsceneClipCompleteCallback(std::function<void()> callback);

protected:
	CutsceneClip();
	virtual ~CutsceneClip();

	void endCutsceneClip();

private:
	std::function<void()> cutsceneClipCompleteCallback;
};
