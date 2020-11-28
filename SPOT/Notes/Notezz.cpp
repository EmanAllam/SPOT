#include "Notezz.h"
#include "GUI/GUI.h"

Notezz::Notezz(string n_content):content(n_content)
{
}

Notezz::~Notezz()
{
}


string Notezz::getContent() const
{
	return content;
}


void Notezz::DrawMe(GUI* pG) const
{
	pG->DrawNote(this);
}