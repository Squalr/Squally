#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class CshlBlock : public BlockBase
{
public:
	static CshlBlock* create(BlockType blockType = BlockType::Normal);
	
protected:
	CshlBlock(BlockType blockType);
	virtual ~CshlBlock();

	void onEnter() override;
	void initializePositions() override;
	unsigned char compute() override;

private:
	typedef BlockBase super;
};
