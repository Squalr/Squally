#pragma once

#include "Scenes/Cipher/Components/CipherComponentBase.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;
class ClickableTextNode;
class DisplayModeToggles;
class ImmediateBlock;
class LocalizedLabel;
class RadioButton;
class ScrollPane;
class SmartAsciiLabel;

class AsciiTable : public CipherComponentBase
{
public:
	static AsciiTable* create();

	void open(ImmediateBlock* immediateBlock, std::function<void()> onCloseCallback);

protected:
	AsciiTable();
	virtual ~AsciiTable();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onAnyStateChange(CipherState* cipherState) override;

private:
	typedef CipherComponentBase super;

	std::vector<ImmediateBlock*> asciiLetters;

	void select(ImmediateBlock* block);
	void close();

	cocos2d::Sprite* background = nullptr;
	ScrollPane* scrollPane = nullptr;
	cocos2d::Sprite* selectionSprite = nullptr;
	DisplayModeToggles* displayModeToggles = nullptr;
	cocos2d::Sprite* frame = nullptr;
	ClickableTextNode* returnButton = nullptr;
	LocalizedLabel* asciiTableTitle = nullptr;
	LocalizedLabel* chooseANewValueTitle = nullptr;

	ImmediateBlock* selectedBlock = nullptr;
	ImmediateBlock* immediateBlock = nullptr;
	std::function<void()> onCloseCallback = nullptr;
};
