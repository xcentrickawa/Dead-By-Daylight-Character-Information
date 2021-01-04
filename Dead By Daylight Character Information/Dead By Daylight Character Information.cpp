#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstddef>
using namespace std;

/*
* struct over the data in the Killers.csv file
* includes the name of the killer, whether the killer is owned, whether the killer's adept has been unlocked, the highest winstreak of each killer, and the current winstreak of each killer
*/
struct killer {
	char killer[15];
	char own[5];
	char adept[7];
	int highWin;
	int currWin;
};

/*
* struct over the data in the Killers.csv file
* includes the name of the survivor, whether the killer is owned, whether the killer's adept has been unlock, and the highest and current winstreaks of all survivors
*/
struct survivor {
	char survivor[20];
	char own[5];
	char adept[7];
};

string ctos(char ch[], int maxSize);
void printKill(killer* k[], int killArrCount);
void sortKill(killer* k[], int killArrCount);
void sortKillByHighWin(killer* k[], int killArrCount);
void sortKillByCurrWin(killer* k[], int killArrCount);
void printSurv(survivor* s[], int survArrCount);
void sortSurv(survivor* survArr[], int survArrCount);

int main() {
	//variables for opening the killer file
  	ifstream infile;
	char cNum[20];
	killer killArr[30]; //holds all the data of Killers.csv
	killer* k[30]; //pointer for killArr
	int killArrCount = 0; //counts the number of rows

	//opens the Killers.csv file and loads all of the data into the variables defined in the killer struct
	infile.open("Killers.csv", ios::in); 
	if(infile.is_open()) {
		int c=0;
		while(infile.good()) {
			infile.getline(killArr[c].killer, 256, ',');
			infile.getline(killArr[c].own, 256, ',');
			infile.getline(killArr[c].adept, 256, ',');

			infile.getline(cNum, 256, ',');
			killArr[c].highWin = atoi(cNum);
			infile.getline(cNum, 256, '\n');
			killArr[c].currWin = atoi(cNum);

			c++;
		}
		killArrCount = c;
		infile.close();
	}
	//if the file is never opens, then an error is returned
	else {
		cout << "error opening the killer file" << endl;
	}

	for(int i=0; i < killArrCount; i++) {
		k[i] = &killArr[i];
	}

	//variables for opening the killer file
	ifstream surinfile;
	survivor survArr[30]; //holds all the data of Survivors.csv
	survivor* s[30]; //pointer for survArr
	int survArrCount = 24; //counts the number of survivors

	surinfile.open("Survivors.csv", ios::in);
	if(surinfile.is_open()) {
		int c=0;
		while(c<=survArrCount) {
			surinfile.getline(survArr[c].survivor, 256, ',');
			surinfile.getline(survArr[c].own, 256, ',');
			surinfile.getline(survArr[c].adept, 256, '\n');

			c++;
		}
		surinfile.close();
	}
	//if the file never opens, then the error is printed
	else {
		cout << "error opening the survivor file << endl";
	}

	for(int i=0; i < survArrCount; i++) {
		s[i] = &survArr[i];
	}

	//prints out the killer data
	printKill(k, killArrCount);

	//prints out the survivor data
	printSurv(s, survArrCount);

	//main user interface
	int loopCount=0;
	while (true) {
		string userInput;
		if(loopCount<3) { //gets told of the 'help' command for the first 3 commands
			cout << "\ninsert a command (use the command 'help' for a list of commands) : ";
		} else {
			cout << "\ninsert a command : ";
		}
		cin >> userInput; //collects the user userInput

		//COMMANDS

		//generic help command --- prints a list of all generic commands
		if(userInput == "help") {
			cout << "\nList of commands:\nhelp --- prints a list of generic commands\nkiller.help --- prints all killer commands\nsurvivor.help --- prints all survivor commands\nquit --- quits the program\n" << endl;
		}

		//prints a list of all killer commands
		else if(userInput == "killer.help") {
			cout << "\nList of killer commands:\nkiller.help --- prints all killer commands\nkiller.save --- saves the killer data\nkiller.dataReset --- resets all killer data\nkiller.print --- prints all killer data\nkiller.print(killerName) --- prints the information of a specific killer\nkiller.own(killerName) --- prints whether a specific killer is owned\nkiller.adept(killerName) --- prints whether a killer has adept\nkiller.ownc(killerName) --- changes whether a specific killer is owned\nkiller.owncAll --- makes all killers owned/not owned\nkiller.adeptc(killerName) --- changes whether a specific killer has adept\nkiller.adeptcAll --- makes all killers have/dont have adept\nkiller.currWin(killerName) --- prints the current winstreak of a specific killer\nkiller.currWinAdd(killerName) --- adds 1 win to the current winstreak of a specific killer\nkiller.currWinReset(killerName) --- resets the current winstreak of a specific killer and updates the high winstreak if needed\nkiller.currWinSet(killerName,num) --- set the current winstreak of a specific killer\nkiller.highWin(killerName) --- prints the highest winstreak of a specific killer\nkiller.highWinSet(killerName,num) --- sets the highest winstreak\nkiller.sort --- generic sort of the killer data\nkiller.sort(currWin) --- sorts killer data by current winstreak\nkiller.sort(highWin) --- sorts killer data by highest winstreak\n" << endl;
		}

		//saves all killer data to the Killers.csv sheet
		else if(userInput == "killer.save") {
			sortKill(k, killArrCount);
			ofstream outfile;
			outfile.open("Killers.csv", ios::out | ios::trunc);
			for(int i=0; i<killArrCount; i++) {
				if(i==0) {
					outfile << k[i]->killer << "," << k[i]->own << "," << k[i]->adept << "," << k[i]->highWin << "," << k[i]->currWin;
				} else {
					outfile << "\n" << k[i]->killer << "," << k[i]->own << "," << k[i]->adept << "," << k[i]->highWin << "," << k[i]->currWin;
				}
			}
			outfile.close();
			cout << "\nKILLER DATA SAVED" << endl;
		}

		//resets all killer data to the default values
		else if(userInput == "killer.dataReset") {
			for(int i=0; i<killArrCount; i++) {
				strcpy(k[i]->own, "No");
				strcpy(k[i]->adept, "No");
				k[i]->highWin = 0;
				k[i]->currWin = 0;
			}
			cout << "\nKILLER DATA RESET" << endl;
		}

		//prints all killer data
		else if(userInput == "killer.print") {
			printKill(k, killArrCount);
		}

		//prints the killer data of the specified killer
		else if(userInput.find("killer.print(") != string::npos) {
			string killerName = userInput.substr(13, userInput.length()-14);
			int killerNum=-1;
			for(int i=0; i<killArrCount; i++) {
				//converts k[i]->killer to a string
				string kCharToString = ctos(k[i]->killer, 15);
				//gets the information of the specified killer
				if(kCharToString.find(killerName) != string::npos) {
					killerNum=i;
				}
			}
			//makes sure that the killer mentioned in the command is an actual killer
			if(killerNum != -1) {
				cout << "\nKiller: " << k[killerNum]->killer << ", own: " << k[killerNum]->own << ", adept: " << k[killerNum]->adept << ", highest winstreak: " << k[killerNum]->highWin << ", current winstreak: " << k[killerNum]->currWin << endl;
			} else {
				cout << "\n'" << killerName << "' is not a recognized killer (Make sure to use correct capitalization!)" << endl; 
			}
		}

		//prints whether a specified killer is owned
		else if(userInput.find("killer.own(") != string::npos) {
			string killerName = userInput.substr(11, userInput.length()-12);
			string killerOwn;
			for(int i=0; i<killArrCount; i++) { 
				//converts k[i]->killer to a string
				string kCharToString = ctos(k[i]->killer, 15);
				//gets the information of the specified killer
				if(kCharToString.find(killerName) != string::npos) {
					killerOwn = ctos(k[i]->own, 5);
					i = killArrCount;
				}
			}
			//makes sure that the killer mentioned in the command is an actual killer
			if(killerOwn != "") {
				cout << "\n" << killerName << " - Own: " << killerOwn << endl; 
			} else {
				cout << "\n'" << killerName << "' is not a recognized killer (Make sure to use correct capitalization!)" << endl; 
			}
		}

		//prints whether a killer has adept
		else if(userInput.find("killer.adept(") != string::npos) {
			string killerName = userInput.substr(13, userInput.length()-14);
			string killerAdept;
			for(int i=0; i<killArrCount; i++) {
				//converts k[i]->killer to a string
				string kCharToString = ctos(k[i]->killer, 15);
				//gets the information of the specified killer
				if(kCharToString.find(killerName) != string::npos) {
					killerAdept = ctos(k[i]->adept, 7);
					i = killArrCount;
				}
			}
			//makes sure that the killer mentioned in the command is an actual killer
			if(killerAdept != "") {
				cout << "\n" << killerName << " - Adept: " << killerAdept << endl;
			} else {
				cout << "\n'" << killerName << "' is not a recognized killer (Make sure to use correct capitalization!)" << endl;
			}
		}

		//changes whether a specific killer is owned
		else if(userInput.find("killer.ownc(") != string::npos) {
			string killerName = userInput.substr(12, userInput.length()-13);
			string killerOwn;
			string killerAdept;
			for(int i=0; i<killArrCount; i++) { 
				//converts k[i]->killer to a string
				string kCharToString = ctos(k[i]->killer, 15);
				//gets the information of the specified killer and swaps it
				if(kCharToString.find(killerName) != string::npos) {
					killerOwn = ctos(k[i]->own, 5);
					killerAdept = ctos(k[i]->adept, 7);
					if(killerOwn.find("No") != string::npos) {
						killerOwn = "Yes";
						strcpy(k[i]->own, "Yes");
					} else {
						killerOwn = "No";
						strcpy(k[i]->own, "No");
						if(killerAdept.find("Yes") != string::npos) {
							killerAdept = "No";
							strcpy(k[i]->adept, "No");
						}
					}
					i = killArrCount;
				}
			}
			//makes sure that the killer mentioned in the command is an actual killer
			if(killerOwn != "") {
				cout << "\n" << killerName << "'s owned value has been set to " << killerOwn << endl; 
				cout << killerName << " - Own: " << killerOwn << endl; 
			} else {
				cout << "\n'" << killerName << "' is not a recognized killer (Make sure to use correct capitalization!)" << endl; 
			}
		}

		//changes whether a specific killer has adept
		else if(userInput.find("killer.adeptc(") != string::npos) {
			string killerName = userInput.substr(14, userInput.length()-15);
			string killerAdept;
			for(int i=0; i<killArrCount; i++) { 
				//converts k[i]->killer to a string
				string kCharToString = ctos(k[i]->killer, 15);
				//gets the information of the specified killer and swaps it
				if(kCharToString.find(killerName) != string::npos) {
					killerAdept = ctos(k[i]->adept, 5);
					if(killerAdept.find("No") != string::npos) {
						killerAdept = "Yes";
						strcpy(k[i]->adept, "Yes");
					} else {
						killerAdept = "No";
						strcpy(k[i]->adept, "No");
					}
					i = killArrCount;
				}
			}
			//makes sure that the killer mentioned in the command is an actual killer
			if(killerAdept != "") {
				cout << "\nThe adept for " << killerName << " has changed to " << killerAdept << endl;
				cout << killerName << " - Adept: " << killerAdept << endl; 
			} else {
				cout << "\n'" << killerName << "' is not a recognized killer (Make sure to use correct capitalization!)" << endl; 
			}
		}

		//makes all killers owned/not owned
		else if(userInput == "killer.owncAll") {
			int noCheck=0;
			for(int i=0; i<killArrCount; i++) {
				string kCharToString = ctos(k[i]->own, 5);
				if(kCharToString.find("No") != string::npos) {
					noCheck = 1;
				}
			}
			if(noCheck > 0) {
				for(int i=0; i<killArrCount; i++) {
					string kCharToString = ctos(k[i]->own, 5);
					if(kCharToString.find("No") != string::npos) {
						strcpy(k[i]->own, "Yes");
					}
				}
				cout << "\nAll killer's owned values were changed to 'Yes'" << endl;
			} else {
				for(int i=0; i<killArrCount; i++) {
					string kCharToString = ctos(k[i]->own, 5);
					string adeptCharToString = ctos(k[i]->adept, 7);
					if(kCharToString.find("Yes") != string::npos) {
						strcpy(k[i]->own, "No");
					} if(adeptCharToString.find("Yes") != string::npos) {
						strcpy(k[i]->adept, "No");
					}
				}
				cout << "\nAll killer's owned values were changed to 'No'" << endl;
			}
		}

		//makes all killers have adept and owned if they have adept
		else if(userInput == "killer.adeptcAll") {
			int noCheck=0;
			for(int i=0; i<killArrCount; i++) {
				string kCharToString = ctos(k[i]->adept, 7);
				if(kCharToString.find("No") != string::npos) {
					noCheck = 1;
				}
			}
			if(noCheck > 0) {
				for(int i=0; i<killArrCount; i++) {
					string kCharToString = ctos(k[i]->adept, 7);
					string ownCharToString = ctos(k[i]->own, 5);
					if(kCharToString.find("No") != string::npos) {
						strcpy(k[i]->adept, "Yes");
					} 
					if(ownCharToString.find("No") != string::npos) {
						strcpy(k[i]->own, "Yes");
					}
				}
				cout << "\nAll killer's adept values were changed to 'Yes'" << endl;
			} else {
				for(int i=0; i<killArrCount; i++) {
					string kCharToString = ctos(k[i]->adept, 7);
					if(kCharToString.find("Yes") != string::npos) {
						strcpy(k[i]->adept, "No");
					} 
				}
				cout << "\nAll killer's adept values were changed to 'No'" << endl;
			}
		}

		//prints the current winstreak of the specific killer
		else if(userInput.find("killer.currWin(") != string::npos) {
			string killerName = userInput.substr(15, userInput.length()-16);
			int killerCurrWin=-1;
			for(int i=0; i<killArrCount; i++) {
				//converts k[i]->killer to a string
				string kCharToString = ctos(k[i]->killer, 15);
				//gets and modifies the information of the specified killer
				if(kCharToString.find(killerName) != string::npos) {
					killerCurrWin = k[i]->currWin;
					i=killArrCount;
				}
			}
			//makes sure that the killer mentioned in the command is an actual killer
			if(killerCurrWin!=-1) {
				cout << "\n" << killerName << " - Current Winstreak: " << killerCurrWin << endl; 
			} else {
				cout << "\n'" << killerName << "' is not a recognized killer (Make sure to use correct capitalization!)" << endl; 
			}
		}

		//adds 1 win to the current winstreak of the specified killer
		else if(userInput.find("killer.currWinAdd(") != string::npos) {
			string killerName = userInput.substr(18, userInput.length()-19);
			int killCheck=0;
			int killCurrWin=0;
			for(int i=0; i<killArrCount; i++) {
				//converts k[i]->killer to a string
				string kCharToString = ctos(k[i]->killer, 15);
				//gets and modifies the information of the specified killer
				if(kCharToString.find(killerName) != string::npos) {
					k[i]->currWin = k[i]->currWin+1;
					killCurrWin = k[i]->currWin;
					killCheck = 1;
					i=killArrCount;
				}
			}
			//makes sure that the killer mentioned in the command is an actual killer
			if(killCheck > 0) {
				cout << "\n" << killerName << " - Current Winstreak: " << killCurrWin << endl; 
			} else {
				cout << "\n'" << killerName << "' is not a recognized killer (Make sure to use correct capitalization!)" << endl; 
			}
		}

		//resets the current winstreak of a specific killer
		else if(userInput.find("killer.currWinReset(") != string::npos) {
			string killerName = userInput.substr(20, userInput.length()-21);
			int killCheck=0;
			int killCurrWin=0;
			for(int i=0; i<killArrCount; i++) {
				//converts k[i]->killer to a string
				string kCharToString = ctos(k[i]->killer, 15);
				//gets and modifies the information of the specified killer
				if(kCharToString.find(killerName) != string::npos) {
					killCurrWin = k[i]->currWin;
					k[i]->currWin = 0;
					killCheck = 1;
					if(killCurrWin > k[i]->highWin) {
						k[i]->highWin = killCurrWin;
					}
					killCurrWin = 0;
				}
			}
			//makes sure that the killer mentioned in the command is an actual killer
			if(killCheck > 0) {
				cout << "\n" << killerName << " - Current Winstreak: " << killCurrWin << endl; 
			} else {
				cout << "\n'" << killerName << "' is not a recognized killer (Make sure to use correct capitalization!)" << endl; 
			}
		}

		//sets the current winstreak of a specific killer
		else if(userInput.find("killer.currWinSet(") != string::npos) {
			int findComma = userInput.find_first_of(',');
			string killerName = userInput.substr(18, (findComma-18));
			string killCurrWinString = userInput.substr(findComma+1, (userInput.length()-findComma-2));
			int killCheck=0;
			stringstream stringToInt(killCurrWinString);
			int killCurrWin = 0;
			stringToInt >> killCurrWin;
			for(int i=0; i<killArrCount; i++) {
				//converts k[i]->killer to a string
				string kCharToString = ctos(k[i]->killer, 15);
				//gets and modifies the information of the specified killer
				if(kCharToString.find(killerName) != string::npos) {
					k[i]->currWin = killCurrWin;
					killCheck = 1;
				}
			}
			//makes sure that the killer mentioned in the command is an actual killer
			if(killCheck > 0) {
				cout << "\n" << killerName << " - Current Winstreak: " << killCurrWin << endl; 
			} else {
				cout << "\n'" << killerName << "' is not a recognized killer (Make sure to use correct capitalization!)" << endl; 
			}
		}

		//prints the highest winstreak of a specific killer
		else if(userInput.find("killer.highWin(") != string::npos) {
			string killerName = userInput.substr(15, userInput.length()-16);
			int killerHighWin=-1;
			for(int i=0; i<killArrCount; i++) {
				//converts k[i]->killer to a string
				string kCharToString = ctos(k[i]->killer, 15);
				//gets and modifies the information of the specified killer
				if(kCharToString.find(killerName) != string::npos) {
					killerHighWin = k[i]->highWin;
					i=killArrCount;
				}
			}
			//makes sure that the killer mentioned in the command is an actual killer
			if(killerHighWin!=-1) {
				cout << "\n" << killerName << " - Highest Winstreak: " << killerHighWin << endl; 
			} else {
				cout << "\n'" << killerName << "' is not a recognized killer (Make sure to use correct capitalization!)" << endl; 
			}
		}

		//sets the highest winstreak of a specific killer
		else if(userInput.find("killer.highWinSet(") != string::npos) {
			int findComma = userInput.find_first_of(',');
			string killerName = userInput.substr(18, (findComma-18));
			string killHighWinString = userInput.substr(findComma+1, (userInput.length()-findComma-2));
			int killCheck=0;
			stringstream stringToInt(killHighWinString);
			int killHighWin = 0;
			stringToInt >> killHighWin;
			for(int i=0; i<killArrCount; i++) {
				//converts k[i]->killer to a string
				string kCharToString = ctos(k[i]->killer, 15);
				//gets and modifies the information of the specified killer
				if(kCharToString.find(killerName) != string::npos) {
					k[i]->highWin = killHighWin;
					killCheck = 1;
				}
			}
			//makes sure that the killer mentioned in the command is an actual killer
			if(killCheck > 0) {
				cout << "\n" << killerName << " - Highest Winstreak: " << killHighWin << endl; 
			} else {
				cout << "\n'" << killerName << "' is not a recognized killer (Make sure to use correct capitalization!)" << endl; 
			}
		}

		//generic sort of the killer data
		else if(userInput == "killer.sort") {
			sortKill(k, killArrCount);
			cout << "\nkiller data sorted" << endl;
		}

		//sorts killer data - current winstreak -> alphabetical order
		else if(userInput == "killer.sort(currWin)") {
			sortKillByCurrWin(k, killArrCount);
			cout << "\nkiller data sorted" << endl;
		}

		//sorts the killer data - highest winstreak -> alphabetical order
		else if(userInput == "killer.sort(highWin)") {
			sortKillByHighWin(k, killArrCount);
			cout << "\nkiller data sorted" << endl;
		}
		
		//prints out a list of all survivor commands
		else if(userInput == "survivor.help") {
			cout << "\nList of survivor commands:\nsurvivor.help --- prints a list of all survivor commands\nsurvivor.save --- saves the survivor data\nsurvivor.dataReset --- resets the survivor data\nsurvivor.print --- prints the survivor data\nsurvivor.print(survivorName) --- prints the data of the specified survivor\nsurvivor.own(survivorName) --- prints whether a survivor is owned\nsurvivor.ownc(survivorName) --- changes whether a specified survivor is owned\nsurvivor.owncAll --- makes all survivors owned/not owned\nsurvivor.adept(survivorName) --- prints whether a survivor has adept\nsurvivor.adeptc(survivorName) --- changes whether a specified survivor has adept\nsurvivor.adeptcAll --- makes all survivors have adept/dont have adept\nsurvivor.currWin --- prints the current winstreak of survivors\nsurvivor.highWin --- prints the highest winstreak of survivors" << endl;
		}

		//saves the survivor data
		else if(userInput == "survivor.save") {
			ofstream survoutfile;
			survoutfile.open("Survivors.csv", ios::out | ios::trunc);
			for(int i=0; i < survArrCount; i++) {
				if(i==0) {
					survoutfile << s[i]->survivor << "," << s[i]->own << "," << s[i]->adept;
				} else {
					survoutfile << "\n" << s[i]->survivor << "," << s[i]->own << "," << s[i]->adept;
				}
			}
			survoutfile.close();
			cout << "\nSURVIVOR DATA SAVED" << endl;
		}

		//resets the survivor data
		else if(userInput == "survivor.dataReset") {
			for(int i=0; i<survArrCount; i++) {
				strcpy(s[i]->own, "No");
				strcpy(s[i]->adept, "No");
			}
			cout << "\nSURVIVOR DATA RESET" << endl;
		}

		//prints out survivor data
		else if(userInput == "survivor.print") {
			printSurv(s, survArrCount);
		}

		//prints out the data of the specified survivor
		else if(userInput.find("survivor.print(") != string::npos) {
			string survName = userInput.substr(15, userInput.length()-16);
			int survivorNum=-1;
			for(int i=0; i<survArrCount; i++) {
				string survstr = ctos(s[i]->survivor, 30);
				if(survstr.find(survName) != string::npos) {
					survivorNum=i;
					i=survArrCount;
				}
			}
			//checks to make sure the specified survivor actually exists
			if(survivorNum != -1) {
				cout << "\nSurvivor: " << s[survivorNum]->survivor << ", owned: " << s[survivorNum]->own << ", adept: " << s[survivorNum]->adept << endl;
			} else {
				cout << "\n'" << survName << "' is not a recognized survivor (Make sure to use correct capitalization!)" << endl;
			}
		}

		//prints whether a specified survivor is owned
		else if(userInput.find("survivor.own(") != string::npos) {
			string survName = userInput.substr(13, userInput.length()-14);
			string survOwn;
			for(int i=0; i<survArrCount; i++) { 
				//converts s[i]->survivor to a string
				string survstr = ctos(s[i]->survivor, 30);
				//gets the information of the specified survivor
				if(survstr.find(survName) != string::npos) {
					survOwn = ctos(s[i]->own, 5);
					i = survArrCount;
				}
			}
			//makes sure that the survivor mentioned in the command is an actual survivor
			if(survOwn != "") {
				cout << "\n" << survName << " - Own: " << survOwn << endl; 
			} else {
				cout << "\n'" << survName << "' is not a recognized survivor (Make sure to use correct capitalization!)" << endl; 
			}
		}

		//prints whether a survivor has adept
		else if(userInput.find("survivor.adept(") != string::npos) {
			string survName = userInput.substr(15, userInput.length()-16);
			string survAdept;
			for(int i=0; i<survArrCount; i++) {
				//converts s[i]->survivor to a string
				string survstr = ctos(s[i]->survivor, 30);
				//gets the information of the specified survivor
				if(survstr.find(survName) != string::npos) {
					survAdept = ctos(s[i]->adept, 7);
					i = survArrCount;
				}
			}
			//makes sure that the survivor mentioned in the command is an actual survivor
			if(survAdept != "") {
				cout << "\n" << survName << " - Adept: " << survAdept << endl;
			} else {
				cout << "\n'" << survName << "' is not a recognized survivor (Make sure to use correct capitalization!)" << endl;
			}
		}

		//changes whether a specific survivor is owned
		else if(userInput.find("survivor.ownc(") != string::npos) {
			string survName = userInput.substr(14, userInput.length()-15);
			string survOwn;
			string survAdept;
			for(int i=0; i<survArrCount; i++) { 
				//converts s[i]->survivor to a string
				string survstr = ctos(s[i]->survivor, 30);
				//gets the information of the specified survivor and swaps it
				if(survstr.find(survName) != string::npos) {
					survOwn = ctos(s[i]->own, 5);
					survAdept = ctos(s[i]->adept, 7);
					if(survOwn.find("No") != string::npos) {
						survOwn = "Yes";
						strcpy(s[i]->own, "Yes");
					} else {
						survOwn = "No";
						strcpy(s[i]->own, "No");
						if(survAdept.find("Yes") != string::npos) {
							survAdept = "No";
							strcpy(s[i]->adept, "No");
						}
					}
					i = survArrCount;
				}
			}
			//makes sure that the survivor mentioned in the command is an actual survivor
			if(survOwn != "") {
				cout << "\n" << survName << "'s owned value has been set to " << survOwn << endl; 
				cout << survName << " - Own: " << survOwn << endl; 
			} else {
				cout << "\n'" << survName << "' is not a recognized survivor (Make sure to use correct capitalization!)" << endl; 
			}
		}

		//changes whether a specific survivor has adept
		else if(userInput.find("survivor.adeptc(") != string::npos) {
			string survName = userInput.substr(16, userInput.length()-17);
			string survAdept;
			for(int i=0; i<survArrCount; i++) { 
				//converts s[i]->survivor to a string
				string survstring = ctos(s[i]->survivor, 30);
				//gets the information of the specified survivor and swaps it
				if(survstring.find(survName) != string::npos) {
					survAdept = ctos(s[i]->adept, 5);
					if(survAdept.find("No") != string::npos) {
						survAdept = "Yes";
						strcpy(s[i]->adept, "Yes");
					} else {
						survAdept = "No";
						strcpy(s[i]->adept, "No");
					}
					i = survArrCount;
				}
			}
			//makes sure that the survivor mentioned in the command is an actual survivor
			if(survAdept != "") {
				cout << "\nThe adept for " << survName << " has changed to " << survAdept << endl;
				cout << survName << " - Adept: " << survAdept << endl; 
			} else {
				cout << "\n'" << survName << "' is not a recognized survivor (Make sure to use correct capitalization!)" << endl; 
			}
		}

		//makes all survivors owned/not owned
		else if(userInput == "survivor.owncAll") {
			int noCheck=0;
			for(int i=0; i<survArrCount; i++) {
				string survstr = ctos(s[i]->own, 5);
				if(survstr.find("No") != string::npos) {
					noCheck = 1;
				}
			}
			if(noCheck > 0) {
				for(int i=0; i<survArrCount; i++) {
					string survstr = ctos(s[i]->own, 5);
					if(survstr.find("No") != string::npos) {
						strcpy(s[i]->own, "Yes");
					}
				}
				cout << "\nAll survivors' owned values were changed to 'Yes'" << endl;
			} else {
				for(int i=0; i<survArrCount; i++) {
					string survstr = ctos(s[i]->own, 5);
					string adeptCharToString = ctos(s[i]->adept, 7);
					if(survstr.find("Yes") != string::npos) {
						strcpy(s[i]->own, "No");
					} if(adeptCharToString.find("Yes") != string::npos) {
						strcpy(s[i]->adept, "No");
					}
				}
				cout << "\nAll survivors' owned values were changed to 'No'" << endl;
			}
		}

		//makes all survivors have adept and owned if they have adept
		else if(userInput == "survivor.adeptcAll") {
			int noCheck=0;
			for(int i=0; i<survArrCount; i++) {
				string survstr = ctos(s[i]->adept, 7);
				if(survstr.find("No") != string::npos) {
					noCheck = 1;
				}
			}
			if(noCheck > 0) {
				for(int i=0; i<survArrCount; i++) {
					string survstr = ctos(s[i]->adept, 7);
					string ownCharToString = ctos(s[i]->own, 5);
					if(survstr.find("No") != string::npos) {
						strcpy(s[i]->adept, "Yes");
					} 
					if(ownCharToString.find("No") != string::npos) {
						strcpy(s[i]->own, "Yes");
					}
				}
				cout << "\nAll survivors' adept values were changed to 'Yes'" << endl;
			} else {
				for(int i=0; i<survArrCount; i++) {
					string survstr = ctos(s[i]->adept, 7);
					if(survstr.find("Yes") != string::npos) {
						strcpy(s[i]->adept, "No");
					} 
				}
				cout << "\nAll survivors' adept values were changed to 'No'" << endl;
			}
		}

		//breaks out of the while loop, ending user input
		else if(userInput == "quit") {
			break;
		}

		//command not recognized
		else {
			cout << "\n'" << userInput << "' is not a known command. Use the command 'help' for a list of commands" << endl;
		}
		
		loopCount = loopCount+1;
	}
}

