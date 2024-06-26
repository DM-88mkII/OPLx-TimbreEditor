﻿#pragma once



#include "SettingTab.h"



struct CIntermediate
{
	public:
		virtual ~CIntermediate() = default;
		
		CIntermediate();
	
	public:
		struct Control
		{
			int CON;
			int FB;
			int NUM;
			int KML;
			int KMH;
			int EN;
			int FDE;
			int SEL;
			int AMD;
			int VBD;
			int KT;
			int FDT;
			
			int OPLL;
			int INST;
			int VOL;
			int SUS;
		};
		Control Control;
		
		struct Operator
		{
			int AR;
			int DR;
			int SL;
			int RR;
			int KSL;
			int TL;
			int MT;
			int AM;
			int VIB;
			int EGT;
			int KSR;
			
			int WF;
		};
		Operator aOperator[2];
	
	public:
		void to_json(nlohmann::json& j) const;
		void from_json(const nlohmann::json& j);
		
		void ToFormat(CSettingTab::EFormatType EFormatType, CString& Text);
		void FromFormat(CSettingTab::EFormatType EFormatType, const CString& Text);
	
	private:
		void Replace(std::string& source, const std::string& target, const std::string& replace);
		std::vector<std::string> GetLines(const CString& Text);
		std::vector<std::string> GetToken(const std::string& Line, char delim);
		std::string CommentCut(const std::string& Line, const std::string& target);
		std::string Trim(const std::string& Token, const std::string& trim);
		int ToValue(const std::string& Token);
		int ToValueHex(const std::string& Token);
		
		void GetOperator2413(const std::vector<std::string>& Tokens, int iOperator);
		
		void ToMgsDrv(CString& Text);
		void FromMgsDrv(const CString& Text);
		
		void ToMml2VgmLL(CString& Text);
		void FromMml2VgmLL(const CString& Text);
		
		void ToPmdOPL(CString& Text);
		void FromPmdOPL(const CString& Text);
		
		void ToFamiTracker(CString& Text);
		void FromFamiTracker(const CString& Text);
		
		void ToMsxBasic(CString& Text);
		void FromMsxBasic(const CString& Text);
};



void to_json(nlohmann::json& j, const CIntermediate& r);
void from_json(const nlohmann::json& j, CIntermediate& r);
