#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class CshlBlock : public BlockBase
{
public:
	static CshlBlock* create(bool isToolBoxItem = false);
	
protected:
	BlockBase* spawn() override;

private:
	typedef BlockBase super;
	CshlBlock(bool isToolBoxItem);
	~CshlBlock();

	void onEnter() override;
	void initializePositions() override;
};