/*
* converts a char array to a string
*/ 
string ctos(char ch[], int maxSize) {
	string charToString;
	for(int j=0; j<maxSize; j++) {
		charToString = charToString + ch[j];
		if(ch[j] == NULL) {
			j=maxSize;
		}
	}
	return charToString;
}

/*
* prints out the killArr
*/
void printKill(killer* k[], int killArrCount) {
	cout << "\nkiller, own, adept, highest winstreak, current winstreak" << endl;
	for(int i=0; i<killArrCount; i++) {
		cout << k[i]->killer << ", " << k[i]->own << ", " << k[i]->adept << ", " << k[i]->highWin << ", " << k[i]->currWin << endl;
	}
}

/*
* sorts the killArr 
* whether the killer is owned -> whether it has adept -> alphabetical order
*/
void sortKill(killer* k[], int killArrCount) {
	//sort alphabetically
	for(int i=0; i < killArrCount; i++) {
		for(int j=i+1; j < killArrCount; j++) {
			string killeri = ctos(k[i]->killer, 15);
			string killerj = ctos(k[j]->killer, 15);
			if(killeri > killerj) {
				swap(k[i], k[j]);
			}
		}
	}

	//sort owned
	for(int i=0; i < killArrCount; i++) {
		for(int j=i+1; j < killArrCount; j++) {
			string killeri = ctos(k[i]->own, 5);
			string killerj = ctos(k[j]->own, 5);
			if(killeri < killerj) {
				swap(k[i], k[j]);
			}
		}
	}

	//sort adept
	for(int i=0; i < killArrCount; i++) {
		for(int j=i+1; j < killArrCount; j++) {
			string killeri = ctos(k[i]->adept, 5);
			string killerj = ctos(k[j]->adept, 5);
			if(killeri < killerj) {
				swap(k[i], k[j]);
			}
		}
	}
}

