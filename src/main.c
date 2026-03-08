#include "common.h"
#include "globals.h"
#include "arithmetic.h"
#include "utils.h"
#include "list.h"
#include "tree.h"
#include "parser.h"
#include "validation.h"
#include "commands.h"
#include "tools.h"

/*
 * Contains the main execution loop of the calculator.
 * Handles user input, orchestrates modules, and outputs results.
 */


int main(int argc, char *argv[])
{	
	//Main variables
	char mode[LENGTH_OF_MODE + 1];
	char stopMode[LENGTH_OF_MODE + 1];
	int precision;
	char string[COMMAND_LENGTH + 1 + 1]; //+1 for '\n' and another +1 for '\0'
	char stringToOperate[FUNCTION_ARGS_SIZE];
	long double results;
	//Main variables

	int i;
	for (i = 0; i < LENGTH_OF_MODE; i++) //Initializations
	{
		mode[i] = '0';
		stopMode[i] = '0';
	}
	mode[i] = '\0';
	stopMode[i] = '\0';

	c_setPrecision(&precision);
	c_setMode(mode, false);

	while (strcmp(mode, stopMode) != 0)
	{
		//Calculator
		if (mode[0] == '1')
		{
			while (mode[0] == '1')
			{
				printf("\e[32mCalculator : \e[0m");
				scan(string, COMMAND_LENGTH);
				if (isCommand(string))
				{
					runCommand(string, mode, &precision);
					continue;
				}

				List *list = initializeList();
				errorInInterpretation = false;
				list = stringToList(string);
				if (errorInInterpretation)
				{
					continue;
				}

				if (syntaxAnalysis(list) == false)
				{
					printf("\n\n");
					continue;
				}
				manageAllConstants(list);
				manageImplicitMultiplications(list);

				Tree *tree = initializeTree();
				insertBefore(list, "(", list->first);
				insertAtTheEnd(list, ")");
				fillTree(tree, list);
				manageAllObjects(tree);
				strcpy(stringToOperate, listToString(list));

				deleteAllFromList(list);
				deleteAllFromTree(tree);

				errorInExecution = false;
				results = operate(stringToOperate);
				if (!errorInExecution)
				{
					printf("\e[32mResults : \e[0m");
					printf("%.*Lg\n\n", precision, results);
				}
			}
		}
		//Tools
		else if (mode[0] == '2')
		{
			//Identifier of prime number
			if (mode[1] == '1')
			{
				while (mode[0] == '2' && mode[1] == '1')
				{
					printf("\e[32mTools->IdentifierOfPN : \e[0m");
					scan(string, COMMAND_LENGTH);
					if (isCommand(string))
					{
						runCommand(string, mode, &precision);
						continue;
					}

					printf("\e[32mResults : \e[0m");
					identifyPrimeNumber(string);
				}
			}
		}
		//Documentation
		else if (mode[0] == '3')
		{
			bool firstTime;
			firstTime = true;

			//Credit
			if (mode[1] == '1')
			{
				while (mode[0] == '3' && mode[1] == '1')
				{
					printf("\e[32mDoc->Credit : \e[0m");
					if (firstTime)
					{
						printf("\n"
							   "-----DEVELOPER-----"
							   "\n"
							   "J. G. O. Samuel AKABASSI"
							   "\n\n");
						firstTime = false;
						continue;
					}
					scan(string, COMMAND_LENGTH);
					if (isCommand(string))
					{
						runCommand(string, mode, &precision);
						continue;
					}
				}
			}
			//How to use ?
			else if (mode[1] == '2')
			{
				while (mode[0] == '3' && mode[1] == '2')
				{
					printf("\e[32mDoc->HowToUse : \e[0m");
					if (firstTime)
					{
						printf("\n"
							   "HOW TO USE ?"
							   "\n"
							   "This program is divided into two main parts:"
							   "\n"
							   "- a calculator which allows you to perform all the basic operations and also offers some scientific functions;"
							   "\n"
							   "- a set of mathematical tools (for example to check if a number is prime or not)."
							   "\n"
							   "\n"
							   "This program also has a control system using commands. Here are the available commands and their functions:"
							   "\n"
							   "1- setMode: Allows you to choose an operating mode."
							   "\n"
							   "2- back: Returns to the previous mode selection step."
							   "\n"
							   "3- setPrecision: Sets the display precision of decimal results."
							   "\n"
							   "4- displayInfos: Allows you to display information about representable values, display precision of real numbers, etc."
							   "\n"
							   "5- clear: Clears the screen."
							   "\n"
							   "6- exit: Allows you to stop the program and exit."
							   "\n"
							   "\n"
							   "THE CALCULATOR"
							   "\n"
							   "To perform an operation, you must select Calculator mode and then write your operation. Your operation can only contain five (5) types of elements: Numbers, Operators, Constants, Separators, Functions."
							   "\n"
							   "1- The numbers are expressed in decimal base. The decimal point is indicated by the character \".\" . Example: 45.6 ."
							   "\n"
							   "2- This is the list of available operators: \"/\" (Division), \"*\" (Multiplication), \"-\" (Subtraction), \"+\" (Addition), \"%%\" (Percentage), \"!\" (Factorial  ), \"^\" (Exponentation). Example: 2.2+3*4.4 ."
							   "\n"
							   "3- There are two constants: \"pi\" (Mathematical constant Pi) and \"e\" (Mathematical constant e). Example: 2pi*e ."
							   "\n"
							   "4- There are two separators that allow you to group operations: \"(\" and \")\". Example: 2.2(3+4)(5+6) ."
							   "\n"
							   "5- This is the list of available functions: \"sqrt\" (Square Root), \"sin\" (Sinus), \"cos\" (Cosine), \"tan\" (Tangent), \"ln\" (Natural Logarithm), \"log\" (Decimal Logarithm), \"asin\" (Arc Sinus), \"acos\" (Arc Cosine), \"atan\" (Arc Tangent), \"exp\" (Exponential). To apply a function to a number(or operation), surround it with separators. Example: sin(sqrt(16)+5) ."
							   "\n"
							   "NOTE: Please see the \"Operators Precedence\" section of the documentation for details on how operators are evaluated."
							   "\n"
							   "\n"
							   "TOOLS"
							   "\n"
							   "To use a tool, select the corresponding mode."
							   "\n\n");
						firstTime = false;
						continue;
					}
					scan(string, COMMAND_LENGTH);
					if (isCommand(string))
					{
						runCommand(string, mode, &precision);
						continue;
					}
				}
			}
			//Operators precedence
			else if (mode[1] == '3')
			{
				while (mode[0] == '3' && mode[1] == '3')
				{
					printf("\e[32mDoc->OperatorsPrecedence : \e[0m");
					if (firstTime)
					{
						printf("\n"
							   "OPERATORS PRECEDENCE"
							   "\n"
							   "This is the list of operators grouped in descending order of priority :"
							   "\n"
							   "\t! %%\t\t-->"
							   "\n"
							   "\t^ unary-\t<--"
							   "\n"
							   "\t/ *\t\t-->"
							   "\n"
							   "\t+ binary-\t-->"
							   "\n"
							   "Operators on the same line have the same precedence and are evaluated against each other following the direction of the associated arrow."
							   "\n"
							   "Example 1: In \"2+3*4\", \"*\" is evaluated and then \"+\". The expression is therefore equivalent to: \"2+(3*4)\". The result is: 14 ."
							   "\n"
							   "Example 2: In \"2+3-4\", \"+\" is evaluated and then \"-\". The expression is therefore equivalent to: \"(2+3)-4\". The result is: 1 ."
							   "\n"
							   "Example 3: In \"-3^4^5\", the last \"^\" is evaluated, then the first \"^\" and finally the \"-\". The expression is therefore equivalent to: \"-(3^(4^5))\". The result is approximately: -3.733918487×10⁴⁸⁸ ."
							   "\n"
							   "Example 4: In \"-3^4+5^-6-7!\", \"!\" is evaluated, then the second \"-\", then the second \"^\", then the first \"^\", then the first \"-\", then the \"+\", then the last \"-\".  The expression is therefore equivalent to: \"((-(3^4))+(5^(-6)))-(7!)\". The result is: -5120.999936 ."
							   "\n\n");
						firstTime = false;
						continue;
					}
					scan(string, COMMAND_LENGTH);
					if (isCommand(string))
					{
						runCommand(string, mode, &precision);
						continue;
					}
				}
			}
		}
	}

	printf("\n");
	system("pause");
	return 0;
	
	
	
	
}
