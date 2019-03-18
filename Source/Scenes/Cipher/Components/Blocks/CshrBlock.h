#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class CshrBlock : public BlockBase
{
public:
	static CshrBlock* create();

private:
	typedef BlockBase super;
	CshrBlock();
	~CshrBlock();

	void onEnter() override;
	void initializePositions() override;
};
