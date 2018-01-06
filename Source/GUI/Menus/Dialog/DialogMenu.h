#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Gui/Menus/Dialog/Dialog.h"

using namespace cocos2d;

class DialogMenu : public Node
{
public:
	static DialogMenu * create(Dialog* dialogRoot);

private:
	DialogMenu(Dialog* dialogRoot);
	~DialogMenu();

	void onEnter() override;
	void initializePositions();

	Sprite* dialogMenu;
	Node* dialog;
	Sprite* frameLeft;
	Sprite* frameRight;
};

