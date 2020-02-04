#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class CshrBlock : public BlockBase
{
public:
	static CshrBlock* create(BlockType blockType = BlockType::Normal);
	
protected:
	CshrBlock(BlockType blockType);
	virtual ~CshrBlock();

	void onEnter() override;
	void initializePositions() override;
	unsigned char compute() override;

private:
	typedef BlockBase super;
};
