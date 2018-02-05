#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Shaders/PostProcess.h"
#include "GUI/Components/CCheckbox.h"
#include "GUI/Components/MenuLabel.h"
#include "GUI/Components/MenuSprite.h"
#include "GUI/Components/MouseOverPanel.h"
#include "GUI/Menus/HackerMode/CodeEditor.h"
#include "Objects/Hackables/HackableObject.h"
#include "Utils/HackUtils.h"

using namespace cocos2d;

class CodeMenu : public Node
{
public:
	static CodeMenu * create();

	void open(HackableObject* hackableObject);

private:
	CodeMenu();
	~CodeMenu();

	void initializePositions();
	void initializeListeners();
	void populateRows();
	void resume() override;
	bool onActivated(CCheckbox* checkbox, bool isActivated);
	void onCodeEditClick(MenuSprite* menuSprite);
	void onDataReferencesClick(MenuSprite* menuSprite);
	void onClose(MenuSprite* menuSprite);

	MouseOverPanel* constructAddressMouseOver(HackableCode* hackableCode, Label* address);
	MouseOverPanel* constructNameMouseOver(HackableCode* hackableCode, Label* name);
	MouseOverPanel* constructByteLengthMouseOver(HackableCode* hackableCode, Label* byteLength);
	MouseOverPanel* constructBytesMouseOver(HackableCode* hackableCode, Label* bytes);

	HackableObject* activeHackableObject;
	Sprite* codeMenuBackground;
	MenuLabel* codeMenuTitle;
	MenuSprite* closeButton;
	Node* header;
	Node* rows;
	Node* mouseOverMenuHost;
	CodeEditor* codeEditor;
	std::map<CCheckbox*, HackableCode*>* checkboxMap;
	std::map<MenuSprite*, HackableCode*>* editMap;

	static const float activeColumnOffset;
	static const float addressColumnOffset;
	static const float functionNameColumnOffset;
	static const float dataReferencesColumnOffset;
};

