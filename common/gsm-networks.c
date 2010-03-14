/*

  G N O K I I

  A Linux/Unix toolset and driver for Nokia mobile phones.

  Released under the terms of the GNU GPL, see file COPYING for more details.
	
  This file implements GSM networks searching.

*/

#include <string.h>

#include "gsm-common.h"
#include "gsm-networks.h"
#include "gsm-coding.h"

GSM_Country GSM_Countries[] =
{
  { "202", "Greece" },
  { "204", "Netherlands" },
  { "206", "Belgium" },
  { "208", "France" },
  { "213", "Andorra" },
  { "214", "Spain" },
  { "216", "Hungary" },
  { "218", "Bosnia Herzegovina" },
  { "219", "Croatia" },
  { "220", "Yugoslavia" },
  { "222", "Italy" },
  { "226", "Romania" },
  { "228", "Switzerland" },
  { "230", "Czech Republic" },
  { "231", "Slovak Republic" },
  { "232", "Austria" },
  { "234", "United Kingdom" },
  { "238", "Denmark" },
  { "240", "Sweden" },
  { "242", "Norway" },
  { "244", "Finland" },
  { "246", "Lithuania" },
  { "247", "Latvia" },
  { "248", "Estonia" },
  { "250", "Russia" },
  { "255", "Ukraine" },
  { "259", "Moldova" },
  { "260", "Poland" },
  { "262", "Germany" },
  { "266", "Gibraltar" },
  { "268", "Portugal" },
  { "270", "Luxembourg" },
  { "272", "Ireland" },
  { "274", "Iceland" },
  { "276", "Albania" },
  { "278", "Malta" },
  { "280", "Cyprus" },
  { "282", "Georgia" },
  { "283", "Armenia" },
  { "284", "Bulgaria" },
  { "286", "Turkey" },
  { "290", "Greenland" },
  { "293", "Slovenia" },
  { "294", "Macedonia" },
  { "302", "Canada" },
  { "310", "Papua New Guinea" },
  { "310", "U.S.A." },
  { "340", "French West Indies" },
  { "400", "Azerbaijan" },
  { "404", "India" },
  { "410", "Pakistan" },
  { "413", "Sri Lanka" },
  { "415", "Lebanon" },
  { "416", "Jordan" },
  { "417", "Syria" },
  { "418", "Iraq" },
  { "419", "Kuwait" },
  { "420", "Saudi Arabia" },
  { "422", "Oman" },
  { "424", "United Arab Emirates" },
  { "425", "Israel" },
  { "426", "Bahrain" },
  { "427", "Qatar" },
  { "432", "Iran" },
  { "434", "Uzbekistan" },
  { "437", "Kyrgyz Republic" },
  { "452", "Vietnam" },
  { "454", "Hong Kong" },
  { "455", "Macau" },
  { "456", "Cambodia" },
  { "457", "Lao" },
  { "460", "China" },
  { "466", "Taiwan" },
  { "470", "Bangladesh" },
  { "502", "Malaysia" },
  { "505", "Australia" },
  { "510", "Indonesia" },
  { "515", "Philippines" },
  { "520", "Thailand" },
  { "525", "Singapore" },
  { "528", "Brunei Darussalam" },
  { "530", "New Zealand" },
  { "542", "Fiji" },
  { "546", "New Caledonia" },
  { "547", "French Polynesia" },
  { "602", "Egypt" },
  { "603", "Algeria" },
  { "604", "Morocco" },
  { "605", "Tunisia" },
  { "608", "Senegal" },
  { "611", "Guinea" },
  { "612", "Cote d'Ivoire" },
  { "615", "Togo" },
  { "617", "Mauritius" },
  { "618", "Liberia" },
  { "620", "Ghana" },
  { "624", "Cameroon" },
  { "625", "Cape Verde" },
  { "633", "Seychelles" },
  { "634", "Mozambique" },
  { "634", "Sudan" },
  { "635", "Rwanda" },
  { "636", "Ethiopia" },
  { "640", "Tanzania" },
  { "641", "Uganda" },
  { "645", "Zambia" },
  { "646", "Madagascar" },
  { "647", "Reunion" },
  { "648", "Zimbabwe" },
  { "649", "Namibia" },
  { "650", "Malawi" },
  { "651", "Lesotho" },
  { "652", "Botswana" },
  { "655", "South Africa" },
  { "730", "Chile" },
  { "734", "Venezuela" },

  { "undefined", "unknown" }
};

