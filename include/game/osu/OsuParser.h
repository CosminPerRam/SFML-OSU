////////////////////////////////////////////////////////////////
//                                                            //
//      OsuParser.h                                           //
//      HaselLoyance 2017-2018, Unlicense                     //
//      https://github.com/HaselLoyance/osu-parser            //
//                                                            //
////////////////////////////////////////////////////////////////

#pragma once

#ifndef OSU_PARSER_OSU_H
#define OSU_PARSER_OSU_H

#include <sstream>
#include <fstream>
#include "./game/osu/OsTypes.h"
#include "./game/osu/OsUtils.h"
#include <iostream>

namespace osuParser
{
	// Object for parsing "*.osu" files from preloaded stream
	// For file format please visit: https://osu.ppy.sh/help/wiki/osu!_File_Formats/Osu_(file_format)
	class OsuParser
	{
	public:
		// Creates a parser from input data stream
		OsuParser(std::ifstream* stream, std::string folder);
		OsuParser();
		~OsuParser();

		OsuParser(const OsuParser& q);

		// Goes through istream and reads all data
		bool Parse();

		// Version of beatmap file
		uint8_t formatVersion;

		// Location of the audio file
		std::string audioFilename;

		// Amount of time added before the audio file begins playing
		OsTime audioLeadIn;

		// When the audio file should begin playing when selected in the song selection menu
		OsTime previewTime;

		// Whether or not a countdown occurs before the first hit object appears
		bool countdown;

		// What set of hit sounds will be used
		SampleSet sampleSet;

		// How often closely placed hit objects will be stacked together
		double stackLeniency;

		// Defines the game mode
		GameMode mode;

		// Whether the letterbox appears during breaks
		bool letterboxInBreaks;

		// Whether or not the storyboard should be widescreen
		bool widescreenStoryboard;

		// Times of editor bookmarks
		std::vector<OsTime> bookmarks;

		// Multiplier for the "Distance Snap" feature
		double distanceSpacing;

		// Beat division for placing objects
		uint8_t beatDivisor;

		// Size of the grid for the "Grid Snap" feature
		uint8_t gridSize;

		// Grid level as it appears in the editor
		uint8_t gridLevel;

		// Zoom in the editor timeline
		double timelineZoom;

		// Title of the song limited to ASCII characters
		std::string title;

		// Title of the song with unicode support. If not present, title is used
		std::string titleUnicode;

		// Name of the song's artist limited to ASCII characters
		std::string artist;

		// Name of the song's artist with unicode support. If not present, artist is used
		std::string artistUnicode;

		// Username of the mapper
		std::string creator;

		// Name of the beatmap's difficulty
		std::string version;

		// Describes the origin of the song
		std::string source;

		// Vector of words describing the song
		std::vector<std::string> tags;

		// ID of the single beatmap
		OsInteger beatmapID;

		// ID of the beatmap set
		OsInteger beatmapSetID;

		// HP drain difficulty
		double hpDrainRate, HP;

		// Size of hit object circles
		double circleSize, CS;

		// Amount of time allowed to click a hit object on time
		double overallDifficulty, OD;

		// Amount of time taken for the approach circle and hit object to appear
		double approachRate, AR;

		// Radius of a circle based on CS in osu! pixels
		double circleRadiusPx;

		// How much time is allowed to hit each score
		OsTime hitWindow300, hitWindow100, hitWindow50;

		// Harshness of spinners based on OD. Rotations per second required
		double requiredRPS;

		// Amount of time since object's start to fade in to perfect hit
		OsTime preemptMs;

		// Amount of time it takes for object to completely fade in
		OsTime fadeInMs;

		// Multiplier for the slider velocity
		double sliderMultiplier;

		// How often slider ticks appear
		double sliderTickRate;

		// Events related to background and breaks
		std::vector<Event> events;

		// Vector of timing points that describe a number of
		//   properties regarding beats per minute and hit sounds
		std::vector<TimingPoint> timingPoints;

		// All values of msPerBeat in the beatmap that are inheritable
		std::vector<double> msPerBeats;

		// Lowest beatmap BPM (highest msPerBeat)
		double lowestBPM;

		// Highest beatmap BPM (lowest msPerBeat)
		double highestBPM;

