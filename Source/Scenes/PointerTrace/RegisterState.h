#pragma once

class RegisterState
{
public:
	static int getRegisterEax();
	static void setRegisterEax(int value);
	static int getRegisterEbx();
	static void setRegisterEbx(int value);
	static int getRegisterEcx();
	static void setRegisterEcx(int value);
	static int getRegisterEdx();
	static void setRegisterEdx(int value);
	static int getRegisterEdi();
	static void setRegisterEdi(int value);
	static int getRegisterEsi();
	static void setRegisterEsi(int value);
	static int getRegisterEbp();
	static void setRegisterEbp(int value);
	static int getRegisterEsp();
	static void setRegisterEsp(int value);
	static int getRegisterEip();
	static void setRegisterEip(int value);

private:
	static int registerEax;
	static int registerEbx;
	static int registerEcx;
	static int registerEdx;
	static int registerEdi;
	static int registerEsi;
	static int registerEbp;
	static int registerEsp;
	static int registerEip;
};
