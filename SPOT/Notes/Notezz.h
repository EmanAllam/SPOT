#pragma once
#include <string>
#include <list>
using namespace std;
#include "DEFs.h"

#include "GUI/Drawable.h"

//Base class for all types of Notes
class Notezz : public Drawable
{
	string content;		//content
	//bool Done;		//Done or not yet?

public:
	Notezz();
	string getContent() const;
	void AddContent(std::string);
	void DrawMe(GUI*) const;
	virtual ~Notezz();

};