		// Average beatmap BPM
		double averageBPM;

		// Vector of the colors of the combos
		std::vector<RGBAColor> colors;

		// Vector of all the hit objects in a beatmap
		std::vector<HitObject> hitObjects;

		std::string m_folder;

	private:
		// Methods that extract and parse data from beatmap file
		void _GetBeatmapVersion();
		void _ExtractStructure();
		_OsSection _GetSection(const std::string & name = "General");
		template<typename T>
		T _ParseSectionField(const _OsSection & section, const std::string & fieldName, const T & defaultTo);
		template<typename T>
		std::vector<T> _ParseSectionFieldAsList(const _OsSection & section, const std::string & fieldName, const std::string & delim);
		Event _ParseFieldAsEvent(const std::string & field);
		TimingPoint _ParseFieldAsTimingPoint(const std::string & field);
		RGBAColor _ParseFieldAsRGBAColor(const std::string & field);
		HitObject _ParseFieldAsHitObject(const std::string & field);
		void _ExtractExtras(const std::string & s, HitObject & o);

		// When hit objects' extras are adjusted based on inheritance from
		//   timing points this counter is used, so there are no three leveled
		//   references through methods
		size_t _tpIndex;

		// Structure of all of the sections of the beatmap with all fields
		_OsBeatmap _b;

		// Data stream
		std::ifstream* _s;
	};
}

// Prepares the parser
osuParser::OsuParser::OsuParser(std::ifstream* stream, std::string folder)
{
	_s = stream;
	m_folder = folder;
	formatVersion = 0;
	audioFilename.clear();
	audioLeadIn = 0;
	previewTime = 0;
	countdown = false;
	sampleSet = ssAuto;
	stackLeniency = 0.0;
	mode = gmStandard;
	letterboxInBreaks = false;
	widescreenStoryboard = false;
	bookmarks = {};
	distanceSpacing = 0.0;
	beatDivisor = 0;
	gridSize = 0;
	gridLevel = 0;
	timelineZoom = 0.0;
	title.clear();
	titleUnicode.clear();
	artist.clear();
	artistUnicode.clear();
	creator.clear();
	version.clear();
	source.clear();
	tags = {};
	beatmapID = 0;
	beatmapSetID = 0;
	hpDrainRate = 0.0;
	HP = 0.0;
	circleSize = 0.0;
	CS = 0.0;
	circleRadiusPx = 0.0;
	overallDifficulty = 0.0;
	OD = 0.0;
	hitWindow300 = 0;
	hitWindow100 = 0;
	hitWindow50 = 0;
	requiredRPS = 0.0;
	approachRate = 0.0;
	AR = 0.0;
	preemptMs = 0;
	fadeInMs = 0;
	sliderMultiplier = 0.0;
	sliderTickRate = 0.0;
	events = {};
	timingPoints = {};
	msPerBeats = {};
	lowestBPM = 0.0;
	highestBPM = 0.0;
	averageBPM = 0.0;
	colors = {};
	hitObjects = {};

	_tpIndex = 0;
	_b = {};
}

osuParser::OsuParser::OsuParser() {};

osuParser::OsuParser::~OsuParser() {};

