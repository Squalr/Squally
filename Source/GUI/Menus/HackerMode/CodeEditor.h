#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Resources.h"
#include "Shaders/PostProcess.h"
#include "GUI/Components/MenuLabel.h"
#include "GUI/Components/MenuSprite.h"
#include "GUI/Components/MouseOverPanel.h"
#include "Objects/Hackables/HackableObject.h"
#include "Utils/HackUtils.h"

using namespace cocos2d;
using namespace cocos2d::ui;

class CodeEditor : public Node
{
public:
	static CodeEditor * create();

	void open(HackableCode* hackableCode);

private:
	CodeEditor();
	~CodeEditor();

	void initializePositions();
	void initializeListeners();
	void update(float) override;
	void onClose(MenuSprite* menuSprite);

	Sprite* codeEditorBackground;
	MenuSprite* closeButton;
	EditBox* assemblyCodeText;
	RichText* displayText;

	std::vector<RichElementText*>* displayTextElements;
	std::string previousAssemblyText;

	static const Size textSize;
};

