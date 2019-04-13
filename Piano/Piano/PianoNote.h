#include <Windows.h>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <thread>

using namespace std;

//Format: vector<DataType> name
//v.push_back() => add an element to the end

class PianoNote
{
public:
	int noteOffsetFromStart;
	int noteFrequency;
	int duration;
};

class Loop
{
public:
	int Start;
	int End;
	int times;
};

void ChangeNotesPerMin(int);
int GetBPM();

int GetLastNote();

void PlayNeededNotes(int);

void PlayNote(int);

void addNote(PianoNote);


void readAndLoad(string);
void loadHelp();