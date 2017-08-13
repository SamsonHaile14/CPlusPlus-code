#include <ncurses.h>

int main()
	{

	 char key;

	 initscr();
	 raw();

	 while( key != 'q' )
	   {

	    key = getch();

	   }

	 endwin();

	 return 0;

	}
