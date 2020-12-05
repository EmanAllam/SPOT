#include "GUI.h"
#include "../Courses/Course.h"
#include "../Notes/Notezz.h"
#include "../StudyPlan/AcademicYear.h"
#include <sstream>
#include <iostream>




GUI::GUI()
{ 
	pWind = new window(WindWidth, WindHeight,wx,wy);
	pWind->ChangeTitle(WindTitle);
	ClearDrawingArea();
	ClearStatusBar();
	CreateMenu();
}


//Clears the status bar
void GUI::ClearDrawingArea() const
{
	pWind->SetBrush(BkGrndColor);
	pWind->SetPen(BkGrndColor);
	pWind->DrawRectangle(0, MenuBarHeight, WindWidth, WindHeight -StatusBarHeight);

}

void GUI::ClearStatusBar() const
{
	pWind->SetBrush(StatusBarColor);
	pWind->SetPen(StatusBarColor);
	pWind->DrawRectangle(0, WindHeight - StatusBarHeight, WindWidth, WindHeight);
}

void GUI::CreateMenu() const
{
	pWind->SetBrush(StatusBarColor);
	pWind->SetPen(StatusBarColor);
	pWind->DrawRectangle(0, 0, WindWidth, MenuBarHeight);

	//You can draw the menu icons any way you want.

	//First prepare List of images paths for menu item
	string MenuItemImages[ITM_CNT];
	MenuItemImages[ITM_ADD] = "GUI\\Images\\Menu\\Menu_add_course.jpg";
	MenuItemImages[ITM_AddNote] = "GUI\\Images\\Menu\\Menu_Add_Note.jpg";
	MenuItemImages[ITM_ImportStudyPlan] = "GUI\\Images\\Menu\\Menu_StudyPlan.jpg";
	MenuItemImages[ITM_EXIT] = "GUI\\Images\\Menu\\Menu_Exit.jpg";

	//TODO: Prepare image for each menu item and add it to the list

	//Draw menu items one image at a time
	for (int i = 0; i<ITM_CNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*MenuItemWidth, 0, MenuItemWidth, MenuBarHeight);
}

////////////////////////    Output functions    ///////////////////

//Prints a message on the status bar
void GUI::PrintMsg(string msg) const
{
	ClearStatusBar();	//Clear Status bar to print message on it
						// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = StatusBarHeight - 10;

	// Print the Message
	pWind->SetFont(20, BOLD , BY_NAME, "Arial");
	pWind->SetPen(MsgColor);
	pWind->DrawString(MsgX, WindHeight - MsgY, msg);
}

//////////////////////////////////////////////////////////////////////////
void GUI::UpdateInterface() const
{
	
	pWind->SetBuffering(true);
	//Redraw everything
	CreateMenu();
	ClearStatusBar();
	ClearDrawingArea();
	pWind->UpdateBuffer();
	pWind->SetBuffering(false);

}

////////////////////////    Drawing functions    ///////////////////
void GUI::DrawCourse(const Course* pCrs)
{
	if (pCrs->isSelected())
		pWind->SetPen(HiColor, 2);
	else
	pWind->SetPen(DrawColor, 2);
	pWind->SetBrush(FillColor);
	graphicsInfo gInfo = pCrs->getGfxInfo();
	pWind->DrawRectangle(gInfo.x, gInfo.y, gInfo.x + CRS_WIDTH, gInfo.y + CRS_HEIGHT);
	pWind->DrawLine(gInfo.x, gInfo.y + CRS_HEIGHT / 2, gInfo.x + CRS_WIDTH, gInfo.y + CRS_HEIGHT / 2);
	
	//Write the course code and credit hours.
	int Code_x = gInfo.x + CRS_WIDTH * 0.15;
	int Code_y = gInfo.y + CRS_HEIGHT * 0.05;
	pWind->SetFont(CRS_HEIGHT * 0.4, BOLD , BY_NAME, "Gramound");
	pWind->SetPen(MsgColor);

	ostringstream crd;
	crd<< "crd:" << pCrs->getCredits();
	pWind->DrawString(Code_x, Code_y, pCrs->getCode());
	pWind->DrawString(Code_x, Code_y + CRS_HEIGHT/2, crd.str());
}

