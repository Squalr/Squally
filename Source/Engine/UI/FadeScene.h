#pragma once
#include "cocos2d.h"

#include "Engine/SmartScene.h"
#include "Resources.h"

using namespace cocos2d;

class FadeScene : public SmartScene
{
protected:
	FadeScene();
	~FadeScene();

	void setFadeSpeed(float newFadeSpeed);
	float getFadeSpeed();
	void onEnter() override;

	LayerColor* layerColor;
	FiniteTimeAction* fadeAction;

private:
	void pause() override;

	float fadeSpeed;
	static const float defaultFadeSpeed;
};

