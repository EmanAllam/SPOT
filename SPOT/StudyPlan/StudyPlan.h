#pragma once
#include <vector>
#include "AcademicYear.h"
#include "../Notes/Notezz.h"
#include "../GUI/Drawable.h"

//A full study plan for as student
class StudyPlan:public Drawable
{
	int TotalCredits=0;		//total no. of credit hours for courses registred in this year
	int TotalUnivCredits=0, TotalMajorCredits=0,
		TotalTrackCredits=0, TotalConcentrationCredits=0,
		TotalMinorCredits=0;

	vector<AcademicYear*> plan;	//plan is a list of academic years

	string PlanNotes;
	vector<Notezz*> planNotes;
public:
	StudyPlan();
	bool AddCourse(Course*, int year, SEMESTER);
	bool AddNote(Notezz*);
	void virtual DrawMe(GUI*) const;
	virtual ~StudyPlan();
};

