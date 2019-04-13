#include "PianoNote.h"

vector<PianoNote> Notes;

int notesPerMin_ = 0;
int durationOfNote_ = 0;

int TurnPianoNoteToFreq(string);

void PlayNeededNotes(int currentNote)
{
	for ( unsigned int i = 0; i < Notes.size(); i++)
	{
		if (Notes[i].noteOffsetFromStart == currentNote)
		{
			Beep(Notes[i].noteFrequency, durationOfNote_*Notes[i].duration);
			return;
		}
	}
	return;
}

void ChangeNotesPerMin(int notespermin)
{
	notesPerMin_ = notespermin;
	durationOfNote_ = 60000 / notesPerMin_;
	return;
}

void addNote(PianoNote newNote)
{
	Notes.push_back(newNote);
	return;
}

void FindBPM(string str)
{
	string BPM;
	BPM.clear();
	for (int i = 0; str[i] != 'b'; i++)
	{
		BPM += str[i];
	}
	if (BPM != "")
	{
		int BPM_ = (int)strtol(BPM.c_str(), NULL, 10);
		ChangeNotesPerMin(BPM_);
	}

	return;
}

int GetBPM()
{
	return notesPerMin_;
}

bool SpecialCase(string str)
{
	bool foundSomething = false;

	if (str.find("bpm") != string::npos)
	{
		FindBPM(str);
		foundSomething = true;
	}

	else if (str[0] == 'A' || str[0] == 'B' || str[0] == 'C' || str[0] == 'D' || str[0] == 'E' || str[0] == 'F' || str[0] == 'G')
	{
		string freq;
		string duration;
		string offset;
		PianoNote dyn;
		freq.clear();

		int i = 0;
		for (i = 0; str[i] != ' '; i++)
			freq += str[i];

		dyn.noteFrequency = TurnPianoNoteToFreq(freq);
		i++;

		for (; i != str.size() && str[i] != ' '; i++)
			offset += str[i];
		for (; i != str.size(); i++)
			duration += str[i];
		if (duration == "")
			duration = "1";

		dyn.noteOffsetFromStart = (int)strtol(offset.c_str(), NULL, 10);
		dyn.duration = (int)strtol(duration.c_str(), NULL, 10);
		addNote(dyn);

		foundSomething = true;
	}

	return foundSomething;
}

void readAndLoad(string file)
{
	ifstream loadedFile;

	loadedFile.open(file);

	if (!loadedFile.is_open())
	{
		cout << "error: invalid file" << endl;
		system("pause");
		exit(0);
	}

	vector<string> listOfNotes;

	string note;

	string freq;

	string offset;

	string duration;

	PianoNote dynHold;

	while (loadedFile.good())
	{
		note.clear();
		getline(loadedFile, note);
		if (note.size()!= 0)
			listOfNotes.push_back(note);
	}

	loadedFile.close();

	if (listOfNotes.size() == 0)
		return;

	for (unsigned int i = 0; i < listOfNotes.size(); i++)
	{
		int s = 0;
		freq.clear();
		offset.clear();
		duration.clear();
		note = listOfNotes[i];
		if (!SpecialCase(note))
		{
			for (s = 0; note[s] != ' '; s++)
				freq += note[s];
			s++;
			for (; s != note.size() && note[s] != ' '; s++)
				offset += note[s];
			for (; s != note.size(); s++)
				duration += note[s];
			if (duration == "")
				duration = "1";
			dynHold.noteFrequency = (int)strtol(freq.c_str(), NULL, 10);
			dynHold.noteOffsetFromStart = (int)strtol(offset.c_str(), NULL, 10);
			dynHold.duration = (int)strtol(duration.c_str(), NULL, 10);
			addNote(dynHold);
		}
	}
	cout << "success loading" << endl;
	return;
}

void loadHelp()
{
	ifstream loadedFile;

	loadedFile.open("help.txt");

	if (!loadedFile.is_open())
	{
		cout << "error: no help file" << endl;
		system("pause");
		exit(0);
	}

	string line;

	while (loadedFile.good())
	{
		line.clear();
		getline(loadedFile, line);
		cout << line << endl;
	}
}

int GetLastNote()
{
	int lastnote = 0;
	for (unsigned int i = 0; i < Notes.size(); i++)
	{
		if (Notes[i].noteOffsetFromStart > lastnote)
			lastnote = Notes[i].noteOffsetFromStart;
	}
	return lastnote;
}

