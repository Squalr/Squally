#pragma once
#include <functional>

#include "Engine/Cutscenes/Cutscene.h"

class Music;

class IntroCutscene : public Cutscene
{
public:
	static IntroCutscene* create(std::function<void()> cutsceneCompleteCallback);

private:
	IntroCutscene(std::function<void()> cutsceneCompleteCallback);
	~IntroCutscene();

	void onEnter() override;

	Music* music;
};