//Copy constructor
osuParser::OsuParser::OsuParser(const OsuParser& q) {
	this->formatVersion = q.formatVersion;
	this->audioFilename = q.audioFilename;
	this->m_folder = q.m_folder;
	this->audioLeadIn = q.audioLeadIn;
	this->previewTime = q.previewTime;
	this->countdown = q.countdown;
	this->sampleSet = q.sampleSet;
	this->stackLeniency = q.stackLeniency;
	this->mode = q.mode;
	this->letterboxInBreaks = q.letterboxInBreaks;
	this->widescreenStoryboard = q.widescreenStoryboard;
	this->bookmarks = q.bookmarks;
	this->distanceSpacing = q.distanceSpacing;
	this->beatDivisor = q.beatDivisor;
	this->gridSize = q.gridSize;
	this->gridLevel = q.gridLevel;
	this->timelineZoom = q.timelineZoom;
	this->title = q.title;
	this->titleUnicode = q.titleUnicode;
	this->artist = q.artist;
	this->artistUnicode = q.artistUnicode;
	this->creator = q.creator;
	this->version = q.version;
	this->source = q.source;
	this->tags = q.tags;
	this->beatmapID = q.beatmapID;
	this->beatmapSetID = q.beatmapSetID;
	this->hpDrainRate = q.hpDrainRate;
	this->HP = q.HP;
	this->circleSize = q.circleSize;
	this->CS = q.CS;
	this->circleRadiusPx = q.circleRadiusPx;
	this->overallDifficulty = q.overallDifficulty;
	this->OD = q.OD;
	this->hitWindow300 = q.hitWindow300;
	this->hitWindow100 = q.hitWindow100;
	this->hitWindow50 = q.hitWindow50;
	this->requiredRPS = q.requiredRPS;
	this->approachRate = q.approachRate;
	this->AR = q.AR;
	this->preemptMs = q.preemptMs;
	this->fadeInMs = q.fadeInMs;
	this->sliderMultiplier = q.sliderMultiplier;
	this->sliderTickRate = q.sliderTickRate;
	this->events = q.events;
	this->timingPoints = q.timingPoints;
	this->msPerBeats = q.msPerBeats;
	this->lowestBPM = q.lowestBPM;
	this->highestBPM = q.highestBPM;
	this->averageBPM = q.averageBPM;
	this->colors = q.colors;
	this->hitObjects = q.hitObjects;
}

