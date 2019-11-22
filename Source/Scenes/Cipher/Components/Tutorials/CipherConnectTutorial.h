#pragma once

#include "Scenes/Cipher/Components/Tutorials/CipherTutorialBase.h"

class FocusTakeOver;
class HelpArrow;
class LocalizedLabel;
class ClickableTextNode;

class CipherConnectTutorial : public CipherTutorialBase
{
public:
	static CipherConnectTutorial* create();

	static const std::string MapKeyTutorial;

protected:
	void onBeforeStateChange(CipherState* gameState) override;
	void onAnyStateChange(CipherState* gameState) override;

private:
	typedef CipherTutorialBase super;
	CipherConnectTutorial();
	~CipherConnectTutorial();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void initializeCallbacks(CipherState* gameState);
	bool tryHijackState(CipherState* gameState) override;
	void unHijackState(CipherState* gameState) override;
\
	FocusTakeOver* focusTakeOver;
};
