#pragma once

#include "Scenes/Cipher/Components/Tutorials/CipherTutorialBase.h"

class FocusTakeOver;
class HelpArrow;
class LocalizedLabel;
class ClickableTextNode;

class CipherOverflowTutorial : public CipherTutorialBase
{
public:
	static CipherOverflowTutorial* create();

	static const std::string MapKeyTutorial;

protected:
	CipherOverflowTutorial();
	virtual ~CipherOverflowTutorial();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onBeforeStateChange(CipherState* cipherState) override;
	void onAnyStateChange(CipherState* cipherState) override;
	bool tryHijackState(CipherState* cipherState) override;
	void unHijackState(CipherState* cipherState) override;

private:
	typedef CipherTutorialBase super;

	void initializeCallbacks(CipherState* cipherState);
	void runTutorialPartA(CipherState* cipherState);
	void runTutorialPartB(CipherState* cipherState);

	FocusTakeOver* focusTakeOver;
	LocalizedLabel* introLabel;
	LocalizedLabel* connectLabel;
	ClickableTextNode* nextButtonIntro;
	ClickableTextNode* nextButtonConnect;
};