// Goes through istream and reads all data
bool osuParser::OsuParser::Parse()
{
	_s->seekg(0);

	_GetBeatmapVersion();

	_ExtractStructure();

	_s->seekg(0);

	_OsSection defaultSection = _OsSection({});

	// GENERAL
	_OsSection t = _GetSection("General");
	if (t != defaultSection)
	{
		audioFilename = _ParseSectionField<string>(t, "AudioFilename", "Unknown");
		audioLeadIn = _ParseSectionField<OsTime>(t, "AudioLeadIn", 0);
		previewTime = _ParseSectionField<OsTime>(t, "PreviewTime", 0);
		countdown = _ParseSectionField<bool>(t, "Countdown", false);
		sampleSet = StringToEnum<SampleSet>(_ParseSectionField<string>(t, "SampleSet", "Unknown"), _sampleSetNames);
		// TODO: Implement this https://osu.ppy.sh/help/wiki/Beatmap_Editor/Song_Setup 
		stackLeniency = _ParseSectionField<double>(t, "StackLeniency", 0.7);
		mode = (GameMode)_ParseSectionField<int>(t, "Mode", 0);
		letterboxInBreaks = _ParseSectionField<bool>(t, "LetterboxInBreaks", false);
		widescreenStoryboard = _ParseSectionField<bool>(t, "WidescreenStoryboard", false);
	}

	// EDITOR
	t = _GetSection("Editor");
	if (t != defaultSection)
	{
		bookmarks = _ParseSectionFieldAsList<OsTime>(t, "Bookmarks", ",");
		distanceSpacing = _ParseSectionField<double>(t, "DistanceSpacing", 1.22);
		beatDivisor = _ParseSectionField<int>(t, "BeatDivisor", 4); //-V112
		gridSize = _ParseSectionField<int>(t, "GridSize", 4); //-V112
		gridLevel = -round(log2(gridSize)) + 6;
		timelineZoom = _ParseSectionField<double>(t, "TimelineZoom", 1.0);
	}

	// METADATA
	t = _GetSection("Metadata");
	if (t != defaultSection)
	{
		title = _ParseSectionField<string>(t, "Title", "Unknown");
		titleUnicode = _ParseSectionField<string>(t, "TitleUnicode", title);
		artist = _ParseSectionField<string>(t, "Artist", "Unknown");
		artistUnicode = _ParseSectionField<string>(t, "ArtistUnicode", artist);
		creator = _ParseSectionField<string>(t, "Creator", "Unknown");
		version = _ParseSectionField<string>(t, "Version", "Unknown");
		source = _ParseSectionField<string>(t, "Source", "Unknown");
		tags = _ParseSectionFieldAsList<string>(t, "Tags", " ");
		beatmapID = _ParseSectionField<OsInteger>(t, "BeatmapID", 0);
		beatmapSetID = _ParseSectionField<OsInteger>(t, "BeatmapSetID", 0);
	}

	// DIFFICULTY
	t = _GetSection("Difficulty");
	if (t != defaultSection)
	{
		hpDrainRate = _ParseSectionField<double>(t, "HPDrainRate", 5.0);
		HP = hpDrainRate;
		circleSize = _ParseSectionField<double>(t, "CircleSize", 4.0);
		CS = circleSize;
		overallDifficulty = _ParseSectionField<double>(t, "OverallDifficulty", 6.0);
		OD = overallDifficulty;
		approachRate = _ParseSectionField<double>(t, "ApproachRate", 7.0);
		AR = approachRate;
		sliderMultiplier = _ParseSectionField<double>(t, "SliderMultiplier", 1.4);
		sliderTickRate = _ParseSectionField<double>(t, "SliderTickRate", 1.0);

		preemptMs = (AR < 5.0 || IsEqualDouble(AR, 5.0))
			? (1800.0 - 120.0 * AR)
			: (1950.0 - 150.0 * AR);

		fadeInMs = (AR < 5.0 || IsEqualDouble(AR, 5.0))
			? (1200.0 - 80.0 * AR)
			: (1300.0 - 100.0 * AR);

		circleRadiusPx = 54.4 - 4.48 * CS;

		hitWindow300 = 80.0 - 6.0 * OD;
		hitWindow100 = 140.0 - 8.0 * OD;
		hitWindow50 = 200.0 - 10.0 * OD;

		requiredRPS = (OD < 5.0 || IsEqualDouble(OD, 5.0))
			? (3.0 - 2.0 / 5.0 * OD)
			: (5.0 - 5.0 / 2.0 + OD / 2.0);
	}

	// EVENTS
	t = _GetSection("Events");
	if (t != defaultSection)
	{
		for (auto&& f : t.second)
		{
			if (Event e = _ParseFieldAsEvent(f); e.type != eUnknown)
			{
				events.push_back(e);
			}
		}
	}

	// TIMING POINTS
	t = _GetSection("TimingPoints");
	if (t != defaultSection)
	{
		for (auto&& f : t.second)
		{
			timingPoints.push_back(_ParseFieldAsTimingPoint(f));
		}

		lowestBPM = 1234567.0;
		highestBPM = -1234567.0;
		averageBPM = 0.0;

		for (auto&& msPerBeat : msPerBeats)
		{
			double bpm = 60000.0 / msPerBeat;

			if (bpm > highestBPM)
			{
				highestBPM = bpm;
			}

			if (bpm < lowestBPM)
			{
				lowestBPM = bpm;
			}

			averageBPM += bpm;
		}

		averageBPM /= (double)msPerBeats.size();
	}

	// COLORS
	t = _GetSection("Colours");
	if (t != defaultSection)
	{
		for (auto&& f : t.second)
		{
			// Hmmm... so apparently there are "Special coloUrs" for slider
			// TODO (not a priority) them some time 

			colors.push_back(_ParseFieldAsRGBAColor(f));
		}
	}

	// HIT OBJECTS
	t = _GetSection("HitObjects");
	if (t != defaultSection)
	{
		for (auto&& f : t.second)
		{
			hitObjects.push_back(_ParseFieldAsHitObject(f));
		}
	}

	_b.clear();

	return true;
}

void osuParser::OsuParser::_GetBeatmapVersion()
{
	string fileVersionString = "";
	getline(*_s, fileVersionString);

	if (size_t len = fileVersionString.find('v'); len != string::npos)
	{
		fileVersionString.erase(0, len + 1);
		formatVersion = stoi(fileVersionString);

		return;
	}

	formatVersion = (uint8_t)-1;
}

void osuParser::OsuParser::_ExtractStructure()
{
	string t;

	while (!_s->eof() && !_s->fail())
	{
		getline(*_s, t);
		TrimString(t);

		if (t.empty())
		{
			continue;
		}

		size_t sz = t.size();

		if (t[0] != '[' || t[sz - 1] != ']')
		{
			continue;
		}

		_OsSection section;
		section.first = t.substr(1, sz - 2);

		while (true)
		{
			getline(*_s, t);
			TrimString(t);

			if (t.empty())
			{
				break;
			}

			// Skip commented lines
			if (t[0] == '#' || t.find("//") == 0)
			{
				continue;
			}

			section.second.push_back(t);
		}

		_b.push_back(section);
	}
}

