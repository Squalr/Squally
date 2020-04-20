#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedLabel;
class ConstantString;

class RegisterBlockSigned : public SmartNode
{
public:
	static RegisterBlockSigned* create();

	void clearHighlights();
	void highlightEax(bool isDest);
	void highlightEbx(bool isDest);
	void highlightEcx(bool isDest);
	void highlightEdx(bool isDest);
	void highlightEdi(bool isDest);
	void highlightEsi(bool isDest);
	void highlightEbp(bool isDest);
	void highlightEsp(bool isDest);
	void highlightEip(bool isDest);
	void highlightEaxPtr(bool isDest, int offset);
	void highlightEbxPtr(bool isDest, int offset);
	void highlightEcxPtr(bool isDest, int offset);
	void highlightEdxPtr(bool isDest, int offset);
	void highlightEdiPtr(bool isDest, int offset);
	void highlightEsiPtr(bool isDest, int offset);
	void highlightEbpPtr(bool isDest, int offset);
	void highlightEspPtr(bool isDest, int offset);
	void highlightEipPtr(bool isDest, int offset);

	void initEax(long long eax, std::vector<long long> values = { });
	void initEbx(long long ebx, std::vector<long long> values = { });
	void initEcx(long long ecx, std::vector<long long> values = { });
	void initEdx(long long edx, std::vector<long long> values = { });
	void initEdi(long long edi, std::vector<long long> values = { });
	void initEsi(long long esi, std::vector<long long> values = { });
	void initEbp(long long ebp, std::vector<long long> values = { });
	void initEsp(long long esp, std::vector<long long> values = { });
	void initEip(long long eip, std::vector<long long> values = { });

	void setEax(long long eax);
	void setEbx(long long ebx);
	void setEcx(long long ecx);
	void setEdx(long long edx);
	void setEdi(long long edi);
	void setEsi(long long esi);
	void setEbp(long long ebp);
	void setEsp(long long esp);
	void setEip(long long eip);

	void setEaxPtr(long long value, int offset);
	void setEbxPtr(long long value, int offset);
	void setEcxPtr(long long value, int offset);
	void setEdxPtr(long long value, int offset);
	void setEdiPtr(long long value, int offset);
	void setEsiPtr(long long value, int offset);
	void setEbpPtr(long long value, int offset);
	void setEspPtr(long long value, int offset);
	void setEipPtr(long long value, int offset);

	long long getEax();
	long long getEbx();
	long long getEcx();
	long long getEdx();
	long long getEdi();
	long long getEsi();
	long long getEbp();
	long long getEsp();
	long long getEip();

	long long getEaxPtr(int offset);
	long long getEbxPtr(int offset);
	long long getEcxPtr(int offset);
	long long getEdxPtr(int offset);
	long long getEdiPtr(int offset);
	long long getEsiPtr(int offset);
	long long getEbpPtr(int offset);
	long long getEspPtr(int offset);
	long long getEipPtr(int offset);

protected:
	RegisterBlockSigned();
	~RegisterBlockSigned();
	
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;

	void highlightSource(cocos2d::Vec2 position);
	void highlightDest(cocos2d::Vec2 position);

	struct Register
	{
		bool initialized;
		long long currentValue;
		long long initialValue;
		std::vector<long long> initialValues;
		std::vector<long long> currentValues;

		Register() : initialized(false), currentValue(0), initialValue(0), initialValues({}), currentValues({}) { }
		Register(long long currentValue, long long initialValue, std::vector<long long> initialValues, std::vector<long long> currentValues) :
			initialized(true), currentValue(currentValue), initialValue(initialValue), initialValues(initialValues), currentValues(currentValues) {}
	};

	void addToData(long long value, int index, Node* node, std::vector<ConstantString*>* strings, std::vector<LocalizedLabel*>* labels);

	cocos2d::Sprite* registerBlock;
	LocalizedLabel* titleLabel;
	LocalizedLabel* memoryTitleLabel;
	LocalizedLabel* eaxLabel;
	LocalizedLabel* ebxLabel;
	LocalizedLabel* ecxLabel;
	LocalizedLabel* edxLabel;
	LocalizedLabel* ediLabel;
	LocalizedLabel* esiLabel;
	LocalizedLabel* ebpLabel;
	LocalizedLabel* espLabel;
	LocalizedLabel* eipLabel;
	cocos2d::Node* eaxPtrNode;
	cocos2d::Node* ebxPtrNode;
	cocos2d::Node* ecxPtrNode;
	cocos2d::Node* edxPtrNode;
	cocos2d::Node* ediPtrNode;
	cocos2d::Node* esiPtrNode;
	cocos2d::Node* ebpPtrNode;
	cocos2d::Node* espPtrNode;
	cocos2d::Node* eipPtrNode;
	cocos2d::Sprite* destSelector;
	cocos2d::Sprite* srcSelector;

	std::vector<ConstantString*> eaxPtrStrings;
	std::vector<ConstantString*> ebxPtrStrings;
	std::vector<ConstantString*> ecxPtrStrings;
	std::vector<ConstantString*> edxPtrStrings;
	std::vector<ConstantString*> ediPtrStrings;
	std::vector<ConstantString*> esiPtrStrings;
	std::vector<ConstantString*> ebpPtrStrings;
	std::vector<ConstantString*> espPtrStrings;
	std::vector<ConstantString*> eipPtrStrings;

	std::vector<LocalizedLabel*> eaxPtrLabels;
	std::vector<LocalizedLabel*> ebxPtrLabels;
	std::vector<LocalizedLabel*> ecxPtrLabels;
	std::vector<LocalizedLabel*> edxPtrLabels;
	std::vector<LocalizedLabel*> ediPtrLabels;
	std::vector<LocalizedLabel*> esiPtrLabels;
	std::vector<LocalizedLabel*> ebpPtrLabels;
	std::vector<LocalizedLabel*> espPtrLabels;
	std::vector<LocalizedLabel*> eipPtrLabels;

	ConstantString* eaxString;
	ConstantString* ebxString;
	ConstantString* ecxString;
	ConstantString* edxString;
	ConstantString* ediString;
	ConstantString* esiString;
	ConstantString* ebpString;
	ConstantString* espString;
	ConstantString* eipString;

	Register eax;
	Register ebx;
	Register ecx;
	Register edx;
	Register edi;
	Register esi;
	Register ebp;
	Register esp;
	Register eip;

	static const float RegisterPtrSpacing;
	static const cocos2d::Vec2 SelectorRegOffset;
};
