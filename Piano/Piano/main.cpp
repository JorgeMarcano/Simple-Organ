#include "PianoNote.h"

int currentNote = 0;

int noteLimit = 0;

int currentTime = GetTickCount();

int lastTime = GetTickCount();

int timesLoop = 0;

bool pause = false;
bool prevKeyState = true;

string filename;

string notespermin;
int notesPerMin = 0;
int durationOfNote = 0;

void checkToPause()
{
	while (1)
	{
		if (GetAsyncKeyState(VK_F1) && prevKeyState == false)
			pause = !pause;

		if (GetAsyncKeyState(VK_ESCAPE))
			exit(0);

		prevKeyState = GetAsyncKeyState(VK_F1);
	}
}

int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		cout << "partition name: ";
		getline(cin, filename);
	}
	else if (argc > 1)
	{
		filename = argv[1];
	}

	if (filename == "help.txt")
	{
		loadHelp();
		system("pause");
		exit(0);
	}
	readAndLoad(filename);

	notesPerMin = GetBPM();
	string defaultBPM;
	if (notesPerMin)
		defaultBPM = " (" + to_string(notesPerMin) + ") ";
	else
		defaultBPM.clear();

	cout << "beats per min" << defaultBPM << ": ";
	getline(cin, notespermin);
	if (notespermin != "")
	{
		notesPerMin = (int)strtol(notespermin.c_str(), NULL, 10);
		ChangeNotesPerMin(notesPerMin);
	}
	else if (notespermin == "" && defaultBPM == "")
	{
		cout << "error: invalid BPM" << endl;
		system("pause");
		exit(0);
	}
	durationOfNote = 60000 / notesPerMin;

	noteLimit = GetLastNote();

	currentTime = GetTickCount();
	lastTime = GetTickCount();

	thread PauseThread(checkToPause); //starts running

	while (1)
	{
		if (currentTime - lastTime >= durationOfNote && pause == false)
		{
			lastTime = currentTime;

			PlayNeededNotes(currentNote);

			currentNote += 1;
			if (currentNote > noteLimit)
				currentNote = 0;
		}
		currentTime = GetTickCount();
	}

	return 1;
}