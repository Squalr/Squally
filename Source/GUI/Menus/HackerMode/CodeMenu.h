#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Shaders/PostProcess.h"
#include "GUI/Components/MenuSprite.h"
#include "Objects/Hackables/HackableObject.h"

using namespace cocos2d;

class CodeMenu : public Node
{
public:
	static CodeMenu * create();

private:
	CodeMenu();
	~CodeMenu();

	void initializePositions();
	void initializeListeners();

	Sprite* codeMenuBackground;
};

