#pragma once
#include "Action.h"
#include <string>
#include <StudyPlan/StudyPlan.h>


//Class responsible for Importing study plan
class ActionImportStudyPlan:
	public Action
{
	StudyPlan* new_StudyPlan;
public:
	ActionImportStudyPlan(Registrar*);
	bool virtual Execute();
	void readStudyPlan(string fileName);
	virtual ~ActionImportStudyPlan();
};