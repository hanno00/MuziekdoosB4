#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define LCD_LINES 4

#define TRUE 1
#define FALSE 0

#define MENU_SIZE 8

#define BUTTONS 5  // The buttons are W, A, S, D, E

#define MENU_MAIN 0

#define MENU_TIME 1
#define MENU_TIME_SUB 2

#define MENU_RADIO 3
#define MENU_RADIO_SUB 4

#define MENU_RECORD 5

#define MENU_MUSIC 6
#define MENU_MUSIC_SUB 7


// global variables
int currentMenuID = 0;
int state = 0;

// smart speaker global functions
int menuMain();
int getKey();
void handleMenu(int);
void printMenu(int);

// smart speaker navigational functions
void navigateTo(int);

// smart speaker functionality functions
void decreaseTime(void);
void increaseTime(void);
void selectStation(void);
void recordAudio(void);
void selectSong(void);
void confirmFlipBoolean(void);
void confirm(void);
char** menuText(int);

typedef struct MENU_ITEM {
	int menuID;
	char* menuContents[LCD_LINES];
	int menuConnectedTo[BUTTONS];
	void (*menuMethods[BUTTONS])(void);
} MENU_ITEM;

MENU_ITEM menu[MENU_SIZE] = {
	{
		MENU_MAIN,
		{	// Menu contents shown on LCD.
			"|     MAIN MENU    |",
			"|                  |",
			"| ^ MUSIC   TIME v |",
			"|                  |"
		},
		{	// Connected To Menu Items ID. Linked with WASDE, W = [0], A = [1]. -1 means no connection.
			MENU_MUSIC,
			-1,
			MENU_TIME,
			-1,
			-1
		},
		{	// Methods linked to the Menu. Linked with WASDE, W = [0], A = [1]. NULL if no method present.
			NULL,
			NULL,
			NULL,
			NULL,
			NULL
		}
	},
	{
		MENU_TIME,
		{	// Menu contents shown on LCD.
			"|     TIME MENU    |",
			"|    Submenu -->   |",
			"|                  |",
			"| ^ MAIN   RADIO v |"
		},
		{	// Connected To Menu Items ID. Linked with WASDE, W = [0], A = [1]. -1 means no connection.
			MENU_MAIN,			//W
			-1,					//A
			MENU_RADIO,			//S
			MENU_TIME_SUB,		//D
			-1					//E
		},
		{	// Methods linked to the Menu. Linked with WASDE, W = [0], A = [1]. NULL if no method present.
			NULL,				//W
			NULL,				//A
			NULL,				//S
			NULL,				//D
			NULL				//E
		}
	},
	{
		MENU_TIME_SUB,
		{	// Menu contents shown on LCD.
			"|   TIME SUB MENU  |",
			"|                  |",
			"|     Set Alarm    |",
			"|                  |"
		},
		{	// Connected To Menu Items ID. Linked with WASDE, W = [0], A = [1]. -1 means no connection.
			-1,					//W
			-1,					//A
			-1,					//S
			MENU_TIME,			//D
			-1					//E
		},
		{	// Methods linked to the Menu. Linked with WASDE, W = [0], A = [1]. NULL if no method present.
			NULL,				//W
			decreaseTime,		//A
			NULL,				//S
			increaseTime,		//D
			confirmFlipBoolean	//E
		}
	},
	{
		MENU_RADIO,
		{	// Menu contents shown on LCD.
			"|   RADIO MENU     |",
			"|   Submenu -->    |",
			"|                  |",
			"| ^ TIME  RECORD v |"
		},
		{	// Connected To Menu Items ID. Linked with WASDE, W = [0], A = [1]. -1 means no connection.
			MENU_TIME,			//W
			-1,					//A
			MENU_RECORD,		//S
			MENU_RADIO_SUB,		//D
			-1					//E
		},
		{	// Methods linked to the Menu. Linked with WASDE, W = [0], A = [1]. NULL if no method present.
			NULL,				//W
			NULL,				//A
			NULL,				//S
			NULL,				//D
			NULL				//E
		}
	},
	{
		MENU_RADIO_SUB,
		{	// Menu contents shown on LCD.
			"|  RADIO SUB MENU  |",
			"|                  |",
			"|   Set Station    |",
			"|                  |"
		},
		{	// Connected To Menu Items ID. Linked with WASDE, W = [0], A = [1]. -1 means no connection.
			-1,					//W
			-1,					//A
			-1,					//S
			MENU_RADIO,			//D
			-1					//E
		},
		{	// Methods linked to the Menu. Linked with WASDE, W = [0], A = [1]. NULL if no method present.
			NULL,				//W
			selectStation,		//A
			NULL,				//S
			selectStation,		//D
			confirmFlipBoolean				//E
		}
	},
	{
		MENU_RECORD,
		{	// Menu contents shown on LCD.
			"|    RECORD MENU   |",
			"|    Record [E]    |",
			"|                  |",
			"| ^ RADIO  MUSIC v |"
		},
		{	// Connected To Menu Items ID. Linked with WASDE, W = [0], A = [1]. -1 means no connection.
			MENU_RADIO,			//W
			-1,					//A
			MENU_MUSIC,		//S
			-1,		//D
			-1					//E
		},
		{	// Methods linked to the Menu. Linked with WASDE, W = [0], A = [1]. NULL if no method present.
			NULL,				//W
			NULL,				//A
			NULL,				//S
			NULL,				//D
			recordAudio			//E
		}
	},
	{
		MENU_MUSIC,
		{	// Menu contents shown on LCD.
			"|   MUSIC MENU     |",
			"|   Submenu -->    |",
			"|                  |",
			"| ^ RECORD  MAIN v |"
		},
		{	// Connected To Menu Items ID. Linked with WASDE, W = [0], A = [1]. -1 means no connection.
			MENU_RECORD,		//W
			-1,					//A
			MENU_MAIN,			//S
			MENU_MUSIC_SUB,		//D
			-1					//E
		},
		{	// Methods linked to the Menu. Linked with WASDE, W = [0], A = [1]. NULL if no method present.
			NULL,				//W
			NULL,				//A
			NULL,				//S
			NULL,				//D
			NULL				//E
		}
	},
	{
		MENU_MUSIC_SUB,
		{	// Menu contents shown on LCD.
			"|  MUSIC SUB MENU  |",
			"|                  |",
			"|    Set Music     |",
			"|                  |"
		},
		{	// Connected To Menu Items ID. Linked with WASDE, W = [0], A = [1]. -1 means no connection.
			-1,					//W
			-1,					//A
			-1,					//S
			MENU_MUSIC,			//D
			-1					//E
		},
		{	// Methods linked to the Menu. Linked with WASDE, W = [0], A = [1]. NULL if no method present.
			NULL,				//W
			selectSong,			//A
			NULL,				//S
			selectSong,			//D
			confirmFlipBoolean	//E
		}
	},
};

