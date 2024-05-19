


#include "pch.h"
#include <cmath>
#include <random>
#include <memory>
#include "Timbre.h"



CTimbre::~CTimbre()
{
}



CTimbre::CTimbre(int SampleRate)
:m_bPlay(false)
,m_bKeyOn(true)
,output_rate(SampleRate)
,output_step(0x100000000ull / output_rate)
,output_pos(0)
,m_pYM3526(std::make_unique<FmChip<ymfm::ym3526>>(output_rate * 72, EChipType::YM3526))
,m_pYM2413(std::make_unique<FmChip<ymfm::ym2413>>(output_rate * 72, EChipType::YM2413))
{
OutputDebugStringA(std::to_string(output_rate).c_str());
OutputDebugStringA(".");
OutputDebugStringA(std::to_string(output_rate * 72).c_str());
OutputDebugStringA("\n");
	{	// 
		Control.CON.SetValue(0);
		Control.FB.SetValue(0);
		Control.NUM.SetValue(0);
		Control.KML.SetValue(0);
		Control.KMH.SetValue(128);
		Control.EN.SetValue(1);
		Control.FDE.SetValue(1);
		Control.OPLL.SetValue(1);
		Control.VOL.SetValue(0);
		
		for (int i = 0; i < 2; ++i){
			aOperator[i].AR.SetValue(31);
			aOperator[i].DR.SetValue(0);
			aOperator[i].SL.SetValue(0);
			aOperator[i].RR.SetValue(0);
			aOperator[i].KSL.SetValue(0);
			aOperator[i].MT.SetValue(1);
			aOperator[i].AM.SetValue(0);
			aOperator[i].VIB.SetValue(0);
			aOperator[i].EGT.SetValue(0);
			aOperator[i].KSR.SetValue(0);
			aOperator[i].WF.SetValue(0);
		}
		aOperator[0].TL.SetValue(24);
		aOperator[1].TL.SetValue(0);
	}
}



IValue& CTimbre::GetValue(int x, int y)
{
	switch (y){
		case 0:{
			switch (x){
				case 0: return Control.CON;
				case 1: return Control.FB;
				case 2: return Control.NUM;
				case 3: return Control.KML;
				case 4: return Control.KMH;
				case 5: return Control.EN;
				case 6: return Control.FDE;
				case 7: return Control.SEL;
				case 8: return Control.AMD;
				case 9: return Control.PMD;
				case 10: return Control.KT;
				case 11: return Control.FDT;
				case 12: return Control.OPLL;
				case 13: return Control.INST;
				case 14: return Control.VOL;
				case 15: return Control.SUS;
			}
			break;
		}
		default:{
			switch (x){
				case 0: return aOperator[y-1].AR;
				case 1: return aOperator[y-1].DR;
				case 2: return aOperator[y-1].SL;
				case 3: return aOperator[y-1].RR;
				case 4: return aOperator[y-1].KSL;
				case 5: return aOperator[y-1].TL;
				case 6: return aOperator[y-1].MT;
				case 7: return aOperator[y-1].AM;
				case 8: return aOperator[y-1].VIB;
				case 9: return aOperator[y-1].EGT;
				case 10: return aOperator[y-1].KSR;
				case 11: break;
				case 12: return aOperator[y-1].WF;
				case 13: break;
				case 14: break;
				case 15: break;
			}
			break;
		}
	}
	return Dummy;
}



void CTimbre::OnBufferStart(std::vector<int>& aOutput)
{
	SubmitSourceBuffer(aOutput);
	KeyOn();
}



void CTimbre::SubmitSourceBuffer(std::vector<int>& aOutput)
{
	for (auto& i : aOutput){
		int32_t outputs[1] = {0};
//		m_pYM3526->generate(output_pos, output_step, outputs);
		m_pYM2413->generate(output_pos, output_step, outputs);
		i += outputs[0];
		
		output_pos += output_step;
	}
}



