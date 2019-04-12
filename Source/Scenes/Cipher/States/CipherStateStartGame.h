#pragma once

#include "Scenes/Cipher/States/CipherStateBase.h"

class CipherStateStartGame : public CipherStateBase
{
public:
	static CipherStateStartGame* create();

protected:
	void onBeforeStateEnter(CipherState* cipherState) override;
	void onStateEnter(CipherState* cipherState) override;
	void onStateReload(CipherState* cipherState) override;
	void onStateExit(CipherState* cipherState) override;

private:
	typedef CipherStateBase super;
	CipherStateStartGame();
	~CipherStateStartGame();
};
