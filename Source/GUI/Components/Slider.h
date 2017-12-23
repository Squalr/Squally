#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "GUI/Components/MenuSprite.h"

using namespace cocos2d;

class Slider : public Node
{
public:
	static Slider * create(float progress);

protected:
	Slider(float progress);
	~Slider();

private:
	void InitializePositions();
	void InitializeListeners();
	void OnMouseMove(EventMouse* event);

	MenuSprite* slide;
	Sprite* frame;
	Sprite* progressBar;

	float progress;
};

