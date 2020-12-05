#include "ActionImportStudyPlan.h"
#include "..\Registrar.h"
#include "../Courses/UnivCourse.h"
#include "StudyPlan/StudyPlan.h"

#include "fstream"
#include <iostream>
#include <string>
using namespace std;


SEMESTER enumReturnSem(string semString)
{
	SEMESTER enumSem = FALL;
	if (semString == "Fall")
	{
		enumSem = FALL;
	}

	else if (semString == "Spring")
	{
		enumSem = SPRING;
	}

	else if (semString == "Summer")
	{
		enumSem = SUMMER;
	}
	return enumSem;
}


ActionImportStudyPlan::ActionImportStudyPlan(Registrar* p) :Action(p)
{
	Registrar* reg = p;
	new_StudyPlan = new StudyPlan;
}

bool ActionImportStudyPlan::Execute()
{
	GUI* pGUI = pReg->getGUI();

	pGUI->PrintMsg("Write Path to Study Plan");
	string path = pGUI->GetSrting();

	readStudyPlan(path);
	pReg->setStudyPlan(new_StudyPlan);

	return true;
}

void ActionImportStudyPlan::readStudyPlan(string fileName)
{

	//StudyPlan* new_StudyPlan = new StudyPlan;
	ifstream finput(fileName);
	int counter = 0;
	const int size = 300;
	char line[size];
	char* context = nullptr;
	char* pch;
	int year;
	SEMESTER semEnum = FALL;
	Course_Code code;

	//int x = 0;
	//int y = 0;
	while (finput.getline(line, size))
	{
		counter = 0;
		pch = strtok_s(line, ",", &context);

		//y += 50;
		//x = 0;
		while (pch != NULL)
		{

			if (counter == 0)	// if it is the Year
			{
				char* year_char = pch + 5;
				year = *year_char - '0';
				//string year = pch;
				cout << year << endl;
			}
			else if (counter == 1)
			{
				semEnum = enumReturnSem(pch);
				cout << "sem: " << pch << " " << semEnum << endl;
			}
			else {
				code = pch;
				//Temporary until we have a course catalogue
				string Title = "Test101";
				int crd = 0;
				Course* pC = new Course(code, Title, crd);
				//x += 75;
				//graphicsInfo gInfo{ x, y };
				//pC->setGfxInfo(gInfo);
				cout << code << endl;
				new_StudyPlan->AddCourse(pC, year, semEnum);
			}


			counter++;
			pch = strtok_s(NULL, ",", &context);


		}
	}	
}

ActionImportStudyPlan::~ActionImportStudyPlan()
{
}