GSM_Network GSM_Networks[] =
{
  { "202 01", "Cosmote" },
  { "202 05", "PANAFON" },
  { "202 10", "TELESTET" },
  { "204 04", "LIBERTEL" },
  { "204 08", "KPN Telecom" },
  { "204 12", "Telfort" },
  { "204 16", "BEN" },
  { "204 20", "Dutchtone NV" },
  { "206 01", "PROXIMUS" },
  { "206 10", "Mobistar" },
  { "208 01", "ITINERIS" },
  { "208 10", "SFR" },
  { "208 20", "Bouygues Telecom" },
  { "213 03", "MOBILAND" },
  { "214 01", "Airtel GSM 900-Spain" },
  { "214 03", "Retevision Movil" },
  { "214 07", "MOVISTAR" },
  { "216 01", "Pannon GSM" },
  { "216 70", "Vodafone" },
  { "216 30", "Westel 900" },
  { "218 90", "GSMBIH" },
  { "219 01", "CRONET" },
  { "219 10", "VIP" },
  { "220 01", "MOBTEL" },
  { "220 02", "ProMonte GSM" },
  { "222 01", "Telecom Italia Mobile" },
  { "222 10", "OMNITEL" },
  { "222 88", "Wind Telecomunicazioni SpA" },
  { "226 01", "CONNEX GSM" },
  { "226 10", "DIALOG" },
  { "228 01", "NATEL International" },
  { "228 02", "diAx Mobile AG" },
  { "230 01", "Paegas" },
  { "230 02", "EuroTel" },
  { "230 03", "Oskar" },
  { "231 01", "Globtel" },
  { "231 02", "EuroTel GSM" },
  { "232 01", "A1" },
  { "232 03", "max.mobil." },
  { "232 05", "ONE" },
  { "232 07", "tele.ring" },
  { "234 10", "Cellnet" },
  { "234 15", "Vodafone" },
  { "234 30", "One 2 One" },
  { "234 33", "ORANGE" },
  { "234 50", "Jersey Telecoms GSM" },
  { "234 55", "Guernsey Telecoms GSM" },
  { "234 58", "PRONTO GSM" },
  { "238 01", "TDK-MOBIL" },
  { "238 02", "SONOFON" },
  { "238 20", "TELIA DK" },
  { "238 30", "Mobilix" },
  { "240 01", "Telia AB" },
  { "240 07", "COMVIQ" },
  { "240 08", "EUROPOLITAN" },
  { "242 01", "Telenor Mobil" },
  { "242 02", "NetCom GSM" },
  { "244 03", "Telia City (Finland)" },
  { "244 05", "Radiolinja" },
  { "244 09", "Finnet" },
  { "244 91", "Sonera" },
  { "246 01", "OMNITEL" },
  { "246 02", "Bite GSM" },
  { "247 01", "LMT LV" },
  { "247 02", "BALTCOM GSM" },
  { "248 01", "EMT GSM" },
  { "248 02", "Radiolinja Eesti AS" },
  { "248 03", "Q GSM" },
  { "250 01", "Mobile Telesystems" },
  { "250 02", "North-West GSM" },
  { "250 05", "Siberian Cellular Systems 900" },
  { "250 07", "BM Telecom" },
  { "250 10", "Don Telecom" },
  { "250 12", "FECS-900" },
  { "250 13", "Kuban GSM" },
  { "250 39", "Uraltel" },
  { "250 44", "North Caucasian GSM" },
  { "250 99", "BeeLine" },
  { "255 01", "UMC" },
  { "255 02", "WellCOM" },
  { "255 03", "Kyivstar" },
  { "255 05", "Golden Telecom" },
  { "259 01", "VOXTEL" },
  { "260 01", "PLUS GSM" },
  { "260 02", "ERA GSM" },
  { "260 03", "IDEA Centertel" },
  { "262 01", "D1 TELEKOM" },
  { "262 02", "D2 PRIVAT" },
  { "262 03", "E-Plus" },
  { "262 07", "Interkom" },
  { "266 01", "Gibtel GSM" },
  { "268 01", "TELECEL" },
  { "268 03", "OPTIMUS" },
  { "268 06", "TMN" },
  { "270 01", "LUXGSM" },
  { "270 77", "TANGO" },
  { "272 01", "EIRCELL-GSM" },
  { "272 02", "Digifone" },
  { "274 01", "Landssiminn GSM 900" },
  { "274 02", "TAL hf" },
  { "276 01", "AMC" },
  { "278 01", "Vodafone Malta Limited" },
  { "280 01", "CYTAGSM" },
  { "282 01", "Geocell Limited" },
  { "282 02", "Magti GSM" },
  { "283 01", "ArmGSM" },
  { "284 01", "M-TEL GSM BG" },
  { "286 01", "Turkcell" },
  { "286 02", "TELSIM GSM" },
  { "288 01", "Faroese Telecom" },
  { "290 01", "Tele Greenland" },
  { "293 40", "SI.MOBIL d. d." },
  { "293 41", "MOBITEL" },
  { "294 01", "MobiMak" },
  { "302 37", "Microcell Connexions Inc" },
  { "310 01", "Cellnet" },
  { "310 02", "Sprint Spectrum" },
  { "310 11", "Wireless 2000 Telephone Co." },
  { "310 15", "BellSouth Mobility DCS" },
  { "310 16", "Omnipoint" },
  { "310 17", "Pac Bell" },
  { "310 26", "VOICESTREAM" },
  { "310 27", "Powertel" },
  { "310 31", "AERIAL" },
  { "310 77", "Iowa Wireless Services LP" },
  { "340 01", "AMERIS" },
  { "400 01", "AZERCELL GSM" },
  { "400 02", "Bakcell GSM 2000" },

  { "404 01", "AIRCELL"},
  { "404 02", "Evergrowth"},
  { "404 03", "Bharthi Telenet"},
  { "404 05", "Fascel"},
  { "404 07", "Tata Cell"}, //TATA Cellular
  { "404 08", "Koshika"},
  { "404 09", "Reliance"},
  { "404 10", "AIRTEL"}, //AirTel
  { "404 11", "Essar"}, //Essar Cellphone
  { "404 12", "Escotel"},
  { "404 14", "Spice"}, //Modicom
  { "404 15", "AIRCELL"}, //Essar Cellphone
  { "404 18", "Reliance"},
  { "404 19", "Escotel"},
  { "404 20", "Orange"}, //Max Touch
  { "404 21", "BPL Mobile"}, //BPL - Mobile
  { "404 22", "Birla AT&T"},
  { "404 24", "Birla AT&T"},
  { "404 26", "Koshika"},
  { "404 27", "BPL Mobile"}, //BPL USWEST Cellular
  { "404 30", "Usha"}, //Command
  { "404 31", "AIRCELL"}, //?
  { "404 31", "Command"}, //?
  { "404 32", "Koshika"},
  { "404 34", "Koshika"},
  { "404 36", "Reliance"},
  { "404 40", "SkyCell"},
  { "404 41", "RPG"}, //RPG Cellular
  { "404 42", "AIRCELL"}, //AIRCEL
  { "404 43", "BPL Mobile"},
  { "404 44", "Spice"},
  { "404 45", "AIRTEL-blr"},
  { "404 46", "BPL Moibile"},
  { "404 49", "AIRTEL"},
  { "404 50", "Reliance"},
  { "404 52", "Reliance"},
  { "404 56", "Escotel"},
  { "404 60", "AIRCELL"},
  { "404 67", "Reliance"},
  { "404 70", "Hexacom"},
  { "404 78", "RPG"},
  { "404 85", "Reliance"},

  { "410 01", "Mobilink" },
  { "413 02", "DIALOG GSM" },
  { "415 01", "CELLIS" },
  { "415 03", "LIBANCELL" },
  { "416 01", "Fastlink" },
  { "417 09", "MOBILE SYRIA" },
  { "419 02", "MTCNet" },
  { "420 01", "Al Jawwal" },
  { "420 07", "E.A.E" },
  { "422 02", "GTO" },
  { "424 02", "UAE-ETISALAT" },
  { "425 01", "Partner Communications Company Ltd" },
  { "426 01", "BHR MOBILE PLUS" },
  { "427 01", "QATARNET" },
  { "432 11", "TCI" },
  { "434 04", "Daewoo Unitel" },
  { "434 05", "Coscom" },
  { "437 01", "Bitel" },
  { "454 00", "TCSL GSM" },
  { "454 04", "HKGHT" },
  { "454 06", "SMARTONE GSM" },
  { "454 10", "New World PCS" },
  { "454 12", "PEOPLES" },
  { "454 16", "SUNDAY" },
  { "455 01", "TELEMOVEL+ GSM900-Macau" },
  { "456 01", "MobiTel" },
  { "456 02", "SAMART-GSM" },
  { "457 01", "Lao Shinawatra Telecom" },
  { "460 00", "China Telecom GSM" },
  { "460 01", "CU-GSM" },
  { "466 01", "Far EasTone Telecoms 900" },
  { "466 06", "TUNTEX GSM 1800" },
  { "466 88", "KG Telecom" },
  { "466 92", "Chunghwa GSM" },
  { "466 93", "MobiTai" },
  { "466 97", "TWNGSM" },
  { "466 99", "TransAsia" },
  { "470 01", "GrameenPhone Ltd" },
  { "470 19", "Mobile 2000" },
  { "502 12", "Maxis Mobile" },
  { "502 13", "TM Touch" },
  { "502 16", "DiGi 1800" },
  { "502 17", "ADAM" },
  { "502 19", "CELCOM" },
  { "505 01", "MobileNet" },
  { "505 02", "OPTUS" },
  { "505 03", "VODAFONE" },
  { "505 08", "One.Tel" },
  { "510 01", "SATELINDO" },
  { "510 10", "TELKOMSEL" },
  { "510 11", "Excelcom" },
  { "515 01", "ISLACOM" },
  { "515 02", "Globe Telecom" },
  { "520 01", "AIS GSM" },
  { "520 10", "WCS" },
  { "520 18", "Worldphone 1800" },
  { "520 23", "HELLO" },
  { "525 01", "SingTel Mobile" },
  { "525 02", "ST-PCN" },
  { "525 03", "MOBILEONE" },
  { "528 11", "DSTCom" },
  { "530 01", "Vodafone New Zealand Limited" },
  { "542 01", "Vodafone" },
  { "546 01", "Mobilis" },
  { "547 20", "VINI" },
  { "602 01", "MobiNil" },
  { "602 02", "Tunicell" },
  { "603 01", "ALGERIAN MOBILE NETWORK" },
  { "604 01", "I A M" },
  { "608 01", "ALIZE" },
  { "611 02", "Lagui" },
  { "612 03", "IVOIRIS" },
  { "612 05", "Telecel" },
  { "615 01", "TOGO CELL" },
  { "617 01", "Cellplus Mobile Comms" },
  { "618 01", "Omega" },
  { "620 01", "SPACEFON" },
  { "625 01", "CVMOVEL" },
  { "633 01", "Seychelles Cellular Services" },
  { "633 10", "AIRTEL" },
  { "634 01", "MobiTel" },
  { "635 10", "Rwandacell" },
  { "636 01", "ETMTN" },
  { "640 01", "TRITEL" },
  { "641 10", "MTN-Uganda" },
  { "642 02", "ANTARIS" },
  { "643 01", "T.D.M GSM 900" },
  { "645 01", "ZAMCELL" },
  { "646 01", "Madacom" },
  { "646 03", "Sacel Madagascar S.A." },
  { "647 10", "SRR" },
  { "648 01", "NET*ONE" },
  { "648 03", "Telecel" },
  { "649 01", "MTC" },
  { "650 01", "Callpoint 900" },
  { "651 01", "Vodacom Lesotho (Pty) Ltd" },
  { "655 01", "Vodacom" },
  { "655 10", "MTN" },
  { "680 38", "NPI Wireless" },
  { "730 01", "Entel Telefonia Movi" },
  { "730 10", "Entel PCS" },
  { "734 01", "Infonet" },

  { "undefined", "unknown" }
};

