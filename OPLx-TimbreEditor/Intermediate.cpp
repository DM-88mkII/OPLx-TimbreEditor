


#include "pch.h"
#include "Intermediate.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <string>



CIntermediate::CIntermediate()
:Control{0}
,aOperator{0}
{
	Control.KML = 0;
	Control.KMH = 128;
	Control.EN = 1;
	Control.FDE = 1;
}



void CIntermediate::to_json(nlohmann::json& j) const
{
	j = nlohmann::json{
		{"Information",{
			{"Summary",		"Timbre for OPL Series",	},
			{"ChipType",	"OPLx",	},
		}},
		{"Meta",{
			{"Application",	"OPLx-TimbreEditor",	},
			{"Version",		"0.0.0",	},
		}},
		{"Timbre",{
			{"Control",{
				{"CON",		Control.CON,},
				{"FB",		Control.FB,	},
				{"NUM",		Control.NUM,},
				{"KML",		Control.KML,},
				{"KMH",		Control.KMH,},
				{"EN",		Control.EN,},
				{"FDE",		Control.FDE,},
				{"SEL",		Control.SEL,},
				{"AMD",		Control.AMD,},
				{"PMD",		Control.PMD,},
				{"KT",		Control.KT,},
				{"FDT",		Control.FDT,},
				{"OPLL",	Control.OPLL,},
				{"INST",	Control.INST,},
				{"VOL",		Control.VOL,},
				{"SUS",		Control.SUS,},
			}},
			{"Operators",{
				{"AR",{		aOperator[0].AR,	aOperator[1].AR,	}},
				{"DR",{		aOperator[0].DR,	aOperator[1].DR,	}},
				{"SL",{		aOperator[0].SL,	aOperator[1].SL,	}},
				{"RR",{		aOperator[0].RR,	aOperator[1].RR,	}},
				{"KSL",{	aOperator[0].KSL,	aOperator[1].KSL,	}},
				{"TL",{		aOperator[0].TL,	aOperator[1].TL,	}},
				{"MT",{		aOperator[0].MT,	aOperator[1].MT,	}},
				{"AM",{		aOperator[0].AM,	aOperator[1].AM,	}},
				{"VIB",{	aOperator[0].VIB,	aOperator[1].VIB,	}},
				{"EGT",{	aOperator[0].EGT,	aOperator[1].EGT,	}},
				{"KSR",{	aOperator[0].KSR,	aOperator[1].KSR,	}},
				{"WF",{		aOperator[0].WF,	aOperator[1].WF,	}},
			}},
		}},
	};
}



void CIntermediate::from_json(const nlohmann::json& j)
{
	std::exception_ptr pException;
	try {
		{	// 
			auto Information = j.at("Information");
			auto Application = Information.at("Summary").get<std::string>();
			auto ChipType = Information.at("ChipType").get<std::string>();
		}
		
		{	// 
			auto Meta = j.at("Meta");
			auto Application = Meta.at("Application").get<std::string>();
			auto Version = Meta.at("Version").get<std::string>();
		}
		
		{	// 
			auto Timbre = j.at("Timbre");
			
			{	// 
				auto o = Timbre.at("Control");
				Control.CON = o.at("CON").get<int>();
				Control.FB = o.at("FB").get<int>();
				Control.NUM = o.at("NUM").get<int>();
				Control.KML = o.at("KML").get<int>();
				Control.KMH = o.at("KMH").get<int>();
				Control.EN = o.at("EN").get<int>();
				Control.FDE = o.at("FDE").get<int>();
				Control.SEL = o.at("SEL").get<int>();
				Control.AMD = o.at("AMD").get<int>();
				Control.PMD = o.at("PMD").get<int>();
				Control.KT = o.at("KT").get<int>();
				Control.FDT = o.at("FDT").get<int>();
				Control.OPLL = o.at("OPLL").get<int>();
				Control.INST = o.at("INST").get<int>();
				Control.VOL = o.at("VOL").get<int>();
				Control.SUS = o.at("SUS").get<int>();
			}
			
			{	// 
				auto SetOperator = [this](nlohmann::json& Timbre, int i)
				{
					aOperator[i].AR = Timbre.at("AR").at(i).get<int>();
					aOperator[i].DR = Timbre.at("DR").at(i).get<int>();
					aOperator[i].SL = Timbre.at("SL").at(i).get<int>();
					aOperator[i].RR = Timbre.at("RR").at(i).get<int>();
					aOperator[i].KSL = Timbre.at("KSL").at(i).get<int>();
					aOperator[i].TL = Timbre.at("TL").at(i).get<int>();
					aOperator[i].MT = Timbre.at("MT").at(i).get<int>();
					aOperator[i].AM = Timbre.at("AM").at(i).get<int>();
					aOperator[i].VIB = Timbre.at("VIB").at(i).get<int>();
					aOperator[i].EGT = Timbre.at("EGT").at(i).get<int>();
					aOperator[i].KSR = Timbre.at("KSR").at(i).get<int>();
					aOperator[i].WF = Timbre.at("WF").at(i).get<int>();
				};
				
				auto o = Timbre.at("Operators");
				for (int i = 0; i < 2; ++i) SetOperator(o, i);
			}
		}
	}
	catch (...)
	{
		pException = std::current_exception();
	}
	if (pException){
		std::rethrow_exception(pException);
	}
}



void CIntermediate::ToFormat(CSettingTab::EFormatType EFormatType, CString& Text)
{
	switch (EFormatType){
		case CSettingTab::EFormatType::MGSDRV:{		ToMgsDrv(Text);		break;	}
	}
}



void CIntermediate::FromFormat(CSettingTab::EFormatType EFormatType, const CString& Text)
{
	switch (EFormatType){
		case CSettingTab::EFormatType::MGSDRV:{		FromMgsDrv(Text);		break;	}
	}
}



