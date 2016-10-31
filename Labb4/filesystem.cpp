#include "filesystem.h"

#include <sstream>
#include <vector>
#include <fstream>
#include "file.h"

FileSystem::FileSystem()
{
	this->currentPath = "/";
	this->root = new Folder("");

	int size = this->mMemblockDevice.size();
	for (int i = size - 1; i > 1; i--)
	{
		this->freeBlocks.push(i);
	}
}

FileSystem::~FileSystem()
{
	delete root;
}

string FileSystem::parsePath(string absolute, string relative)
{
	string output = "";
	istringstream path;
	vector<string> list;
	string field;


	if (relative.find('/') == 0) {
		path.str(relative);
	}
	else {
		path.str(absolute + '/' + relative);
	}

	while (getline(path, field, '/')) {
		list.push_back(field);
	}

	for (int i = 0; i < list.size(); i++)
	{
		if (list.at(i) == "" || list.at(i) == ".")
		{
			list.erase(list.begin() + i--);
		}
		else if (list.at(i) == "..")
		{
			if (i > 0)
			{
				list.erase(list.begin() + i--);
			}
			list.erase(list.begin() + i--);
		}
	}

	if (list.size() > 0)
	{
		for (string str : list)
		{
			output += "/" + str;
		}
	}
	else
	{
		output = "/";
	}

	return output;
}

Node* FileSystem::resolvePath(string path) {
	Node* output = nullptr;
	Node* child = root;

	istringstream sspath(path);
	string field;
	getline(sspath, field, '/');

	while (child != nullptr && getline(sspath, field, '/')) {
		child = dynamic_cast<Folder*>(child)->getChild(field);
	}

	output = child;

	return output;
}

int FileSystem::createFile(string path, string content)
{
	int output = 0; // -1 parent folder doesnt exist, -2 name already in use, -3 name too long, -4 content to big

	string absPath = this->parsePath(this->currentPath, path);
	int lastSlash = absPath.find_last_of('/');
	string parentPath = absPath.substr(0, lastSlash);
	string name = path.substr(lastSlash + 1);

	Folder* dir = dynamic_cast<Folder*>(this->resolvePath(parentPath));

	if (dir == nullptr) {
		output = -1;
	}
	else {
		for (Node* n : dir->getChildren()) {
			if (name == n->getName()) {
				output = -2;
				break;
			}
		}

		if (output == 0) {
			dir->addChild(new File(name, content));
		}
	}

	return output;
}

int FileSystem::createFolder(string path) {
	int output = 0; // -1 parent folder doesnt exist, -2 name already in use, -3 name too long

	string absPath = this->parsePath(this->currentPath, path);
	int lastSlash = absPath.find_last_of('/');
	string parentPath = absPath.substr(0, lastSlash);
	string name = path.substr(lastSlash + 1);

	Folder* dir = dynamic_cast<Folder*>(this->resolvePath(parentPath));

	if (dir == nullptr) 
	{
		output = -1;
	}
	else 
	{
		for (Node* n : dir->getChildren()) {
			if (name == n->getName()) {
				output = -2;
				break;
			}
		}

		if (output == 0) {
			dir->addChild(new Folder(name));
		}
	}

	return output;
}


bool FileSystem::goToFolder(string path, string & newPath)
{
	bool output = false;
	newPath = this->parsePath(this->currentPath, path);
	Folder* target = dynamic_cast<Folder*>(this->resolvePath(newPath));

	if (target != nullptr)
	{
		this->currentPath = newPath;
		output = true;
	}

	return output;
}

string FileSystem::listDir(string path) {
	string output = "";

	string absPath = this->parsePath(this->currentPath, path);
	Node* target = this->resolvePath(absPath);
	Folder* dir = dynamic_cast<Folder*>(target);

	if (dir != nullptr) {
		for (Node* child : dir->getChildren()) {
			output += " " + child->getName();
		}
	}
	else {
		output = "Could not find directory.";
	}

	return output + '\n';
}

void FileSystem::format()
{
	mMemblockDevice.reset();
	delete root;
	root = new Folder();
}

bool FileSystem::saveToFile(string filename)
{
	bool output = false;
	ofstream file;

	file.open(filename);

	for (int i = 0, s = mMemblockDevice.size(); i < s; i++)
	{
		file << mMemblockDevice.readBlock(i).toString() << endl;
	}

	file.close();

	output = true;
	return output;
}

bool FileSystem::loadFromFile(string filename)
{
	bool output = false;
	ifstream file;
	string block;

	this->format();
	file.open(filename);

	for (int i = 0; getline(file, block); i++)
	{
		mMemblockDevice.writeBlock(i, block);
	}

	file.close();

	output = true;
	return output;
}
