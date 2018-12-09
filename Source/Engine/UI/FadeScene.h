#pragma once
#include "Engine/SmartScene.h"

namespace cocos2d
{
	class FiniteTimeAction;
	class LayerColor;
}

class FadeScene : public SmartScene
{
protected:
	FadeScene();
	virtual ~FadeScene();

	void setFadeSpeed(float newFadeSpeed);
	float getFadeSpeed();
	void onEnter() override;

	cocos2d::LayerColor* layerColor;
	cocos2d::FiniteTimeAction* fadeAction;

private:
	void pause() override;

	float fadeSpeed;
	static const float defaultFadeSpeed;
};

