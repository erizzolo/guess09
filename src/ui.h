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

// using rlutil
#include "rlutil.h"

#include <cstring>

// colour (text = foreground and background)
struct colour
{
    int text, back; // text and background components
};
// rectangular dimensions on the screen
struct dimension
{
    int vertical, horizontal; // vertical (rows) & horizontal (cols) dimension
};
#define MAX_TITLE_LENGTH 30
// a generic "window" on the screen
struct window
{
    dimension corner;                 // corner top (row) & left (col) coordinates
    dimension size;                   // total size (border included)
    dimension border;                 // border size
    colour content, frame;            // colours of content and border area
    char title[MAX_TITLE_LENGTH + 1]; // title
};
// the main window
window mainWindow{{2, 2},
                  {rlutil::trows() - 4, rlutil::tcols() - 2},
                  {1, 1},
                  {rlutil::WHITE, rlutil::BLACK},
                  {rlutil::BLACK, rlutil::GREY},
                  "Welcome to the game!!!"};
// the "menu" bar
window menuBar{{3, 3},
               {NUM_ACTIONS + 1, rlutil::tcols() - 4},
               {1, 0},
               {rlutil::GREEN, rlutil::BLACK},
               {rlutil::BLACK, rlutil::GREEN},
               "Available commands"};
// the game info window
window gameInfo{{9, 3},
                {3, rlutil::tcols() - 4},
                {0, 0},
                {rlutil::YELLOW, rlutil::BLACK},
                {rlutil::YELLOW, rlutil::BLACK},
                ""};
// the user input
window userInput{{13, 3},
                 {1, 20},
                 {0, 0},
                 {rlutil::YELLOW, rlutil::BLACK},
                 {rlutil::YELLOW, rlutil::BLACK},
                 ""};
// the status bar
window statusBar{{rlutil::trows() - 2, 2},
                 {3, rlutil::tcols() - 2},
                 {1, 1},
                 {rlutil::WHITE, rlutil::BLACK},
                 {rlutil::BLACK, rlutil::GREY},
                 "Status messages"};
// the time elapsed window (MM:SS,mmm)
window timeElapsed{{19, 3},
                   {3, 12},
                   {1, 1},
                   {rlutil::WHITE, rlutil::BLACK},
                   {rlutil::BLACK, rlutil::GREY},
                   "Time Elapsed"};
// the progress bar
window progressBar{{19, 15},
                   {3, rlutil::tcols() - 16},
                   {1, 1},
                   {rlutil::WHITE, rlutil::GREEN},
                   {rlutil::BLACK, rlutil::GREY},
                   "Time remaining"};
// functions to paint a window, clear content, ...
void paint(const window &);
void clear(const window &);
void printText(const window &, const char msg[], int row = 0, bool cls = true);
// utility function to show a message from application
void statusMsg(const char msg[]);

#endif