void GUI::DrawNote(const Notezz* pNote)
{	
	if (pNote->isSelected())
		pWind->SetPen(HiColor, 2);
	else
		pWind->SetPen(DrawColor, 2);
	pWind->SetBrush(FillColor);
	graphicsInfo gInfo = pNote->getGfxInfo();
	pWind->DrawRectangle(gInfo.x, gInfo.y, gInfo.x + Note_Width, gInfo.y + Note_Height);
	pWind->DrawLine(gInfo.x, gInfo.y + Note_Height / 10, gInfo.x + Note_Width, gInfo.y + Note_Height / 10);
	
	//Write the content.
	int Code_x = gInfo.x + Note_Width * 0.3;
	int Code_y = gInfo.y;
	pWind->SetFont(Note_Height * 0.06, BOLD, BY_NAME, "Gramound");
	pWind->SetPen(MsgColor);

	pWind->DrawString(Code_x, Code_y, "Notes");


	char* context = nullptr;
	char* pch;
	char* S = new char[pNote->getContent().length() + 1];
	strcpy_s(S, pNote->getContent().length() + 1, pNote->getContent().c_str());
	pch = strtok_s(S, "\n", &context);

	pWind->SetFont(Note_Height * 0.04, BOLD, BY_NAME, "Gramound");
	int new_margin = NoteLine_yMargin;
	while (pch != NULL)
	{	
		new_margin += NoteLine_yMargin;
		pWind->DrawString(gInfo.x + Note_Width * 0.05, gInfo.y + Note_Height / 10 + new_margin, pch);
		pch = strtok_s(NULL, "\n", &context);
	}

	
	
}


void GUI::DrawAcademicYear(const AcademicYear* pY) 
{
	graphicsInfo gInfo = pY->getGfxInfo();

	pWind->SetPen(DrawColor, 2);
	pWind->SetBrush(BkGrndColor);
	pWind->DrawRectangle(gInfo.x , gInfo.y, gInfo.x + YearWidth, gInfo.y + YearHeight );
	pWind->DrawRectangle(gInfo.x + YearBoxSmall_xMargin, gInfo.y + YearBoxSmall_yMargin, gInfo.x + YearBoxSmall_xMargin + YearSmallWidth, gInfo.y + YearBoxSmall_yMargin + YearSmallHeight);


	int Year_x = gInfo.x + YearBoxSmall_xMargin + YearSmallWidth * 0.15;
	int Year_y = gInfo.y + YearBoxSmall_xMargin+ YearSmallHeight * 0.05;
	pWind->SetFont(YearSmallWidth * 0.25, BOLD, BY_NAME, "Gramound");
	pWind->SetPen(MsgColor);
	ostringstream Yr;
	Yr << "Year " << pY->Num;
	pWind->DrawString(Year_x, Year_y, Yr.str());



	int Sem_x = gInfo.x + YearBoxSmall_xMargin + YearSmallWidth + SemWidth * 0.15;
	int Sem_y = gInfo.y + YearBoxSmall_yMargin + SemHeight * 0.05;
	pWind->SetPen(DrawColor, 2);
	pWind->SetBrush(BkGrndColor);
	pWind->DrawRectangle(gInfo.x + YearBoxSmall_xMargin * 2 + YearSmallWidth, gInfo.y + SemBoxSmall_yMargin, gInfo.x + YearBoxSmall_xMargin * 2 + YearSmallWidth + SemWidth, gInfo.y + SemBoxSmall_yMargin + SemHeight);
	pWind->SetFont(SemWidth * 0.2, BOLD, BY_NAME, "Gramound");
	pWind->SetPen(MsgColor);
	pWind->DrawString(Sem_x, Sem_y, "FALL");

	pWind->SetPen(DrawColor, 2);
	pWind->SetBrush(BkGrndColor);
	pWind->DrawRectangle(gInfo.x + YearBoxSmall_xMargin * 2 + YearSmallWidth, gInfo.y + SemBoxSmall_yMargin * 2 + SemHeight, gInfo.x + YearBoxSmall_xMargin * 2 + YearSmallWidth + SemWidth, gInfo.y + SemBoxSmall_yMargin * 2 + SemHeight * 2);
	pWind->SetFont(SemWidth * 0.2, BOLD, BY_NAME, "Gramound");
	pWind->SetPen(MsgColor);
	pWind->DrawString(Sem_x, Sem_y + SemBoxSmall_yMargin + SemHeight, "SPRING");

	pWind->SetPen(DrawColor, 2);
	pWind->SetBrush(BkGrndColor);
	pWind->DrawRectangle(gInfo.x + YearBoxSmall_xMargin * 2 + YearSmallWidth, gInfo.y + SemBoxSmall_yMargin * 3 + SemHeight * 2, gInfo.x + YearBoxSmall_xMargin * 2 + YearSmallWidth + SemWidth, gInfo.y + SemBoxSmall_yMargin * 3 + SemHeight * 3);
	pWind->SetFont(SemWidth * 0.2, BOLD, BY_NAME, "Gramound");
	pWind->SetPen(MsgColor);
	pWind->DrawString(Sem_x, Sem_y + SemBoxSmall_yMargin * 2 + SemHeight * 2, "SUMMER");







	///TODO: compelete this function to:
	//		1- Draw a rectangle for the academic year 
	//		2- Draw a sub-rectangle for each semester
	//Then each course should be drawn inside rect of its year/sem
	
}


