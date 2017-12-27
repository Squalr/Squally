#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "GUI/Components/MenuSprite.h"

using namespace cocos2d;

class Slider : public Node
{
public:
	static Slider * create(float progress);

	void setProgressUpdateCallback(std::function<void(float progress)> callback);
	void initializePositions();

protected:
	Slider(float progress);
	~Slider();

private:
	void onDrag(MenuSprite* sprite, EventMouse* args);
	void setProgress(float newProgress);

	MenuSprite* slide;
	Sprite* frame;
	Sprite* progressBar;
	ClippingRectangleNode* progressClip;

	float progress;

	std::function<void(float progress)> progressUpdateEvent;
};

