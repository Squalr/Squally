#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Shaders/PostProcess.h"
#include "GUI/Components//MenuSprite.h"
#include "Objects/Hackables/HackableObject.h"

using namespace cocos2d;

class DataCodeMenu : public Node
{
public:
	static DataCodeMenu * create();

	void activate(HackableObject::HackableObjectEditArgs* hackableObjectArgs);

private:
	DataCodeMenu();
	~DataCodeMenu();

	void initializePositions();
	void initializeListeners();
	void onClose(MenuSprite* menuSprite);
	void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;

	HackableObject* activeHackableObject;
	Sprite* hackableObjectPreview;

	LayerColor* layerColor;
	Sprite* menuBackground;
	MenuSprite* dataButton;
	MenuSprite* codeButton;
	MenuSprite* returnButton;
	PostProcess* gamePostProcessNightVision;

	static const Size maxPreviewSize;
};

