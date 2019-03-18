#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class CshlBlock : public BlockBase
{
public:
	static CshlBlock* create();

private:
	typedef BlockBase super;
	CshlBlock();
	~CshlBlock();

	void onEnter() override;
	void initializePositions() override;
};
