#include "Notezz.h"
#include "GUI/GUI.h"
#include <iostream>
#include <sstream>
#include <string>

Notezz::Notezz()
{
	content = "";
}

Notezz::~Notezz()
{
}


string Notezz::getContent() const
{
	return content;
}

void Notezz::AddContent(string new_content)
{	
	ostringstream stream;
	stream<< content << new_content << "\n";
	content = stream.str();
}


void Notezz::DrawMe(GUI* pG) const
{
	pG->DrawNote(this);
}