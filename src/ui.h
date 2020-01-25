#ifndef UI_H
#define UI_H

// The UI logic ================================================================
// command -> action description and associated info
// max description length
#define MAX_CMD_LENGTH 15
// the UI command data type
struct UIcommand
{
    action_code code;                     // associated action
    char description[MAX_CMD_LENGTH + 1]; // description
};
// the (global) array of all commands, filled at compile time
UIcommand UIcommands[NUM_ACTIONS] = {{NONE, ""},
                                     {EXIT, "Exit"},
                                     {NEW, "New game"},
                                     {TRY, "Make a guess"},
                                     {SHOW, "Show the secret"}};
// user input data type (in this case, a char)
using input = char;
// prompt for user input
char inputPrompt[] = "Enter your choice: ";
// prompt for user guess
char guessPrompt[] = "Enter your guess: ";
// translation between user input and actions data type
struct translation
{
    input what;     // what the user "types"
    action meaning; // what it means
};
// actual translations (might be filled at runtime)
translation input_action[] = {
    {'N', {NEW, PARAM_NONE}},
    {'n', {NEW, PARAM_NONE}},
    {'X', {EXIT, PARAM_NONE}},
    {'x', {EXIT, PARAM_NONE}},
    {'0', {TRY, '0'}},
    {'1', {TRY, '1'}},
    {'2', {TRY, '2'}},
    {'3', {TRY, '3'}},
    {'4', {TRY, '4'}},
    {'5', {TRY, '5'}},
    {'6', {TRY, '6'}},
    {'7', {TRY, '7'}},
    {'8', {TRY, '8'}},
    {'9', {TRY, '9'}},
    {'S', {SHOW, PARAM_NONE}},
    {'s', {SHOW, PARAM_NONE}}};
const int NUM_TRANSLATIONS = sizeof(input_action) / sizeof(input_action[0]);
// functions of the UI, called by the application logic
// mostra schermata di benvenuto
void showWelcomeScreen();
// nasconde schermata di benvenuto
void hideWelcomeScreen();
// acquisisce comando utente
action getUserCommand(const game &);
// possible alternatives
// everything is updated in update view
#define UPDATE_VIEW 0
// aggiorna schermata
void updateView(const game &);
// or when something new happens in the following functions
// called when a guess is checked
void guessChecked(const game &);
// called when a game is started
void gameStarted(const game &);
// called when a game is over
void gameEnded(const game &);
// called when the secret is shown
void secretShown(const game &);
// or a mix of the two alternatives, of course

#endif