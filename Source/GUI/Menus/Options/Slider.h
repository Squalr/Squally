#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "GUI/Components/MenuSprite.h"

using namespace cocos2d;

class Slider : public Node
{
public:
	static Slider * create();

protected:
	Slider();
	~Slider();

private:
	void InitializeListeners();
	void OnMouseMove(EventMouse* event);

	MenuSprite* slider;
	Sprite* frame;
	Sprite* progress;
};

