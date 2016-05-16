#include "Tutorial.h"

#include <iostream>

#include <unistd.h>
#include <term.h>
#include <curses.h>
#include <functional>

using namespace std;

/// ClearScreen function to clean the terminal contents.
void ClearScreen()
{
  if (!cur_term) {
    int result;
    setupterm(NULL, STDOUT_FILENO, &result);
    if (result <= 0) {
      return;
    }
  }

  putp(tigetstr("clear"));
}

/// Prints the menu for tutorial selection.
void printMenu()
{
  /// Clear the screen so the menu is the only thing visible afterwards.
  ClearScreen();

  /// Print the menu options.
  cout << "Please Make A Selection" << endl;
  cout << "------------------------------------------------------" << endl;
  cout << "... ( 4 ) ... Tutorial 4  ..." << endl;
  cout << "... ( 5 ) ... Tutorial 5  ..." << endl;
  cout << "... ( 6 ) ... Tutorial 6  ..." << endl;
  cout << "... ( 7 ) ... Tutorial 7  ..." << endl;
  cout << "... ( 8 ) ... Tutorial 8  ..." << endl;
  cout << "... ( 9 ) ... Tutorial 9  ..." << endl;
  cout << "... ( a ) ... Tutorial 10 ..." << endl;
  cout << "... ( b ) ... Tutorial 11 ..." << endl;
  cout << "... ( c ) ... Tutorial 12 ..." << endl;
  cout << "... ( d ) ... Tutorial 13 ..." << endl;
  cout << "... ( e ) ... Tutorial 14 ..." << endl;
  cout << "... ( f ) ... Tutorial 15 ..." << endl;
  cout << "... ( g ) ... Tutorial 16 ..." << endl;

  /// All the tutorials up to tutorial 16 can co-exist, as they all use the same
  /// pattern flow for execution.  From 17 onward, that pattern changed significantly
  /// and in the interest of keeping all the tutrials in the same application, a
  /// compile-time define was added to declare the menu option for selection 'g'.

#ifdef __TUT_VERSION

#if __TUT_VERSION >= 17

  cout << "... ( h ) ... Tutorial " << __TUT_VERSION << " ..." << endl;

#endif

#endif

  cout << "------------------------------------------------------" << endl;
  cout << "... ( 0 ) ... Quit        ..." << endl;
  cout << "------------------------------------------------------" << endl;
}

int main(int argc, char* argv[])
{
  /// The tutorial Object that manages and runs the tutorial content.
  Tutorial* tut;

  /// Print the menu.
  printMenu();

  char input[10];

  while (1) {
    /// Capture the user's choice.
    cin.getline(input, 2);

    /// Decide what to do with the provided user input.
    switch (input[0]) {
    case '4' :
      tut = &Tutorial::getInstance(4, &argc, argv);
      break;
    case '5' :
      tut = &Tutorial::getInstance(5, &argc, argv);
      break;
    case '6' :
      tut = &Tutorial::getInstance(6, &argc, argv);
      break;
    case '7' :
      tut = &Tutorial::getInstance(7, &argc, argv);
      break;
    case '8' :
      tut = &Tutorial::getInstance(8, &argc, argv);
      break;
    case '9' :
      tut = &Tutorial::getInstance(9, &argc, argv);
      break;
    case 'a' :
      tut = &Tutorial::getInstance(10, &argc, argv);
      break;
    case 'b' :
      tut = &Tutorial::getInstance(11, &argc, argv);
      break;
    case 'c' :
      tut = &Tutorial::getInstance(12, &argc, argv);
      break;
    case 'd' :
      tut = &Tutorial::getInstance(13, &argc, argv);
      break;
    case 'e' :
      tut = &Tutorial::getInstance(14, &argc, argv);
      break;
    case 'f' :
      tut = &Tutorial::getInstance(15, &argc, argv);
      break;
    case 'g' :
      tut = &Tutorial::getInstance(16, &argc, argv);
      break;

      /// Menu option 'h' will launch a different tutorial for every compiled defined version.

#ifdef __TUT_VERSION

#if __TUT_VERSION >= 17

    case 'h' :
      tut = &Tutorial::getInstance(__TUT_VERSION, &argc, argv);
      break;

#endif

#endif

    case '0' :
      return 0;
    default  :
      cout << "Not a valid choice.  Try again." << endl;
      continue;
    }

    /// Executes the Run function for the tutorial that was set up above.
    tut->Run();

    break;
  }

  return 0;
}



