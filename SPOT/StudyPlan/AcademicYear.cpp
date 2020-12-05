#include "AcademicYear.h"
#include "../GUI/GUI.h"




AcademicYear::AcademicYear(int num) : Num (num)
{
	//TODO: make all necessary initializations
}


AcademicYear::~AcademicYear()
{
}

//Adds a course to this year in the spesified semester
bool AcademicYear::AddCourse(Course* pC, SEMESTER sem)
{
	//TODO:
	//This function still needs many checks to be compelete
	YearCourses[sem].push_back(pC);
	TotalCredits += pC->getCredits();

	//TODO: acording to course type incremenet corrsponding toatl hours for that year


	return true;
}


void AcademicYear::DrawMe(GUI* pGUI) const
{
	pGUI->DrawAcademicYear(this);
	//Draw all semesters inside this year by iterating on each semester list
	//to get courses and draw each course
	int x;
	int y = GfxInfo.y + SemBoxSmall_yMargin;
	for (int sem = FALL; sem < SEM_CNT; sem++)
	{	
		x = GfxInfo.x + YearBoxSmall_xMargin * 3 + YearSmallWidth + SemWidth;
		for (auto it = YearCourses[sem].begin(); it != YearCourses[sem].end(); ++it)
		{	
			graphicsInfo gInfo{ x, y };
			(*it)->setGfxInfo(gInfo);
			(*it)->DrawMe(pGUI);	//call DrawMe for each course in this semester
			x += Course_xMargin + CRS_WIDTH;
		}
		y += SemBoxSmall_yMargin + SemHeight;
	}
}