static const int16_t s_aBlockFNumberYM3526[]={
//	c       c+      d       d+      e       f       f+      g       g+      a       a+      b
	0x009a, 0x00a3, 0x00ad, 0x00b7, 0x00c2, 0x00ce, 0x00da, 0x00e7, 0x00f5, 0x0104, 0x0113, 0x0123,	// o-1
	0x0135, 0x0147, 0x015b, 0x016f, 0x0185, 0x019c, 0x01b5, 0x01cf, 0x01ea, 0x0208, 0x0227, 0x0247,	// o0
	0x026a, 0x028f, 0x02b6, 0x02df, 0x030b, 0x0339, 0x036a, 0x039e, 0x03d5, 0x0410, 0x044e, 0x048f,	// o1
	0x0a6a, 0x0a8f, 0x0ab6, 0x0adf, 0x0b0b, 0x0b39, 0x0b6a, 0x0b9e, 0x0bd5, 0x0c10, 0x0c4e, 0x0c8f,	// o2
	0x126a, 0x128f, 0x12b6, 0x12df, 0x130b, 0x1339, 0x136a, 0x139e, 0x13d5, 0x1410, 0x144e, 0x148f,	// o3
	0x1a6a, 0x1a8f, 0x1ab6, 0x1adf, 0x1b0b, 0x1b39, 0x1b6a, 0x1b9e, 0x1bd5, 0x1c10, 0x1c4e, 0x1c8f,	// o4
	0x226a, 0x228f, 0x22b6, 0x22df, 0x230b, 0x2339, 0x236a, 0x239e, 0x23d5, 0x2410, 0x244e, 0x248f,	// o5
	0x2a6a, 0x2a8f, 0x2ab6, 0x2adf, 0x2b0b, 0x2b39, 0x2b6a, 0x2b9e, 0x2bd5, 0x2c10, 0x2c4e, 0x2c8f,	// o6
	0x326a, 0x328f, 0x32b6, 0x32df, 0x330b, 0x3339, 0x336a, 0x339e, 0x33d5, 0x3410, 0x344e, 0x348f,	// o7
	0x3a6a, 0x3a8f, 0x3ab6, 0x3adf, 0x3b0b, 0x3b39, 0x3b6a, 0x3b9e, 0x3bd5, 0x3c10, 0x3c4e, 0x3c8f,	// o8
	0x3cd4, 0x3d1e, 0x3d6c, 0x3dbe, 0x3e16, 0x3e72, 0x3ed4, 0x3f3c, 0x3faa, 0x0000, 0x0000, 0x0000,	// o9
};

static const int16_t s_aBlockFNumberYM2413[]={
//	c       c+      d       d+      e       f       f+      g       g+      a       a+      b
	0x0055, 0x005a, 0x0060, 0x0066, 0x006c, 0x0072, 0x0079, 0x0080, 0x0088, 0x0090, 0x0098, 0x00a1,	// o0
	0x00ab, 0x00b5, 0x00c0, 0x00cc, 0x00d8, 0x00e5, 0x00f2, 0x0101, 0x0110, 0x0120, 0x0131, 0x0143,	// o1
	0x02ab, 0x02b5, 0x02c0, 0x02cc, 0x02d8, 0x02e5, 0x02f2, 0x0301, 0x0310, 0x0320, 0x0331, 0x0343,	// o2
	0x04ab, 0x04b5, 0x04c0, 0x04cc, 0x04d8, 0x04e5, 0x04f2, 0x0501, 0x0510, 0x0520, 0x0531, 0x0543,	// o3
	0x06ab, 0x06b5, 0x06c0, 0x06cc, 0x06d8, 0x06e5, 0x06f2, 0x0701, 0x0710, 0x0720, 0x0731, 0x0743,	// o4
	0x08ab, 0x08b5, 0x08c0, 0x08cc, 0x08d8, 0x08e5, 0x08f2, 0x0901, 0x0910, 0x0920, 0x0931, 0x0943,	// o5
	0x0aab, 0x0ab5, 0x0ac0, 0x0acc, 0x0ad8, 0x0ae5, 0x0af2, 0x0b01, 0x0b10, 0x0b20, 0x0b31, 0x0b43,	// o6
	0x0cab, 0x0cb5, 0x0cc0, 0x0ccc, 0x0cd8, 0x0ce5, 0x0cf2, 0x0d01, 0x0d10, 0x0d20, 0x0d31, 0x0d43,	// o7
	0x0eab, 0x0eb5, 0x0ec0, 0x0ecc, 0x0ed8, 0x0ee5, 0x0ef2, 0x0f01, 0x0f10, 0x0f20, 0x0f31, 0x0f43,	// o8
	0x0f57, 0x0f6b, 0x0f81, 0x0f98, 0x0fb0, 0x0fca, 0x0fe5, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,	// o9
};

