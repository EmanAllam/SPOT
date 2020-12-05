#include "StudyPlan.h"
#include <iostream>


StudyPlan::StudyPlan()
{
	//By default, the study plan starts with 5 years
	//More year can be added
	for (int i = 0; i < 5; i++)
		plan.push_back(new AcademicYear(i + 1));
	PlanNote = new Notezz();
}

//adds a course to the study plan in certain year, semester
//year idetifies year number to add course to 1=first, 2 = 2nd,....
bool StudyPlan::AddCourse(Course* pC, int year, SEMESTER sem)
{
	//TODO: add all requried checks to add the course 

	plan[year - 1]->AddCourse(pC, sem);
	
	return true;
}

bool StudyPlan::AddNote(string content)
{
	PlanNote->AddContent(content);

	return true;
}


void StudyPlan::DrawMe(GUI* pGUI) const
{

	int x = Year_xStart;
	int y = Year_yStart;
	//Plan draws all year inside it.
	for (int i = 0; i < plan.size(); i++) {
		graphicsInfo gInfo{ x, y };
		plan[i]->setGfxInfo(gInfo);
		plan[i]->DrawMe(pGUI);
		y += YearHeight;
	}

	graphicsInfo gInfo{ Year_xStart + YearWidth + Note_xMargin, Year_yStart };
	PlanNote->setGfxInfo(gInfo);
	PlanNote->DrawMe(pGUI);
}


StudyPlan::~StudyPlan()
{
}
