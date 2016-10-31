#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <string.h>
#include <vector>
#include "memblockdevice.h"
#include "node.h"
#include "folder.h"
#include "duallinklist.h"

using namespace std;

class FileSystem {
private:
    MemBlockDevice mMemblockDevice;
    // Here you can add your own data structures
    Folder* root;
	string currentPath;
	DualLinkList<int> freeBlocks;

	int getEmptyBlock();
	void freeBlock(int index);

public:
    FileSystem();
    ~FileSystem();
	string parsePath(string absolute, string relative);
	Node* resolvePath(string path);


    /* These commands needs to implemented
     *
     * However, you are free to change the parameterlist and specify your own returntype for each function below.
     */

    /* This function creates a file in the filesystem */
	int createFile(string path, string content);

    /* Creates a folder in the filesystem */
	int createFolder(string path);

    /* Removes a file in the filesystem */
    // removeFile(...);

    /* Removes a folder in the filesystem */
    // removeFolder(...);

    /* Function will move the current location to a specified location in the filesystem */
	bool goToFolder(string path, string & newPath);

	/* This function will get all the files and folders in the specified folder */
    string listDir(string path);

    /* Add your own member-functions if needed */

	void format();

	bool saveToFile(string filename);
	bool loadFromFile(string filename);
};

#endif // FILESYSTEM_H