void CTimbre::BlockFNumber(int Note)
{
	Note += Control.KT.GetValue();
	Note = (Note >= 0)? Note: 0;
	Note = (int)((Note < std::size(s_aBlockFNumberYM2413))? Note: std::size(s_aBlockFNumberYM2413)-1);
	
	auto BlockFNumber = s_aBlockFNumberYM2413[Note];
	BlockFNumber += Control.FDT.GetValue();
	BlockFNumber = (BlockFNumber >= 0)? BlockFNumber: 0;
	BlockFNumber = (BlockFNumber <= 0x0fff)? BlockFNumber: 0x0fff;
	
	m_BlockFNumberYM2413 = BlockFNumber;
	
//	m_pYM3526->write(RegH, BlockFNumber>>8);
//	m_pYM3526->write(RegL, BlockFNumber&0xff);
}



void CTimbre::KeyOn()
{
	if (m_bPlay && !m_bKeyOn){
		m_bKeyOn = true;
		m_pYM2413->write(0x00, ((aOperator[0].AM.GetValue()<<7) | (aOperator[0].VIB.GetValue()<<6) | (aOperator[0].EGT.GetValue()<<5) | (aOperator[0].KSR.GetValue()<<4) | aOperator[0].MT.GetValue()));
		m_pYM2413->write(0x01, ((aOperator[1].AM.GetValue()<<7) | (aOperator[1].VIB.GetValue()<<6) | (aOperator[1].EGT.GetValue()<<5) | (aOperator[1].KSR.GetValue()<<4) | aOperator[1].MT.GetValue()));
		m_pYM2413->write(0x02, ((aOperator[0].KSL.GetValue()<<6) | aOperator[0].TL.GetValue()));
		m_pYM2413->write(0x03, ((aOperator[1].KSL.GetValue()<<6) | (aOperator[1].WF.GetValue()<<4) | (aOperator[1].WF.GetValue()<<3) | Control.FB.GetValue()));
		m_pYM2413->write(0x04, ((aOperator[0].AR.GetValue()<<4) | aOperator[0].DR.GetValue()));
		m_pYM2413->write(0x05, ((aOperator[1].AR.GetValue()<<4) | aOperator[1].DR.GetValue()));
		m_pYM2413->write(0x06, ((aOperator[0].SL.GetValue()<<4) | aOperator[0].RR.GetValue()));
		m_pYM2413->write(0x07, ((aOperator[1].SL.GetValue()<<4) | aOperator[1].RR.GetValue()));
		
		{	// 
			BlockFNumber(m_Note);
		}
		
		if (m_Note >= Control.KML.GetValue() && m_Note <= Control.KMH.GetValue()){
			m_pYM2413->write(0x30, ((Control.INST.GetValue()<<4) | Control.VOL.GetValue()));
			m_pYM2413->write(0x10, (m_BlockFNumberYM2413&0xff));
			m_pYM2413->write(0x20, ((Control.SUS.GetValue()<<5) | (Control.EN.GetValue()<<4) | (m_BlockFNumberYM2413>>8)));
		}
	}
}



void CTimbre::Play(int Note)
{
	if (!m_bPlay){
		m_Note = Note;
		
		m_bPlay = true;
		m_bKeyOn = false;
		m_ppFmChip = (Control.OPLL.GetValue() != 0)? &m_pYM2413: &m_pYM3526;
		
		switch (Control.OPLL.GetValue()){
			case 0:{
				m_bFDE = Control.FDE.GetValue();
//				if (m_bFDE) m_pYM3526->write(0x20, ((aOperator[0].SL.GetValue()<<4) | /*RR*/15));
				break;
			}
			case 1:{
				break;
			}
		}
	}
}
void CTimbre::Stop()
{
	if (m_bPlay){
		m_bPlay = false;
//		m_pYM3526->write(0x28, 0x02);
		m_pYM2413->write(0x20, (Control.SUS.GetValue()<<5) | /*KeyOff*/0x00 | (m_BlockFNumberYM2413>>8));
	}
}