/*
* sorts killArr
* highest winstreak -> alphabetical order
*/
void sortKillByHighWin(killer* k[], int killArrCount) {
	//sort alphabetically
	for(int i=0; i < killArrCount; i++) {
		for(int j=i+1; j < killArrCount; j++) {
			string killeri = ctos(k[i]->killer, 15);
			string killerj = ctos(k[j]->killer, 15);
			if(killeri > killerj) {
				swap(k[i], k[j]);
			}
		}
	}

	//sort for highest winstreak
	for(int i=0; i < killArrCount; i++) {
		for(int j=i; j < killArrCount; j++) {
			if(k[i]->highWin < k[j]->highWin) {
				swap(k[i], k[j]);
			}
		}
	}
}

/*
* sorts killArr
* current winstreak -> alphabetical order
*/
void sortKillByCurrWin(killer* k[], int killArrCount) {
	//sort alphabetically
	for(int i=0; i < killArrCount; i++) {
		for(int j=i+1; j < killArrCount; j++) {
			string killeri = ctos(k[i]->killer, 15);
			string killerj = ctos(k[j]->killer, 15);
			if(killeri > killerj) {
				swap(k[i], k[j]);
			}
		}
	}

	//sort for current winstreak
	for(int i=0; i < killArrCount; i++) {
		for(int j=i; j < killArrCount; j++) {
			if(k[i]->currWin < k[j]->currWin) {
				swap(k[i], k[j]);
			}
		}
	}
}

/*
* prints out the survArr
*/
void printSurv(survivor* s[], int survArrCount) {
	cout << "\nsurvivor, own, adept" << endl;
	for(int i=0; i<survArrCount; i++) {
		cout << s[i]->survivor << ", " << s[i]->own << ", " << s[i]->adept << endl;
	}
}
