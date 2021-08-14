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

protected:
	Cipher();
	virtual ~Cipher();
	void onEnter() override;
	void initializeListeners() override;
	void initializePositions() override;

private:
	typedef SmartNode super;
	
	void onMenuExit();
	void buildTutorialMap();

	std::function<void()> backClickCallback = nullptr;

	cocos2d::Node* gameNode = nullptr;
	cocos2d::Node* tutorialNode = nullptr;
	AsciiButton* asciiButton = nullptr;
	CipherBackground* cipherBackground = nullptr;
	CipherLock* cipherLock = nullptr;
	CipherFrame* cipherFrame = nullptr;
	CipherDecor* cipherDecor = nullptr;
	DifficultySelectMenu* difficultySelectMenu = nullptr;
	DisplayModeToggles* displayModeToggles = nullptr;
	TestButton* testButton = nullptr;
	UnlockButton* unlockButton = nullptr;
	InputsOutputsPanel* inputsOutputsPanel = nullptr;
	QuitButton* quitButton = nullptr;

	CipherState* cipherState = nullptr;
	CipherStateGameEnd* cipherStateGameEnd = nullptr;
	CipherStateLoadInitialState* cipherStateLoadInitialState = nullptr;
	CipherStateNeutral* cipherStateNeutral = nullptr;
	CipherStateStartGame* cipherStateStartGame = nullptr;
	CipherStateTesting* cipherStateTesting = nullptr;
	CipherStateTransitionUnlocking* cipherStateTransitionUnlocking = nullptr;
	CipherStateUnlocking* cipherStateUnlocking = nullptr;
	CipherStateVictory* cipherStateVictory = nullptr;

	cocos2d::LayerColor* backdrop = nullptr;
	AsciiTable* asciiTable = nullptr;

	std::map<std::string, std::function<CipherTutorialBase*()>> cipherTutorialMap;

	static const cocos2d::Color3B TitleColor;
};