int TurnPianoNoteToFreq(string PN)
{
	if (PN == "C0")
		return 16;

	else if (PN == "C#0" || PN == "Db0")
		return 17;

	else if (PN == "D0")
		return 18;

	else if (PN == "D#0" || PN == "Eb0")
		return 19;

	else if (PN == "E0")
		return 21;

	else if (PN == "F0")
		return 22;

	else if (PN == "F#0" || PN == "Gb0")
		return 23;

	else if (PN == "G0")
		return 25;

	else if (PN == "G#0" || PN == "Ab0")
		return 26;

	else if (PN == "A0")
		return 28;

	else if (PN == "A#0" || PN == "Bb0")
		return 29;

	else if (PN == "B0")
		return 31;

	else if (PN == "C1")
		return 33;

	else if (PN == "C#1" || PN == "Db1")
		return 35;

	else if (PN == "D1")
		return 37;

	else if (PN == "D#1" || PN == "Eb1")
		return 39;

	else if (PN == "E1")
		return 41;

	else if (PN == "F1")
		return 44;

	else if (PN == "F#1" || PN == "Gb1")
		return 46;

	else if (PN == "G1")
		return 49;

	else if (PN == "G#1" || PN == "Ab1")
		return 52;

	else if (PN == "A1")
		return 55;

	else if (PN == "A#1" || PN == "Bb1")
		return 58;

	else if (PN == "B1")
		return 62;

	else if (PN == "C2")
		return 65;

	else if (PN == "C#2" || PN == "Db2")
		return 69;

	else if (PN == "D2")
		return 73;

	else if (PN == "D#2" || PN == "Eb2")
		return 78;

	else if (PN == "E2")
		return 82;

	else if (PN == "F2")
		return 87;

	else if (PN == "F#2" || PN == "Gb2")
		return 93;

	else if (PN == "G2")
		return 98;

	else if (PN == "G#2" || PN == "Ab2")
		return 104;

	else if (PN == "A2")
		return 110;

	else if (PN == "A#2" || PN == "Bb2")
		return 117;

	else if (PN == "B2")
		return 123;

	else if (PN == "C3")
		return 131;

	else if (PN == "C#3" || PN == "Db3")
		return 139;

	else if (PN == "D3")
		return 147;

	else if (PN == "D#3" || PN == "Eb3")
		return 156;

	else if (PN == "E3")
		return 165;

	else if (PN == "F3")
		return 175;

	else if (PN == "F#3" || PN == "Gb3")
		return 185;

	else if (PN == "G3")
		return 196;

	else if (PN == "G#3" || PN == "Ab3")
		return 208;

	else if (PN == "A3")
		return 220;

	else if (PN == "A#3" || PN == "Bb3")
		return 233;

	else if (PN == "B3")
		return 247;

	else if (PN == "C4" || PN == "middleC")
		return 262;

	else if (PN == "C#4" || PN == "Db4")
		return 277;

	else if (PN == "D4")
		return 294;

	else if (PN == "D#4" || PN == "Eb4")
		return 311;

	else if (PN == "E4")
		return 330;

	else if (PN == "F4")
		return 349;

	else if (PN == "F#4" || PN == "Gb4")
		return 370;

	else if (PN == "G4")
		return 392;

	else if (PN == "G#4" || PN == "Ab4")
		return 415;

	else if (PN == "A4")
		return 440;

	else if (PN == "A#4" || PN == "Bb4")
		return 466;

	else if (PN == "B4")
		return 494;

	else if (PN == "C5")
		return 523;

	else if (PN == "C#5" || PN == "Db5")
		return 554;

	else if (PN == "D5")
		return 587;

	else if (PN == "D#5" || PN == "Eb5")
		return 622;

	else if (PN == "E5")
		return 659;

	else if (PN == "F5")
		return 698;

	else if (PN == "F#5" || PN == "Gb5")
		return 740;

	else if (PN == "G5")
		return 784;

	else if (PN == "G#5" || PN == "Ab5")
		return 831;

	else if (PN == "A5")
		return 880;

	else if (PN == "A#5" || PN == "Bb5")
		return 932;

	else if (PN == "B5")
		return 988;

	else if (PN == "C6")
		return 1047;

	else if (PN == "C#6" || PN == "Db6")
		return 1109;

	else if (PN == "D6")
		return 1175;

	else if (PN == "D#6" || PN == "Eb6")
		return 1245;

	else if (PN == "E6")
		return 1319;

	else if (PN == "F6")
		return 1397;

	else if (PN == "F#6" || PN == "Gb6")
		return 1480;

	else if (PN == "G6")
		return 1568;

	else if (PN == "G#6" || PN == "Ab6")
		return 1661;

	else if (PN == "A6")
		return 1760;

	else if (PN == "A#6" || PN == "Bb6")
		return 1865;

	else if (PN == "B6")
		return 1976;

	else if (PN == "C7")
		return 2093;

	else if (PN == "C#7" || PN == "Db7")
		return 2217;

	else if (PN == "D7")
		return 2349;

	else if (PN == "D#7" || PN == "Eb7")
		return 2489;

	else if (PN == "E7")
		return 2637;

	else if (PN == "F7")
		return 2794;

	else if (PN == "F#7" || PN == "Gb7")
		return 2960;

	else if (PN == "G7")
		return 3136;

	else if (PN == "G#7" || PN == "Ab7")
		return 3322;

	else if (PN == "A7")
		return 3520;

	else if (PN == "A#7" || PN == "Bb7")
		return 3729;

	else if (PN == "B7")
		return 3951;

	else if (PN == "C8")
		return 4186;

	else if (PN == "C#8" || PN == "Db8")
		return 4435;

	else if (PN == "D8")
		return 4699;

	else if (PN == "D#8" || PN == "Eb8")
		return 4978;

	else if (PN == "E8")
		return 5274;

	else if (PN == "F8")
		return 5588;

	else if (PN == "F#8" || PN == "Gb8")
		return 5920;

	else if (PN == "G8")
		return 6272;

	else if (PN == "G#8" || PN == "Ab8")
		return 6645;

	else if (PN == "A8")
		return 7040;

	else if (PN == "A#8" || PN == "Bb8")
		return 7459;

	else if (PN == "B8")
		return 7902;
}