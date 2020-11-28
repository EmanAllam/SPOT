#include "ActionAddNote.h"
#include "..\Registrar.h"
#include "../Courses/UnivCourse.h"
#include "Notes/Notezz.h"

#include <iostream>
ActionAddNote::ActionAddNote(Registrar* p) :Action(p)
{
	Registrar *reg = p;
}

bool ActionAddNote::Execute()
{
	GUI* pGUI = pReg->getGUI();

	pGUI->PrintMsg("Add Note to describe the plan: ");
	string content = pGUI->GetSrting();

	ActionData actData = pGUI->GetUserAction("Select the place where you want the note to be added");


	int x, y;
	if (actData.actType == DRAW_AREA)	//user clicked inside drawing area
	{

		x = actData.x;
		y = actData.y;

		graphicsInfo gInfo{ x, y };
		Notezz* note = new Notezz(content);
		note->setGfxInfo(gInfo);
		
		StudyPlan* pS = pReg->getStudyPlay();
		pS->AddNote(note);

		return true;
	}
}

ActionAddNote::~ActionAddNote()
{
}