osuParser::_OsSection osuParser::OsuParser::_GetSection(const std::string& name)
{
	for (auto&& section : _b)
	{
		if (section.first == name)
		{
			return section;
		}
	}

	return {};
}

template<typename T>
T osuParser::OsuParser::_ParseSectionField(const _OsSection& section, const string& fieldName, const T& defaultTo)
{
	for (auto&& field : section.second)
	{
		if (field.find(fieldName) == string::npos)
		{
			continue;
		}

		string f = field;
		if (size_t len = f.find(':'); len != string::npos)
		{
			f.erase(0, len + 1);

			while (f[0] == ' ') //remove whitespaces at the beginning
				f.erase(0, 1);

			// OH BOY, LOOK, THIS RANDOM constexpr OVER HERE MAKES IT WORK
			if constexpr (is_same_v<T, string>)
			{
				return f;
			}
			else
			{
				T t;
				stringstream(f) >> t;
				return t;
			}
		}
	}

	return defaultTo;
}

template<typename T>
vector<T> osuParser::OsuParser::_ParseSectionFieldAsList(const _OsSection& section, const string& fieldName, const string& delim)
{
	for (auto&& field : section.second)
	{
		if (field.find(fieldName) == string::npos)
		{
			continue;
		}

		string f = field;
		if (size_t len = f.find(':'); len != string::npos)
		{
			f.erase(0, len + 1);

			vector<string> listValues;
			vector<T> listT;
			SplitString(f, delim, listValues);

			for (auto&& val : listValues)
			{
				if constexpr (is_same_v<T, std::string>)
				{
					listT.push_back(val);
				}
				else
				{
					T t;
					stringstream(val) >> t;
					listT.push_back(t);
				}
			}

			return listT;
		}
	}

	return {};
}

osuParser::Event osuParser::OsuParser::_ParseFieldAsEvent(const string& field)
{
	string f = field;

	vector<string> args;
	SplitString(f, ",", args);

	if (args[0] == "0")
	{
		return { eBackground, args[2] };
	}
	else if (args[0] == "2")
	{
		return { eBreak, "", stoll(args[1]), stoll(args[2]) };
	}
	else if (args[0] == "Video")
	{
		size_t sz = f.find('"') + 1;
		return { eVideo, string(f, sz, f.find_last_of('"') - sz), stoll(args[1]) };
	}

	return { eUnknown };
}

osuParser::TimingPoint osuParser::OsuParser::_ParseFieldAsTimingPoint(const string& field)
{
	string f = field;

	vector<string> args;
	SplitString(f, ",", args);

	TimingPoint tp;

	tp.offset = stoll(args[0]);
	tp.msPerBeat = stod(args[1]);

	if (tp.msPerBeat > 0)
	{
		tp.adjustedMsPerBeat = tp.msPerBeat;

		msPerBeats.push_back(tp.msPerBeat);
	}
	else
	{
		tp.adjustedMsPerBeat = (tp.msPerBeat / -100.0) * msPerBeats.back();
	}

	tp.beatsPerMeasure = (uint8_t)stoi(args[2]);
	tp.sampleSet = (SampleSet)stoi(args[3]);
	tp.sampleIndex = (uint8_t)stoi(args[4]);
	tp.volume = (uint8_t)stoi(args[5]);
	tp.isInheritable = (bool)stoi(args[6]);
	tp.isKiaiMode = (bool)stoi(args[7]);

	return tp;
}

osuParser::RGBAColor osuParser::OsuParser::_ParseFieldAsRGBAColor(const string& field)
{
	string f = field; //-V808

	if (size_t len = f.find(':'); len != string::npos)
	{
		f.erase(0, len + 1);

		vector<string> args;
		SplitString(f, ",", args);

		return {
			(uint8_t)stoi(args[0]),
			(uint8_t)stoi(args[1]),
			(uint8_t)stoi(args[2]),
		};
	}

	return {};
}

