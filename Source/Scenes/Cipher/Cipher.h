#pragma once
#include <functional>

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
class CipherTransitionPanel;
class CipherTutorialBase;
class CipherState;
class CipherStateGameEnd;
class CipherStateLoadInitialState;
class CipherStateNeutral;
class CipherStateStartGame;
class CipherStateTesting;
class CipherStateTransitionNeutral;
class CipherStateTransitionUnlocking;
class CipherStateUnlocking;
class CipherStateVictory;
class ClickableNode;
class ClickableTextNode;
class DifficultySelectMenu;
class DisplayModeToggles;
class InputsOutputsPanel;
class LocalizedLabel;
class QuitButton;
class TestButton;
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
	void onMenuExit();
	void buildTutorialMap();

	std::function<void()> backClickCallback;

	cocos2d::Node* gameNode;
	cocos2d::Node* tutorialNode;
	AsciiButton* asciiButton;
	CipherBackground* cipherBackground;
	CipherLock* cipherLock;
	CipherFrame* cipherFrame;
	CipherDecor* cipherDecor;
	DifficultySelectMenu* difficultySelectMenu;
	DisplayModeToggles* displayModeToggles;
	TestButton* testButton;
	UnlockButton* unlockButton;
	InputsOutputsPanel* inputsOutputsPanel;
	QuitButton* quitButton;

	CipherState* cipherState;
	CipherStateGameEnd* cipherStateGameEnd;
	CipherStateLoadInitialState* cipherStateLoadInitialState;
	CipherStateNeutral* cipherStateNeutral;
	CipherStateStartGame* cipherStateStartGame;
	CipherStateTesting* cipherStateTesting;
	CipherStateTransitionUnlocking* cipherStateTransitionUnlocking;
	CipherStateUnlocking* cipherStateUnlocking;
	CipherStateVictory* cipherStateVictory;

	cocos2d::LayerColor* backdrop;
	AsciiTable* asciiTable;

	std::map<std::string, std::function<CipherTutorialBase*()>> cipherTutorialMap;

	static const cocos2d::Color3B TitleColor;
};
