#ifndef FILE_H
#define FILE_H
#include <vector>
#include "node.h"
using namespace std;

class File : public Node
{
private:
	string content;

public:
	File();
	File(string name, string content = "");
	virtual ~File();

	void setContent(string content);
	string getContent();
};

#endif
