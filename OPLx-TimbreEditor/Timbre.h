#pragma once



#include "FmChip.h"
#include "Value.h"
#include "Intermediate.h"



class CTimbre
{
	public:
		virtual ~CTimbre();
		
		CTimbre(int SampleRate);
		
		IValue& GetValue(int x, int y);
	
	private:
		CDummy Dummy;
		
		struct Control
		{
			CValue<1, 0, 1> CON;
			CValue<1, 0, 7> FB;
			CValue<3, 0, 127> NUM;
			CValue<3, 0, 128> KML;
			CValue<3, 0, 128> KMH;
			CValue<1, 0, 1> EN;
			CValue<1, 0, 1> FDE;
			CValue<1, 0, 1> SEL;
			CValue<1, 0, 3> AMD;
			CValue<1, 0, 3> PMD;
			CValue<4, -114, 114> KT;
			CValue<4, -999, 999> FDT;
			
			CValue<1, 0, 1> OPLL;
			CValue<2, 0, 15> INST;
			CValue<2, 0, 15> VOL;
			CValue<1, 0, 1> SUS;
		};
		Control Control;
		
		struct Operator
		{
			CValue<2, 0, 15> AR;
			CValue<2, 0, 15> DR;
			CValue<2, 0, 15> SL;
			CValue<2, 0, 15> RR;
			CValue<1, 0, 3> KSL;
			CValue<2, 0, 63> TL;
			CValue<2, 0, 15> MT;
			CValue<1, 0, 1> AM;
			CValue<1, 0, 1> VIB;
			CValue<1, 0, 1> EGT;
			CValue<1, 0, 1> KSR;
			
			CValue<1, 0, 1> WF;
		};
		Operator aOperator[2];
		
		int m_Note;
		bool m_bPlay;
		bool m_bKeyOn;
		bool m_bFDE;
		
		int16_t m_BlockFNumberYM2413;
		
		uint32_t output_rate;
		emulated_time output_step;
		emulated_time output_pos;
		std::unique_ptr<FmChipBase> m_pYM3526;
		std::unique_ptr<FmChipBase> m_pYM2413;
		std::unique_ptr<FmChipBase>* m_ppFmChip;
	
	private:
		void SubmitSourceBuffer(std::vector<int>& aOutput);
		
		void BlockFNumber(int Note);
		void KeyOn();
	
	public:
		void Play(int Note);
		void Stop();
		
		void OnBufferStart(std::vector<int>& aOutput);
		
		void SetIntermediate(CIntermediate v);
		CIntermediate GetIntermediate();
};
