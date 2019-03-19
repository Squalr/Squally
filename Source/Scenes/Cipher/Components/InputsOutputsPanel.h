#pragma once

#include "Scenes/Cipher/Components/CipherComponentBase.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedLabel;

class InputsOutputsPanel : public CipherComponentBase
{
public:
	static InputsOutputsPanel* create();

protected:
	void onBeforeStateChange(CipherState* cipherState) override;
	void onAnyStateChange(CipherState* cipherState) override;

private:
	typedef CipherComponentBase super;
	InputsOutputsPanel();
	~InputsOutputsPanel();

	void onEnter() override;
	void initializePositions() override;
	void updateDisplayedLosses(CipherState* cipherState);

	LocalizedLabel* inputsLabel;
	LocalizedLabel* outputsLabel;

	std::vector<std::tuple<std::string, std::string>> inputs;
};
