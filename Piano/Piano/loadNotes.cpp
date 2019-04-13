#include "loadNotes.h"

void readAndLoad(string file)
{
	ifstream loadedFile;

	loadedFile.open(file);

	if (!loadedFile.is_open())
		return;

	vector<string> listOfNotes;

	string note;

	string freq;

	string offset;

	PianoNote dynHold;

	while (loadedFile.good())
	{
		getline(loadedFile, note);
		listOfNotes.push_back(note);
	}

	for (unsigned int i = 0; i < listOfNotes.size(); i++)
	{
		int s = 0;
		freq.clear();
		offset.clear();
		note = listOfNotes[i];
		for (int s = 0; note[s] != ' '; s++)
			freq += note[s];
		s++;
		for (int s = 0; s != note.size(); s++)
			offset += note[s];
		dynHold.noteFrequency = (int)strtol(freq.c_str(), NULL, 10);
		dynHold.noteOffsetFromStart = (int)strtol(offset.c_str(), NULL, 10);
		addNote(dynHold);
	}

	return;
}