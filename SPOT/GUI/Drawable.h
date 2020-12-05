#pragma once
class GUI;

struct graphicsInfo
{
	//coords of left corner of rectangular area where this obj should be drawn
	int x, y;	
};
//constants related to objects to be drawn
enum
{
	CRS_WIDTH = 80,		//width of course rectangle to be drawn on screen
	CRS_HEIGHT = 25,	//Height of course rectangle to be drawn on screen
	//PLAN_YEAR_WIDTH = CRS_WIDTH * 4,	//width of plan year rectangle to be drawn on screen
	//PLAN_YEAR_HEIGHT	//Height of play year rectangle to be drawn on screen

	Year_xStart = 10,
	Year_yStart = 100,
	YearWidth = 1000,
	YearHeight = 100,
	YearSmallWidth = 75,
	YearSmallHeight = 75,
	SemWidth = 100,
	SemHeight = 25,
	YearBoxSmall_xMargin = 10,
	YearBoxSmall_yMargin = (YearHeight - YearSmallHeight) / 2,
	SemBoxSmall_yMargin = (YearHeight - SemHeight * 3) / 4,
	Course_xMargin = 10,
	Note_xMargin = 20,
	Note_Width = 250,
	Note_Height = YearHeight * 5,
	NoteLine_yMargin = 15
};

//Base class for all drawable classes
class Drawable
{
protected:
	//Info required for drawing
	graphicsInfo GfxInfo;
	bool Selected;	//is this obj selected (to highlight when drawing)
public:
	Drawable();
	void setGfxInfo(graphicsInfo);
	graphicsInfo getGfxInfo() const;
	void setSelected(bool );
	bool isSelected() const;
	void virtual DrawMe(GUI*) const = 0;
	virtual ~Drawable();
};

