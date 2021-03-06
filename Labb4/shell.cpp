#include <iostream>
#include <sstream>
#include "filesystem.h"

const int MAXCOMMANDS = 8;
const int NUMAVAILABLECOMMANDS = 15;

std::string availableCommands[NUMAVAILABLECOMMANDS] = {
	"quit","format","ls","create","cat","createImage","restoreImage",
	"rm","cp","append","mv","mkdir","cd","pwd","help"
};

/* Takes usercommand from input and returns number of commands, commands are stored in strArr[] */
int parseCommandString(const std::string &userCommand, std::string strArr[]);
int findCommand(std::string &command);
std::string help();

int main(void) {
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	FileSystem fs;

	std::string userCommand, commandArr[MAXCOMMANDS];
	std::string user = "user@DV1492";    // Change this if you want another user to be displayed
	std::string currentDir = "/";    // current directory, used for output

	bool bRun = true;

	do {
		std::cout << user << ":" << currentDir << "$ ";
		getline(std::cin, userCommand);

		int nrOfCommands = parseCommandString(userCommand, commandArr);
		if (nrOfCommands > 0) {

			int cIndex = findCommand(commandArr[0]);
			switch (cIndex) {

			case 0: // quit
				bRun = false;
				std::cout << "Exiting\n";
				break;
			case 1: // format
				fs.format();
				std::cout << "Disk formatted." << std::endl;
				break;
			case 2: // ls
				std::cout << "Listing directory" << std::endl;
				std::cout << fs.listDir(nrOfCommands > 0 ? commandArr[1] : "");
				break;
			case 3: // create
				if (nrOfCommands > 2)
				{
					// -1 parent folder doesnt exist, -2 name already in use, -3 name too long, -4 content to big
					switch (fs.createFile(fs.parsePath(currentDir, commandArr[1]), commandArr[2]))
					{
					case 0:
						std::cout << "File created." << std::endl;
						break;
					case -1:
						std::cout << "Parent folder doesnt exist." << std::endl;
						break;
					case -2:
						std::cout << "Name conflict in parent folder." << std::endl;
						break;
					case -3:
						std::cout << "Name too long." << std::endl;
						break;
					case -4:
						std::cout << "Content too big." << std::endl;
						break;
					default:
						std::cout << "undefine return value" << std::endl;
						break;
					}

				}
				break;
			case 4: // cat
				if (nrOfCommands > 1)
				{
					/*File* file = dynamic_cast<File*>(fs.resolvePath(currentDir, commandArr[1]));
					std::cout << "Saving image to file: " << commandArr[1] << endl;
					fs.saveToFile(commandArr[1]);*/
				}
				break;
			case 5: // createImage
				if (nrOfCommands > 1)
				{
					std::cout << "Saving image to file: " << commandArr[1] << endl;
					fs.saveToFile(commandArr[1]);
				}
				break;
			case 6: // restoreImage
				if (nrOfCommands > 1)
				{
					std::cout << "Saving image to file: " << commandArr[1] << endl;
					fs.loadFromFile(commandArr[1]);
				}
				break;
			case 7: // rm
				break;
			case 8: // cp
				break;
			case 9: // append
				break;
			case 10: // mv
				break;
			case 11: // mkdir
				if (nrOfCommands > 1)
				{
					// -1 parent folder doesnt exist, -2 name already in use, -3 name too long
					switch (fs.createFolder(commandArr[1]))
					{
					case 0:
						std::cout << "Folder created." << std::endl;
						break;
					case -1:
						std::cout << "Parent folder doesnt exist." << std::endl;
						break;
					case -2:
						std::cout << "Name conflict in parent folder." << std::endl;
						break;
					case -3:
						std::cout << "Name too long." << std::endl;
						break;
					default:
						std::cout << "undefine return value" << std::endl;
						break;
					}
					
				}
				break;
			case 12: // cd
				if (nrOfCommands > 1)
				{
					string newPath;
					if (fs.goToFolder(commandArr[1], newPath))
					{
						currentDir = newPath;
					}
					else
					{
						std::cout << "Could not find the folder." << std::endl;
					}
				}
				break;
			case 13: // pwd
				std::cout << currentDir << std::endl;
				break;
			case 14: // help
				std::cout << help() << std::endl;
				break;
			default:
				std::cout << "Unknown command: " << commandArr[0] << std::endl;
			}
		}
	} while (bRun == true);

	return 0;
}

int parseCommandString(const std::string &userCommand, std::string strArr[]) {
	std::stringstream ssin(userCommand);
	int counter = 0;
	while (ssin.good() && counter < MAXCOMMANDS) {
		ssin >> strArr[counter];
		counter++;
	}
	if (strArr[0] == "") {
		counter = 0;
	}
	return counter;
}
int findCommand(std::string &command) {
	int index = -1;
	for (int i = 0; i < NUMAVAILABLECOMMANDS && index == -1; ++i) {
		if (command == availableCommands[i]) {
			index = i;
		}
	}
	return index;
}

std::string help() {
	std::string helpStr;
	helpStr += "OSD Disk Tool .oO Help Screen Oo.\n";
	helpStr += "-----------------------------------------------------------------------------------\n";
	helpStr += "* quit:                             Quit OSD Disk Tool\n";
	helpStr += "* format;                           Formats disk\n";
	helpStr += "* ls     <path>:                    Lists contents of <path>.\n";
	helpStr += "* create <path>:                    Creates a file and stores contents in <path>\n";
	helpStr += "* cat    <path>:                    Dumps contents of <file>.\n";
	helpStr += "* createImage  <real-file>:         Saves disk to <real-file>\n";
	helpStr += "* restoreImage <real-file>:         Reads <real-file> onto disk\n";
	helpStr += "* rm     <file>:                    Removes <file>\n";
	helpStr += "* cp     <source> <destination>:    Copy <source> to <destination>\n";
	helpStr += "* append <source> <destination>:    Appends contents of <source> to <destination>\n";
	helpStr += "* mv     <old-file> <new-file>:     Renames <old-file> to <new-file>\n";
	helpStr += "* mkdir  <directory>:               Creates a new directory called <directory>\n";
	helpStr += "* cd     <directory>:               Changes current working directory to <directory>\n";
	helpStr += "* pwd:                              Get current working directory\n";
	helpStr += "* help:                             Prints this help screen\n";
	return helpStr;
}
