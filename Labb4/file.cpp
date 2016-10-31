#include "file.h"

File::File() : Node()
{

}

File::File(string name, string content) : Node(name)
{
	this->content = content;
}

File::~File()
{
}

void File::setContent(string content)
{
	this->content = content;
}

string File::getContent()
{
	return this->content;
}