osuParser::HitObject osuParser::OsuParser::_ParseFieldAsHitObject(const string& field)
{
	string f = field;

	vector<string> args;
	SplitString(f, ",", args);

	HitObject o;

	o.x = (uint16_t)stoi(args[0]);
	o.y = (uint16_t)stoi(args[1]);
	o.time = stoll(args[2]);
	o.mask = (HitObjectMask)stoi(args[3]);

	if (IsBitSet(o.mask, 0))
	{
		o.type = oCircle;
	}

	if (IsBitSet(o.mask, 1))
	{
		o.type = oSlider;
	}

	if (IsBitSet(o.mask, 3))
	{
		o.type = oSpinner;
	}

	if (IsBitSet(o.mask, 7))
	{
		o.type = oHoldNote;
	}

	o.isNewCombo = IsBitSet(o.mask, 2);

	if (o.isNewCombo)
	{
		o.skipComboColors =
			((uint8_t)IsBitSet(o.mask, 4) << 0) |
			((uint8_t)IsBitSet(o.mask, 5) << 1) |
			((uint8_t)IsBitSet(o.mask, 6) << 2);
	}

	o.soundMask = (HitSoundMask)stoi(args[4]);

	_ExtractExtras(args.back(), o);

	// TODO: maybe safety checks for args size for different type of hit objects
	if (o.type == oSpinner)
	{
		o.spinner.isSpinner = true;
		o.spinner.end = stoll(args[5]);
		o.spinner.duration = o.spinner.end - o.time;
	}

	if (o.type == oSlider)
	{
		o.slider.isSlider = true;
		o.slider.curvePoints.push_back({ o.x, o.y });

		switch (args[5][0])
		{
		case 'B': o.slider.type = sBezier; break;
		case 'C': o.slider.type = sCatmull; break;
		case 'P': o.slider.type = sPerfect; break;
		default: o.slider.type = sLinear; break;
		}

		args[5].erase(0, 2);

		vector<string> params;
		SplitString(args[5], "|", params);

		for (auto&& p : params)
		{
			vector<string> values;
			SplitString(p, ":", values);

			o.slider.curvePoints.push_back({
				(uint16_t)stoi(values[0]),
				(uint16_t)stoi(values[1]),
				});
		}

		o.slider.nRepeats = (uint8_t)stoi(args[6]);
		o.slider.length = stod(args[7]);
		o.slider.duration = (o.slider.length * o.slider.nRepeats) / (100.0 * sliderMultiplier) * timingPoints[_tpIndex].adjustedMsPerBeat;
		o.slider.end = o.time + o.slider.duration;

		SplitString(args[8], "|", params);

		for (size_t i = 0; i < params.size(); i++)
		{
			o.slider.edgeHitSounds.push_back((HitSoundMask)stoi(params[i]));
		}

		SplitString(args[9], "|", params);

		for (size_t i = 0; i < params.size(); i++)
		{
			vector<string> values;
			SplitString(params[i], ":", values);

			o.slider.curvePoints.push_back({
				(uint16_t)stoi(values[0]),
				(uint16_t)stoi(values[1]),
				});
		}
	}

	return o;
}

void osuParser::OsuParser::_ExtractExtras(const string& s, HitObject& o)
{
	vector<string> params;
	SplitString(s, ":", params);

	// Valid extras have at least 4 values
	if (params.size() < 4) //-V112
	{
		return;
	}

	o.extra.sampleSet = (SampleSet)stoi(params[0]);
	o.extra.additionSet = (SampleSet)stoi(params[1]);
	o.extra.customIndex = (uint8_t)stoi(params[2]);
	o.extra.volume = (uint8_t)stoi(params[3]);

	if (params.size() == 5)
	{
		o.extra.volume = (uint8_t)stoi(params[4]);
	}

	o.adjustedExtra = o.extra;

	// Keep track of the internal timing point counter
	while (_tpIndex + 1 < timingPoints.size() && o.time >= timingPoints[_tpIndex + 1].offset)
	{
		_tpIndex++;
	}

	const TimingPoint& tp = timingPoints[_tpIndex];

	if (o.extra.sampleSet == ssAuto)
	{
		o.adjustedExtra.sampleSet = tp.sampleSet;
	}

	o.adjustedExtra.additionSet = tp.sampleSet;

	if (o.extra.customIndex == 0)
	{
		o.adjustedExtra.customIndex = tp.sampleIndex;
	}
}

#endif
