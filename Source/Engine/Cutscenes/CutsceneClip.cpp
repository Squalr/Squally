#include "CutsceneClip.h"

CutsceneClip::CutsceneClip()
{
}

CutsceneClip::~CutsceneClip()
{
}

void CutsceneClip::setCutsceneClipCompleteCallback(std::function<void()> callback)
{
	this->cutsceneClipCompleteCallback = callback;
}

void CutsceneClip::endCutsceneClip()
{
	if (this->cutsceneClipCompleteCallback != nullptr)
	{
		this->cutsceneClipCompleteCallback();
	}
}