void CTimbre::SetIntermediate(CIntermediate v)
{
	Control.CON.SetValue(v.Control.CON);
	Control.FB.SetValue(v.Control.FB);
	Control.NUM.SetValue(v.Control.NUM);
	Control.KML.SetValue(v.Control.KML);
	Control.KMH.SetValue(v.Control.KMH);
	Control.EN.SetValue(v.Control.EN);
	Control.FDE.SetValue(v.Control.FDE);
	Control.SEL.SetValue(v.Control.SEL);
	Control.AMD.SetValue(v.Control.AMD);
	Control.PMD.SetValue(v.Control.PMD);
	Control.KT.SetValue(v.Control.KT);
	Control.FDT.SetValue(v.Control.FDT);
	Control.OPLL.SetValue(v.Control.OPLL);
	Control.INST.SetValue(v.Control.INST);
	Control.VOL.SetValue(v.Control.VOL);
	Control.SUS.SetValue(v.Control.SUS);
	
	for (int i = 0; i < 2; ++i){
		aOperator[i].AR.SetValue(v.aOperator[i].AR);
		aOperator[i].DR.SetValue(v.aOperator[i].DR);
		aOperator[i].SL.SetValue(v.aOperator[i].SL);
		aOperator[i].RR.SetValue(v.aOperator[i].RR);
		aOperator[i].KSL.SetValue(v.aOperator[i].KSL);
		aOperator[i].TL.SetValue(v.aOperator[i].TL);
		aOperator[i].MT.SetValue(v.aOperator[i].MT);
		aOperator[i].AM.SetValue(v.aOperator[i].AM);
		aOperator[i].VIB.SetValue(v.aOperator[i].VIB);
		aOperator[i].EGT.SetValue(v.aOperator[i].EGT);
		aOperator[i].KSR.SetValue(v.aOperator[i].KSR);
		aOperator[i].WF.SetValue(v.aOperator[i].WF);
	}
}



CIntermediate CTimbre::GetIntermediate()
{
	CIntermediate v;
	
	v.Control.CON = Control.CON.GetValue();
	v.Control.FB = Control.FB.GetValue();
	v.Control.NUM = Control.NUM.GetValue();
	v.Control.KML = Control.KML.GetValue();
	v.Control.KMH = Control.KMH.GetValue();
	v.Control.EN = Control.EN.GetValue();
	v.Control.FDE = Control.FDE.GetValue();
	v.Control.SEL = Control.SEL.GetValue();
	v.Control.AMD = Control.AMD.GetValue();
	v.Control.PMD = Control.PMD.GetValue();
	v.Control.KT = Control.KT.GetValue();
	v.Control.FDT = Control.FDT.GetValue();
	v.Control.OPLL = Control.OPLL.GetValue();
	v.Control.INST = Control.INST.GetValue();
	v.Control.VOL = Control.VOL.GetValue();
	v.Control.SUS = Control.SUS.GetValue();
	
	for (int i = 0; i < 2; ++i){
		v.aOperator[i].AR = aOperator[i].AR.GetValue();
		v.aOperator[i].DR = aOperator[i].DR.GetValue();
		v.aOperator[i].SL = aOperator[i].SL.GetValue();
		v.aOperator[i].RR = aOperator[i].RR.GetValue();
		v.aOperator[i].KSL = aOperator[i].KSL.GetValue();
		v.aOperator[i].TL = aOperator[i].TL.GetValue();
		v.aOperator[i].MT = aOperator[i].MT.GetValue();
		v.aOperator[i].AM = aOperator[i].AM.GetValue();
		v.aOperator[i].VIB = aOperator[i].VIB.GetValue();
		v.aOperator[i].EGT = aOperator[i].EGT.GetValue();
		v.aOperator[i].KSR = aOperator[i].KSR.GetValue();
		v.aOperator[i].WF = aOperator[i].WF.GetValue();
	}
	
	return std::move(v);
}
