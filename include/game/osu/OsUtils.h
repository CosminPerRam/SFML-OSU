////////////////////////////////////////////////////////////////
//                                                            //
//      OsUtils.h                                             //
//      HaselLoyance 2017-2018, Unlicense                     //
//      https://github.com/HaselLoyance/osu-parser            //
//                                                            //
////////////////////////////////////////////////////////////////

#ifndef OSU_PARSER_UTILS_H
#define OSU_PARSER_UTILS_H

#include <algorithm>
#include <cctype>
#include <string>
#include <fstream>
#include <math.h>
#include "./game/osu/OsTypes.h"
#include "LzmaLib.h"

#define IsBitSet(variable, bitNumber) bool((variable) & (1 << (bitNumber)))

namespace osuParser
{
	// Splits a string into multiple parts with given delimiter
	//   str, string, string to split
	//   delimiter, string, in what places to split the string
	//   output, ref vector<string>, all parts of the splitted string
	// Eg: SplitString("1|2|3,4|5|6", ',', output) -> ["1|2|3","4|5|6"]
	void SplitString(const std::string & str, const std::string & delimiter, std::vector<std::string> & output);

	// Trims (removes whitespace) passed string
	//   str, ref string, string to trim
	void TrimString(std::string & str);

	// Decompress LZMA-compressed buffer
	//   inBuf, vector<uint8_t>, input buffer with LZMA-compressed bytes
	//   outBuf, ref vector<uint8_t>, output buffer where decompressed data will be written
	void DecompressLZMA(const std::vector<uint8_t> &inBuf, std::vector<uint8_t> & outBuf);

	// Checks to see if two double values are equal
	//   a, double, first value to check
	//   b, double, second value to check
	// Returns true if both values are equal, false otherwise
	bool IsEqualDouble(const double & a, const double & b);

	// String names for each available mod
	const extern std::vector<std::string> _modNames;

	// String names for each available game mode
	const extern std::vector<std::string> _modeNames;

	// String names for each available sample set
	const extern std::vector<std::string> _sampleSetNames;

	// String names for each available beatmap event
	const extern std::vector<std::string> _eventNames;

	// String names for each available hit sound type
	const extern std::vector<std::string> _hitSoundNames;

	// String names for each available slider type
	const extern std::vector<std::string> _sliderNames;

	// Converts any enumerated type value to the string from
	// associated vector of string values
	// <T>: enumerated type
	//   val, T, value of the enumerated type
	//   names, vector<string>, dictionary of string values for enum
	//   defaultTo, string, what to default return value to if there is
	//     no associated string value, defaults to "Unknown"
	// Returns a string representation of the enumerated type value
	template<typename T>
	std::string EnumToString(const T & val, const std::vector<std::string> & names, const std::string & defaultTo = "Unknown")
	{
		if (val < 0 || val > names.size())
		{
			return defaultTo;
		}

		return names[val];
	}

	// Converts string value to any enumerated type value via
	// associated vector of string values
	// <T>: enumerated type
	//   val, string, string value
	//   names, vector<string>, dictionary of string values for enum
	//   defaultTo, T, what to default return value to if there is
	//     no associated enumerated type value, defaults to T(0)
	// Returns a T representation of the string value
	template<typename T>
	T StringToEnum(const std::string & val, const std::vector<std::string> & names, const T & defaultTo = static_cast<T>(0))
	{
		for (size_t i = 0; i < names.size(); i++)
		{
			if (names[i] == val)
			{
				return static_cast<T>(i);
			}
		}

		return defaultTo;
	}
}

using namespace std;

// Splits a string into multiple parts with given delimiter
//   str, string, string to split
//   delimiter, string, in what places to split the string
//   output, ref vector<string>, all parts of the splitted string
// Eg: SplitString("1|2|3,4|5|6", ',', output) -> ["1|2|3","4|5|6"]
void osuParser::SplitString(const string& str, const string& delimiter, vector<string>& output)
{
	output.clear();

	size_t prev = 0;
	size_t pos = 0;

	while (true)
	{
		pos = str.find(delimiter, prev);

		if (pos == string::npos)
		{
			pos = str.length();
		}

		output.push_back(str.substr(prev, pos - prev));

		prev = pos + delimiter.length();

		if (pos >= str.length() || prev >= str.length())
		{
			break;
		}
	}
}

// Trims (removes whitespace) passed string
//   str, ref string, string to trim
void osuParser::TrimString(string& str) {
	str.erase(str.begin(), find_if(str.begin(), str.end(), [](int ch) {
		return !isspace(static_cast<unsigned char>(ch));
		}));
}

// Decompress LZMA-compressed buffer
//   inBuf, vector<uint8_t>, input buffer with LZMA-compressed bytes
//   outBuf, ref vector<uint8_t>, output buffer where decompressed data will be written
void osuParser::DecompressLZMA(const vector<uint8_t>& inBuf, vector<uint8_t>& outBuf)
{
	outBuf.clear();
	// Reserves N bytes, shrinks to fit after decompression
	outBuf.resize(inBuf.size() * 4); //-V112
	size_t dstLen = outBuf.size();
	size_t srcLen = inBuf.size() - LZMA_PROPS_SIZE - 8;
	LzmaUncompress(&outBuf[0], &dstLen, &inBuf[LZMA_PROPS_SIZE + 8], &srcLen, &inBuf[0], LZMA_PROPS_SIZE);
	outBuf.resize(dstLen);
}

// Checks to see if two double values are equal
//   a, double, first value to check
//   b, double, second value to check
// Returns true if both values are equal, false otherwise
bool osuParser::IsEqualDouble(const double& a, const double& b)
{
	return fabs(a - b) < DBL_EPSILON;
}

// String names for each available mod
const vector<string> osuParser::_modNames = {
	"NoFail", "Easy", "NoVideo", "Hidden", "HardRock", "SuddenDeath", "DoubleTime",
	"Relax", "HalfTime", "Nightcore", "Flashlight", "Autoplay", "SpunOut", "Relax2",
	"Perfect", "Key4", "Key5", "Key6", "Key7", "Key8", "FadeIn", "Random", "LastMod",
	"TargetPractice", "Key9", "Coop", "Key1", "Key3", "Key2",
};

// String names for each available game mode
const vector<string> osuParser::_modeNames = {
	"Standard", "Taiko", "Catch The Beat", "Mania"
};

// String names for each available sample set
const vector<string> osuParser::_sampleSetNames = {
	"Auto", "Normal", "Soft", "Drum"
};

// String names for each available beatmap event
const vector<string> osuParser::_eventNames = {
	"Background", "Video", "Break", "Unknown"
};

// String names for each available hit sound type
const vector<string> osuParser::_hitSoundNames = {
	"Normal", "Whistle", "Finish", "Clap"
};

// String names for each available slider type
const vector<string> osuParser::_sliderNames = {
	"Linear", "Perfect", "Bezier", "Catmull"
};


#endif
