#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Shaders/PostProcess.h"
#include "GUI/Components/MenuSprite.h"
#include "Utils/HackUtils.h"

using namespace cocos2d;

class Bejeweled : public Node
{
public:
	static Bejeweled * create();

private:
	Bejeweled();
	~Bejeweled();

	void initializePositions();
	void initializeListeners();
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onClose(MenuSprite* menuSprite);
};

