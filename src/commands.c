#include "common.h"
#include "commands.h"
#include "utils.h"

/*
 * Implements the logic for interpreting and executing user commands.
 */


/**
 * This function allow to know if a character string is a command or not.
 *
 */
bool isCommand(char *string)
{
	//********************
	const int FUNCTION_ID = 65;
	//********************

	if (string == NULL)
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return false;
	}

	if (strcmp(string, C_SET_M) == 0 || strcmp(string, C_BACK) == 0 || strcmp(string, C_SET_P) == 0 || strcmp(string, C_DISPLAY_I) == 0 || strcmp(string, C_CLEAR) == 0 || strcmp(string, C_EXIT) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/**
 * This function is used to execute commands. It calls the function corresponding to the given command.
 *
 */
void runCommand(char *command, char *mode, int *precision)
{
	//********************
	const int FUNCTION_ID = 66;
	//********************

	if (!isCommand(command))
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return;
	}

	if (strcmp(command, C_SET_M) == 0)
	{
		c_setMode(mode, false);
	}
	else if (strcmp(command, C_BACK) == 0)
	{
		c_back(mode);
	}
	else if (strcmp(command, C_SET_P) == 0)
	{
		c_setPrecision(precision);
	}
	else if (strcmp(command, C_DISPLAY_I) == 0)
	{
		c_displayInfos(*precision);
	}
	else if (strcmp(command, C_CLEAR) == 0)
	{
		c_clear();
	}
	else if (strcmp(command, C_EXIT) == 0)
	{
		c_exit(mode);
	}
	else
	{
		printError(FUNCTION_ID, 2);
		exit(EXIT_FAILURE);
		//return;
	}
}

/**
 * This function allow user to select the operating mode of the program.
 * The "mode" character string is used to store the mode. For example, the character string "2130" corresponds to the "2-1-3" mode.
 * The boolean "settingInProgress" indicates whether the initial value (value when calling the function) of "mode" must be taken into account or not.
 *
 * Case where "settingInProgress" = "false": The mode is first initialized to zero (for example "0000" or "000" or "00") then the user is asked to choose his mode from the  beginning.
 * For example the user can choose "1000" then "1300" then "1320".
 *
 * Case where "settingInProgress" = "true": In this case, we go up one level before asking the user to choose the mode he wants.
 * Suppose for example that the mode supplied as a parameter is "2130".
 * We go up one level and we get "2100". Then the user is invited to choose his mode.
 * He can then choose the modes "2110", "2120", 2130",...,"2111", 2112",...,"2121", "2122"  ,...,"2131", "2132",...
 *
 */
void c_setMode(char *mode, bool settingInProgress)
{
	//********************
	const int FUNCTION_ID = 67;
	//********************

	if (mode == NULL || strlen(mode) != LENGTH_OF_MODE)
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return;
	}

	char n;
	int i;
	if (!settingInProgress)
	{
		for (i = 0; i < LENGTH_OF_MODE; i++) //Initialization
		{
			mode[i] = '0';
		}
		mode[i] = '\0';

		printf("\nSelect a mode :\n1 - Calculator\n2 - Tools\n3 - Documentation\n\n");
		do
		{
			scanf("%c", &n);
		} while (n != '1' && n != '2' && n != '3');
		mode[0] = n;
		emptyBuffer();
	}
	else
	{
		for (i = LENGTH_OF_MODE - 1; i >= 0; i--) //Return to the back level
		{
			if (mode[i] != '0')
			{
				mode[i] = '0';
				break;
			}
		}
	}

	//Calculator
	if (mode[0] == '1')
	{
	}
	//Tools
	else if (mode[0] == '2')
	{
		printf("\nSelect a tool :\n1 - Identifier of prime numbers\n\n");
		do
		{
			scanf("%c", &n);
		} while (n != '1');
		mode[1] = n;
		emptyBuffer();

		//Tools : Identifier of prime numbers
		if (mode[1] == '1')
		{
		}
	}
	//Documentation
	else if (mode[0] == '3')
	{
		printf("\nSelect a documentation :\n1 - Credit\n2 - How to use ?\n3 - Operators precedence\n\n");
		do
		{
			scanf("%c", &n);
		} while (n != '1' && n != '2' && n != '3');
		mode[1] = n;
		emptyBuffer();

		//Documentation : Credit
		if (mode[1] == '1')
		{
		}
		//Documentation : How to use
		else if (mode[1] == '2')
		{
		}
		//Documentation : Operators Precedence
		else if (mode[1] == '3')
		{
		}
	}
	//Error : We chose to use Calculator by default.
	else
	{
		for (i = 0; i < LENGTH_OF_MODE; i++) //Initialization
		{
			mode[i] = '0';
		}
		mode[0] = '1';
	}
}

/**
 * This function allows the user to choose an operating mode after returning to the previous level.
 *
 */
void c_back(char *mode)
{
	//********************
	const int FUNCTION_ID = 68;
	//********************

	if (mode == NULL)
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return;
	}

	c_setMode(mode, true);
}

/**
 * This function allow user to choose the display precision of decimal numbers.
 *
 */
void c_setPrecision(int *precision)
{
	//********************
	const int FUNCTION_ID = 69;
	//********************

	if (precision == NULL)
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return;
	}

	char n;
	printf("\n"
		   "Select the precision :"
		   "\n"
		   "1 - 06 significant digits"
		   "\n"
		   "2 - 12 significant digits"
		   "\n"
		   "3 - %d significant digits"
		   "\n\n", LDBL_DIG);
	do
	{
		scanf("%c", &n);
	} while (n != '1' && n != '2' && n != '3');
	emptyBuffer();

	switch (n)
	{
	case '1':
		*precision = 6;
		break;
	case '2':
		*precision = 12;
		break;
	case '3':
		*precision = LDBL_DIG;
		break;
	}
}

/**
 * This function allow to display information about representable values, display precision of real numbers, etc.
 *
 */
void c_displayInfos(int precision)
{
	printf("\nRepresentable decimal values : min = (-) %Lg ; max = (-) %Lg \nRepresentable integer values : min = %lld ; max = %lld\n", LDBL_MIN, LDBL_MAX, LLONG_MIN, LLONG_MAX);
	printf("Display precision of decimal values = %d significant digits\n", precision);
	printf("Length of entries : min = 1 ; max = %d\n", COMMAND_LENGTH);
	printf("Maximum length of numbers = %d\n\n", MAX_LENGTH_OF_NUMBER - 1);
	printf("NOTE:\n- The decimal representation is used by default. It is always used in Calculator mode.\n- The integer representation is used only when it is the best fit. It is used in tools that operate on integers.\n\n");
}

/**
 * This function allow to clear the screen.
 *
 */
void c_clear()
{
	printf("\e[2J\e[1;1H");
}

/**
 * This function allow to stop the program and exit. Therefore, we set the mode to the stop mode which corresponds to null mode (eg "0000" or "000").
 *
 */
void c_exit(char *mode)
{
	//********************
	const int FUNCTION_ID = 70;
	//********************

	if (mode == NULL || strlen(mode) != LENGTH_OF_MODE)
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return;
	}

	int i;
	for (i = 0; i < LENGTH_OF_MODE; i++)
	{
		mode[i] = '0';
	}
	mode[i] = '\0';
}