////////////////////////    Input functions    ///////////////////
//This function reads the position where the user clicks to determine the desired action
//If action is done by mouse, actData will be the filled by mouse position
ActionData GUI::GetUserAction(string msg) const
{
	keytype ktInput;
	clicktype ctInput;
	char cKeyData;

	
	// Flush out the input queues before beginning
	pWind->FlushMouseQueue();
	pWind->FlushKeyQueue();
	
	PrintMsg(msg);

	while (true)
	{
		int x, y;
		ctInput = pWind->GetMouseClick(x, y);	//Get the coordinates of the user click
		ktInput = pWind->GetKeyPress(cKeyData);

		if (ktInput == ESCAPE)	//if ESC is pressed,return CANCEL action
		{
			return ActionData{ CANCEL };
		}

		
		if (ctInput == LEFT_CLICK)	//mouse left click
		{
			//[1] If user clicks on the Menu bar
			if (y >= 0 && y < MenuBarHeight)
			{
				//Check whick Menu item was clicked
				//==> This assumes that menu items are lined up horizontally <==
				int ClickedItemOrder = (x / MenuItemWidth);
				//Divide x coord of the point clicked by the menu item width (int division)
				//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

				switch (ClickedItemOrder)
				{
				case ITM_ADD: return ActionData{ ADD_CRS };	//Add course
				case ITM_AddNote: return ActionData{ ADD_NOTE };
				case ITM_ImportStudyPlan: return ActionData{ Import_StudyPlan };//Add note
				case ITM_EXIT: return ActionData{ EXIT };		//Exit

				default: return ActionData{ MENU_BAR };	//A click on empty place in menu bar
				}
			}

			//[2] User clicks on the drawing area
			if (y >= MenuBarHeight && y < WindHeight - StatusBarHeight)
			{
				return ActionData{ DRAW_AREA,x,y };	//user want clicks inside drawing area
			}

			//[3] User clicks on the status bar
			return ActionData{ STATUS_BAR };
		}
	}//end while

}

string GUI::GetSrting() const
{
	//Reads a complete string from the user until the user presses "ENTER".
	//If the user presses "ESCAPE". This function should return an empty string.
	//"BACKSPACE" is also supported
	//User should see what he is typing at the status bar

	

	string userInput;
	char Key;
	while (1)
	{
		pWind->WaitKeyPress(Key);

		switch (Key)
		{
		case 27: //ESCAPE key is pressed
			PrintMsg("");
			return ""; //returns nothing as user has cancelled the input

		case 13:		//ENTER key is pressed
			return userInput;

		case 8:		//BackSpace is pressed
			if (userInput.size() > 0)
				userInput.resize(userInput.size() - 1);
			break;

		default:
			userInput += Key;
		};

		PrintMsg(userInput);
	}

}








GUI::~GUI()
{
	delete pWind;
}
