#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class CshlBlock : public BlockBase
{
public:
	static CshlBlock* create(BlockType blockType = BlockType::Normal);
	
protected:
	char compute() override;
	BlockBase* spawn() override;

private:
	typedef BlockBase super;
	CshlBlock(BlockType blockType);
	~CshlBlock();

	void onEnter() override;
	void initializePositions() override;
};
