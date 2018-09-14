#include "Cutscene.h"

Cutscene::Cutscene()
{
	this->cutsceneCompleteCallback = nullptr;
}

Cutscene::~Cutscene()
{
}

void Cutscene::setCutsceneCompleteCallback(std::function<void()> callback)
{
	this->cutsceneCompleteCallback = callback;
}

void Cutscene::endCutscene()
{
	if (this->cutsceneCompleteCallback != nullptr)
	{
		this->cutsceneCompleteCallback();
	}
}
