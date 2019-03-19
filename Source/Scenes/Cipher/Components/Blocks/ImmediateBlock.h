#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class ImmediateBlock : public BlockBase
{
public:
	static ImmediateBlock* create(BlockType blockType = BlockType::Normal);
	
protected:
	BlockBase* spawn() override;

private:
	typedef BlockBase super;
	ImmediateBlock(BlockType blockType);
	~ImmediateBlock();

	void onEnter() override;
	void initializePositions() override;
};
