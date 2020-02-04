#pragma once

#include "Scenes/Cipher/States/CipherStateBase.h"

class CipherStateGameEnd : public CipherStateBase
{
public:
	static CipherStateGameEnd* create();

protected:
	CipherStateGameEnd();
	virtual ~CipherStateGameEnd();
	
	void onBeforeStateEnter(CipherState* cipherState) override;
	void onStateEnter(CipherState* cipherState) override;
	void onStateReload(CipherState* cipherState) override;
	void onStateExit(CipherState* cipherState) override;

private:
	typedef CipherStateBase super;
};
