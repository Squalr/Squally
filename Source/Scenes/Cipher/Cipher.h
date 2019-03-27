#pragma once
#include <functional>

#include "cocos/base/CCEventKeyboard.h"

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Node;
	class LayerColor;
	class Sprite;
}

class AsciiButton;
class AsciiTable;
class CipherBackground;
class CipherDecor;
class CipherFrame;
class CipherLock;
class CipherPuzzleData;
class CipherState;
class CipherStateGameEnd;
class CipherStateLoadInitialState;
class CipherStateNeutral;
class CipherStateStartGame;
class CipherStateTesting;
class CipherStateUnlocking;
class CipherStateVictory;
class ClickableNode;
class ClickableTextNode;
class DisplayModeToggles;
class InputsOutputsPanel;
class LocalizedLabel;
class QuitButton;
class TestButton;
class ToolBox;
class UnlockButton;

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

	AsciiButton* asciiButton;
	CipherBackground* cipherBackground;
	CipherLock* cipherLock;
	CipherFrame* cipherFrame;
	CipherDecor* cipherDecor;
	DisplayModeToggles* displayModeToggles;
	TestButton* testButton;
	UnlockButton* unlockButton;
	InputsOutputsPanel* inputsOutputsPanel;
	QuitButton* quitButton;
	ToolBox* toolBox;

	CipherState* cipherState;
	CipherStateGameEnd* cipherStateGameEnd;
	CipherStateLoadInitialState* cipherStateLoadInitialState;
	CipherStateNeutral* cipherStateNeutral;
	CipherStateStartGame* cipherStateStartGame;
	CipherStateTesting* cipherStateTesting;
	CipherStateUnlocking* cipherStateUnlocking;
	CipherStateVictory* cipherStateVictory;

	cocos2d::LayerColor* backdrop;
	AsciiTable* asciiTable;

	static const cocos2d::Color3B TitleColor;
};
