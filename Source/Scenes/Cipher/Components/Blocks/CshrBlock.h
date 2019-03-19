#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class CshrBlock : public BlockBase
{
public:
	static CshrBlock* create(bool isToolBoxItem = false);
	
protected:
	BlockBase* spawn() override;

private:
	typedef BlockBase super;
	CshrBlock(bool isToolBoxItem);
	~CshrBlock();

	void onEnter() override;
	void initializePositions() override;
};
