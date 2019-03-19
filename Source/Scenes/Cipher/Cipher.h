#pragma once
#include <functional>

#include "cocos/base/CCEventKeyboard.h"

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Node;
	class Sprite;
}

class AsciiTable;
class CipherBackground;
class CipherDecor;
class CipherFrame;
class CipherPuzzleData;
class ClickableNode;
class ClickableTextNode;
class DisplayModeToggles;
class ExecuteButton;
class InputsOutputsPanel;
class QuitButton;
class ToolBox;
class LocalizedLabel;

class Cipher : public SmartNode
{
public:
	static Cipher* create();

	void openCipher(CipherPuzzleData* cipherPuzzleData);
	void setBackClickCallback(std::function<void()> backClickCallback);

protected:
	Cipher();
	~Cipher();

private:
	typedef SmartNode super;
	
	void onEnter() override;
	void initializeListeners() override;
	void initializePositions() override;
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onMenuExit();

	std::function<void()> backClickCallback;

	AsciiTable* asciiTable;
	CipherBackground* cipherBackground;
	CipherFrame* cipherFrame;
	CipherDecor* cipherDecor;
	DisplayModeToggles* displayModeToggles;
	ExecuteButton* executeButton;
	InputsOutputsPanel* inputsOutputsPanel;
	QuitButton* quitButton;
	ToolBox* toolBox;

	static const cocos2d::Color3B TitleColor;
};
