#pragma once

#include "Scenes/Cipher/Components/CipherComponentBase.h"

namespace cocos2d
{
	class Sprite;
}

class CipherPuzzleData;
class LocalizedLabel;
class ScrollPane;

class InputsOutputsPanel : public CipherComponentBase
{
public:
	static InputsOutputsPanel* create();

	void loadPuzzleData(CipherPuzzleData* cipherPuzzleData);

protected:
	void onBeforeStateChange(CipherState* cipherState) override;
	void onAnyStateChange(CipherState* cipherState) override;

private:
	typedef CipherComponentBase super;
	InputsOutputsPanel();
	~InputsOutputsPanel();

	void onEnter() override;
	void initializePositions() override;

	LocalizedLabel* inputsHeaderLabel;
	LocalizedLabel* outputsHeaderLabel;
	ScrollPane* scrollPane;
	cocos2d::Node* ioPanelsNode;
	cocos2d::Sprite* ioSelectionMarker;

	std::vector<LocalizedLabel*> inputLabels;
	std::vector<LocalizedLabel*> outputLabels;
	std::vector<std::tuple<std::string, std::string>> inputOutputMap;
};
