#include "filesystem.h"
#include <sstream>
#include <vector>
#include <fstream>

FileSystem::FileSystem() {
  this->root = new Folder("");
}

FileSystem::~FileSystem() {
  delete root;
}

string FileSystem::parsePath(string wd, string path)
{
	string output = "";
	istringstream swd(wd), spath(path);
	string field;
    vector<string> abs, rel, fields;

	while (getline(spath, field, '/')) {
		abs.push_back(field);
	}
    
    while (getline(swd, field, '/')) {
        rel.push_back(field);
    }
    
    if (rel.at(0) == "")
    {
        fields = rel;
    }
    else
    {
        fields.reserve( abs.size() + rel.size() ); // preallocate memory
        fields.insert( fields.end(), abs.begin(), abs.end() );
        fields.insert( fields.end(), rel.begin(), rel.end() );
    }

	for (size_t i = 0; i < fields.size(); i++)
	{
        if (fields.at(i) == "")
        {
            //TODO REMOVE SELF FROM VECTOR
            fields.erase(fields.begin() + i);
            i--;
            
        }
		else if (fields.at(i) == ".")
		{
			//TODO REMOVE SELF FROM VECTOR
            fields.erase(fields.begin() + i);
            i--;

		}
        else if (fields.at(i) == "..")
        {
            //TODO REMOVE SELF AND PREVIOUS IF NOT FIRST FROM VECTOR
            if (i > 0)
            {
                fields.erase(fields.begin() + (i-1), fields.begin() + (i+1));
                i -= 2;
            }
            else
            {
                fields.erase(fields.begin() + i);
                i--;
            }
        }
	}

	for (string str : fields)
	{
		output += "/" + str;
	}
    
    if (output == "")
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

bool FileSystem::createFolder(string path, string name){
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
  } else {
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
