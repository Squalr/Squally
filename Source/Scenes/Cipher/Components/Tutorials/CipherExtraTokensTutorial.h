#pragma once

#include "Scenes/Cipher/Components/Tutorials/CipherTutorialBase.h"

class FocusTakeOver;
class HelpArrow;
class LocalizedLabel;
class ClickableTextNode;

class CipherExtraTokensTutorial : public CipherTutorialBase
{
public:
	static CipherExtraTokensTutorial* create();

	static const std::string MapKeyTutorial;

protected:
	void onBeforeStateChange(CipherState* cipherState) override;
	void onAnyStateChange(CipherState* cipherState) override;

private:
	typedef CipherTutorialBase super;
	CipherExtraTokensTutorial();
	virtual ~CipherExtraTokensTutorial();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void initializeCallbacks(CipherState* cipherState);
	bool tryHijackState(CipherState* cipherState) override;
	void unHijackState(CipherState* cipherState) override;

	void runTutorialPartA(CipherState* cipherState);

	FocusTakeOver* focusTakeOver;
	LocalizedLabel* introLabel;
	ClickableTextNode* nextButtonIntro;
};
