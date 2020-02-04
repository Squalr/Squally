#pragma once

#include "Scenes/Cipher/Components/CipherComponentBase.h"

namespace cocos2d
{
	class Sprite;
}

class CipherState;
class ClickableNode;
class InputOutputItem;
class LocalizedLabel;
class ScrollPane;

class InputsOutputsPanel : public CipherComponentBase
{
public:
	static InputsOutputsPanel* create();

protected:
	InputsOutputsPanel();
	virtual ~InputsOutputsPanel();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onAnyStateChange(CipherState* cipherState) override;

private:
	typedef CipherComponentBase super;
	
	void loadPuzzleData();
	void selectInputOutputPairAtIndex(int index);
	
	LocalizedLabel* inputsHeaderLabel;
	LocalizedLabel* outputsHeaderLabel;
	ScrollPane* scrollPane;
	cocos2d::Node* ioItemsNode;
	cocos2d::Sprite* ioSelectionMarker;

	CipherState* currentCipherState;
	std::vector<InputOutputItem*> ioItems;
};
