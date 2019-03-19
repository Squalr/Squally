#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class OrBlock : public BlockBase
{
public:
	static OrBlock* create(bool isToolBoxItem = false);
	
protected:
	BlockBase* spawn() override;

private:
	typedef BlockBase super;
	OrBlock(bool isToolBoxItem);
	~OrBlock();

	void onEnter() override;
	void initializePositions() override;
};
