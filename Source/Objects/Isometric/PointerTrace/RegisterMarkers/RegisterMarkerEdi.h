#pragma once

#include "Objects/Isometric/PointerTrace/RegisterMarkers/RegisterMarker.h"

class RegisterMarkerEdi : public RegisterMarker
{
public:
	static RegisterMarkerEdi* create();

protected:
	RegisterMarkerEdi();
	virtual ~RegisterMarkerEdi();

	int getRegisterIndex() override;

private:
	typedef RegisterMarker super;
};