char *GSM_GetNetworkName(char *NetworkCode)
{

  int index=0;

  while ( strcmp(GSM_Networks[index].Code, NetworkCode) &&
          strcmp(GSM_Networks[index].Code, "undefined") )
    index++;

  return GSM_Networks[index].Name;
}

char *GSM_GetNetworkCode(char *NetworkName)
{

  int index=0;

  while ( strcmp(GSM_Networks[index].Name, NetworkName) &&
          strcmp(GSM_Networks[index].Code, "undefined") )
    index++;

  return GSM_Networks[index].Code;
}

char *GSM_GetCountryName(char *CountryCode)
{

  int index=0;

  while ( strncmp(GSM_Countries[index].Code, CountryCode, 3) &&
          strcmp(GSM_Countries[index].Code, "undefined") )
    index++;

  return GSM_Countries[index].Name;
}

char *GSM_GetCountryCode(char *CountryName)
{

  int index=0;

  while ( strcmp(GSM_Countries[index].Name, CountryName) &&
          strcmp(GSM_Countries[index].Code, "undefined") )
    index++;

  return GSM_Countries[index].Code;
}

void EncodeNetworkCode(unsigned char* buffer, unsigned char* output)
{
    EncodeBCD (buffer, output, 6, false);
    buffer[1]=buffer[1] | 0xf0;
}

void DecodeNetworkCode(unsigned char* buffer, unsigned char* output)
{
    DecodeBCD (output, buffer, 3);
    output[6]=output[5];
    output[5]=output[4];
    output[4]=output[3];
    output[3]=' ';
}