int menuMain()
{
	
	char** menucontents = menuText(currentMenuID);


	while (1)
	{
		// menucontents[0] t/m menucontents[3] zijn de 4 lines die je nodig hebt voor de LCD.
		// handleMenu() zorgt voor het wisselen van schermen op het menu.
		// getKey() leest input van het keyboard uit, alleen nodig op pc. 

		printf("\n%s\n", menucontents[0]);
		printf("%s\n", menucontents[1]);
		printf("%s\n", menucontents[2]);
		printf("%s\n", menucontents[3]);
		handleMenu(getKey());
		menucontents = menuText(currentMenuID);
	}
	
	return 0;
}

int getKey(void) 
{
	return _getch();
}

void handleMenu(int key)
{	// pas dit aan naar de waarden die de buttons gebruiken. Anders werkt ie alleen met keyboard.
	switch (key)
	{
		case 'W':
		case 'w':
			if (menu[currentMenuID].menuConnectedTo[0] == -1)
			{
				if (menu[currentMenuID].menuMethods[0] == NULL)
				{
					
				}
				else
				{
					menu[currentMenuID].menuMethods[0]();
				}
			}
			else
			{
				navigateTo(menu[currentMenuID].menuConnectedTo[0]);
			}
			break;
		case 'A':
		case 'a':
			if (menu[currentMenuID].menuConnectedTo[1] == -1)
			{
				if (menu[currentMenuID].menuMethods[1] == NULL)
				{
					
				}
				else
				{
					menu[currentMenuID].menuMethods[1]();
				}
			}
			else
			{
				navigateTo(menu[currentMenuID].menuConnectedTo[1]);
			}
			break;
		case 'S':
		case 's':
			if (menu[currentMenuID].menuConnectedTo[2] == -1)
			{
				if (menu[currentMenuID].menuMethods[2] == NULL)
				{
					
				}
				else
				{
					menu[currentMenuID].menuMethods[2]();
				}
			} 
			else
			{
				navigateTo(menu[currentMenuID].menuConnectedTo[2]);
			}
			break;
		case 'D':
		case 'd':
			if (menu[currentMenuID].menuConnectedTo[3] == -1)
			{
				if (menu[currentMenuID].menuMethods[3] == NULL)
				{
					
				}
				else
				{
					menu[currentMenuID].menuMethods[3]();
				}
			}
			else if ((menu[currentMenuID].menuConnectedTo[3] != -1 && menu[currentMenuID].menuMethods[3] != NULL)) 
			{
				if (state == FALSE)
				{   // submenu function
					menu[currentMenuID].menuMethods[3]();
				}
				else
				{	// switch back to main menu
					navigateTo(menu[currentMenuID].menuConnectedTo[3]);
					state = FALSE;
				}
			}
			else
			{
				navigateTo(menu[currentMenuID].menuConnectedTo[3]);
			}
			break;
		case 'E':
		case 'e':
			if (menu[currentMenuID].menuConnectedTo[4] == -1)
			{
				if (menu[currentMenuID].menuMethods[4] == NULL)
				{
					
				}
				else
				{
					menu[currentMenuID].menuMethods[4]();
				}
			}
			else
			{
				navigateTo(menu[currentMenuID].menuConnectedTo[4]);
			}
			break;
	}
}

void navigateTo(int destination)
{
	currentMenuID = destination;
}

void printMenu(int menuID)
{
	printf("\n+------------------+\n%s\n%s\n%s\n%s\n+------------------+\n", menu[menuID].menuContents[0], menu[menuID].menuContents[1], menu[menuID].menuContents[2], menu[menuID].menuContents[3]);
}

void decreaseTime(void) { printf("Time decreased!"); }
void increaseTime(void) { printf("Time increased!"); }
void selectStation(void) { printf("New station selected!"); }
void recordAudio(void) { printf("Audio recording!"); }
void selectSong(void) { printf("New song selected"); }
void confirm(void) { printf("Confirmed!"); }

void confirmFlipBoolean(void) 
{
	printf("Confirmed!");

	if (state == FALSE)
		state = TRUE;
	else
		state = FALSE;
}

char** menuText(int menuID) 
{
	char** sub_str = malloc(4 * sizeof(char*));

	for (int i = 0 ; i < 4; i++)
	{
		sub_str[i] = malloc(10 * sizeof(char));
		sub_str[i] = menu[menuID].menuContents[i];
	}

	return sub_str;
}