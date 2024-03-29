#pragma once
#include <functional>

#include "Engine/SmartScene.h"

class CutsceneClip : public SmartScene
{
public:
	void setCutsceneClipCompleteCallback(std::function<void()> callback);

protected:
	CutsceneClip();
	virtual ~CutsceneClip();

	void endCutsceneClip();

private:
	typedef SmartScene super;

	std::function<void()> cutsceneClipCompleteCallback = nullptr;
};
