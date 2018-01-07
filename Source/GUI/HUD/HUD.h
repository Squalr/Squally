#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "GUI/Menus/Dialog/DialogMenu.h"

using namespace cocos2d;

class HUD : public Node
{
public:
	static HUD * create();

private:
	HUD();
	~HUD();

	void onEnter() override;
	void initializePositions();
	void initializeListeners();
	void onDialogOpen(EventCustom* event);

	Sprite* heart;
	Sprite* healthBarFrame;

	Node* dialogNode;
};