void CIntermediate::Replace(std::string& source, const std::string& target, const std::string& replace)
{
	size_t p = 0;
	size_t o = 0;
	size_t n = target.length();
	int c = 0;
	while ((p = source.find(target, o)) != std::string::npos){
		source.replace(p, n, replace);
		o = p + replace.length();
		++c;
	}
	if (c > 0) Replace(source, target, replace);
}


std::vector<std::string> CIntermediate::GetLines(const CString& Text)
{
	std::string s = CStringA(Text).GetBuffer();
	Replace(s, "\r\n", "\n");
	Replace(s, "\n\n", "\n");
	
	std::stringstream ss(s);
	std::string Line;
	std::vector<std::string> Lines;
	while (std::getline(ss, Line, '\n')) Lines.push_back(Line);
	return Lines;
}



std::vector<std::string> CIntermediate::GetToken(const std::string& Line, char delim)
{
	std::stringstream ss(Line);
	std::string Token;
	std::vector<std::string> Tokens;
	while (std::getline(ss, Token, delim)) Tokens.push_back(Token);
	return Tokens;
}



std::string CIntermediate::Trim(const std::string& Token, const std::string& trim)
{
	std::string Result;
	auto First = Token.find_first_not_of(trim);
	if (First != std::string::npos){
		auto Last = Token.find_last_not_of(trim);
		Result = Token.substr(First, Last - First + 1);
	}
	return Result;
}



int CIntermediate::ToValue(const std::string& Token)
{
	auto Value = Trim(Token, " ");
	return (Value.empty())? 0: std::stoi(Value);
}



void CIntermediate::GetOperator2413(const std::vector<std::string>& Tokens, int iOperator)
{
	int TimbreToken = 0;
	for (auto Token : Tokens){
		switch (TimbreToken){
			case 0:{	aOperator[iOperator].AR = ToValue(Token);	break;	}
			case 1:{	aOperator[iOperator].DR = ToValue(Token);	break;	}
			case 2:{	aOperator[iOperator].SL = ToValue(Token);	break;	}
			case 3:{	aOperator[iOperator].RR = ToValue(Token);	break;	}
			case 4:{	aOperator[iOperator].KSL = ToValue(Token);	break;	}
			case 5:{	aOperator[iOperator].MT = ToValue(Token);	break;	}
			case 6:{	aOperator[iOperator].AM = ToValue(Token);	break;	}
			case 7:{	aOperator[iOperator].VIB = ToValue(Token);	break;	}
			case 8:{	aOperator[iOperator].EGT = ToValue(Token);	break;	}
			case 9:{	aOperator[iOperator].KSR = ToValue(Token);	break;	}
			case 10:{	aOperator[iOperator].WF = ToValue(Token);	break;	}
		}
		++TimbreToken;
	}
}



void CIntermediate::ToMgsDrv(CString& Text)
{
	std::string s;
	s += std::format("@v{} = ", Control.NUM);
	s += "{";
	s += std::format("{:>2},{:>2},\n      ", aOperator[0].TL, Control.FB);
	for (int i = 0; i < 2; ++i){
		s += std::format(" {:>2}", aOperator[i].AR);
		s += std::format(",{:>2}", aOperator[i].DR);
		s += std::format(",{:>2}", aOperator[i].SL);
		s += std::format(",{:>2}", aOperator[i].RR);
		s += std::format(",{:>2}", aOperator[i].KSL);
		s += std::format(",{:>2}", aOperator[i].MT);
		s += std::format(",{:>2}", aOperator[i].AM);
		s += std::format(",{:>2}", aOperator[i].VIB);
		s += std::format(",{:>2}", aOperator[i].EGT);
		s += std::format(",{:>2}", aOperator[i].KSR);
		s += std::format(",{:>2}", aOperator[i].WF);
		s += (i < 1)? ",\n      ": " }\n";
	}
	Text = s.c_str();
}



void CIntermediate::FromMgsDrv(const CString& Text)
{
	auto IsTimbre = false;
	int TimbreLine = 0;
	int iOperator = 0;
	
	auto Lines = GetLines(Text);
	for (auto& Line : Lines){
		auto o = Line.find_first_not_of(" \t");
		if (Line.size() > 0 && o != std::string::npos && Line[o] == ';') continue;
		
		if (!IsTimbre){
			auto m1 = Line.find("@v");
			auto m2 = Line.find("=");
			if (m1 == 0 && m2 != std::string::npos && m1 < m2){
				IsTimbre = true;
				
				Replace(Line, "@v", "");
				Replace(Line, "=", ",");
				Replace(Line, "{", " ");
				
				auto Tokens = GetToken(Line, ',');
				int TimbreToken = 0;
				for (auto Token : Tokens){
					switch (TimbreToken){
						case 0:{	Control.NUM = ToValue(Token);		break;	}
						case 1:{	aOperator[0].TL = ToValue(Token);	break;	}
						case 2:{	Control.FB = ToValue(Token);		break;	}
					}
					++TimbreToken;
				}
			}
		} else {
			Replace(Line, "\t", " ");
			Replace(Line, "  ", " ");
			
			auto Tokens = GetToken(Line, ',');
			switch (TimbreLine){
				case 0:
				case 1:
				{
					GetOperator2413(Tokens, iOperator);
					++iOperator;
					break;
				}
			}
			++TimbreLine;
		}
	}
	if (!(IsTimbre && iOperator == 2)){
		throw std::runtime_error("Format Error");
	}
	Control.OPLL = 1;
}



void to_json(nlohmann::json& j, const CIntermediate& r){ r.to_json(j); }
void from_json(const nlohmann::json& j, CIntermediate& r){ r.from_json(j); }
