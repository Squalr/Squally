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
	
	LocalizedLabel* inputsHeaderLabel = nullptr;
	LocalizedLabel* outputsHeaderLabel = nullptr;
	ScrollPane* scrollPane = nullptr;
	cocos2d::Node* ioItemsNode = nullptr;
	cocos2d::Sprite* ioSelectionMarker = nullptr;

	CipherState* currentCipherState = nullptr;
	std::vector<InputOutputItem*> ioItems;
};
