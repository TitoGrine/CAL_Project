#ifndef INPUT_H_
#define INPUT_H_

#include <string>

/**
* Robustness of the int Input:
* - Checks if there is something left on the istringstream after the numbers
* - Controls eof character and other invalids characters erros using getlineZ;
*
* @param	question		Question that you want to write on the console when asking for an unsigned int
*
* @return	unsigned int	Int with the desired number
*
* @see		afterNumber
* @see		getlineZ		(@		ConsoleFunctions)
*/
unsigned int intInput(std::string question);

/**
* Robustness of the menu Input:
* - Checks if the input number is inside the menu option bounds
* - Controls eof character and other invalids characters erros using getlineZ;
*
* @param	question		Question that you want to write on the console when asking for the option number
* @param	inferiorLimit	Lower possible option in the menu
* @param	superiorLimit	Higher possible option in the menu
*
* @return	int				Integer with the desired option
*
* @see		getlineZ		(@		ConsoleFunctions)
*/
int menuInput(std::string question, int inferiorLimit, int superiorLimit);

#endif