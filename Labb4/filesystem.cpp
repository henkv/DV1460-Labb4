#include "filesystem.h"

#include <sstream>
#include <vector>
#include <fstream>
#include "duallinklist.h"

FileSystem::FileSystem()
{
	this->root = new Folder("");
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

bool FileSystem::createFolder(string path, string name) {
	bool output = false;

	Folder* dir = dynamic_cast<Folder*>(resolvePath(path));

	if (dir != nullptr) {
		output = dir->addChild(new Folder(name));
	}

	return output;
}

string FileSystem::listDir(string path) {
	string output = "";

	Folder* dir = dynamic_cast<Folder*>(this->resolvePath(path));

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
