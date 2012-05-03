#include <curses.h>

/**********************************************************************************
  DESCRIPTION

  Move the physical cursor (as opposed to the logical cursor affected by 
  wmove()) to the given location. This is called mainly from doupdate(). 
  In general, this function need not compare the old location with the new 
  one, and should just move the cursor unconditionally.
************************************************************************************/

void PDC_gotoyx(int y, int x)
{
}

/**********************************************************************************
  DESCRIPTION

  The core output routine. It takes len chtype entities from srcp (a 
  pointer into curscr) and renders them to the physical screen at line 
  lineno, column x. It must also translate characters 0-127 via acs_map[], 
  if they're flagged with A_ALTCHARSET in the attribute portion of the 
  chtype.
************************************************************************************/

void PDC_transform_line(int lineno, int x, int len, const chtype* srcp)
{
}

