#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <string.h>
#include <vector>
#include "memblockdevice.h"
#include "node.h"
#include "folder.h"

using namespace std;

class FileSystem {
private:
    MemBlockDevice mMemblockDevice;
    // Here you can add your own data structures
    Folder* root;
	Node* resolvePath(string path);

public:
    FileSystem();
    ~FileSystem();
	string parsePath(string wd, string path);


    /* These commands needs to implemented
     *
     * However, you are free to change the parameterlist and specify your own returntype for each function below.
     */

    /* This function creates a file in the filesystem */
    // createFile(...)

    /* Creates a folder in the filesystem */
    bool createFolder(string path, string name);

    /* Removes a file in the filesystem */
    // removeFile(...);

    /* Removes a folder in the filesystem */
    // removeFolder(...);

    /* Function will move the current location to a specified location in the filesystem */
    // goToFolder(...);

    /* This function will get all the files and folders in the specified folder */
    string listDir(string path);

    /* Add your own member-functions if needed */

	void format();

	bool saveToFile(string filename);
	bool loadFromFile(string filename);
};

#endif // FILESYSTEM_H
