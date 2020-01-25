/**
 * Purpose: base game application: guess a decimal digit
 * Author:  Emanuele Rizzolo
 * Class:   3XIN
 * Date:    2020/01/15
 * Note:
*/

/**
 * La logica del gioco è semplice e consiste nel far indovinare all'utente,
 * in un tempo e con guesses limitati, un segreto generato casualmente
 * dal computer.
 * L'utente può eseguire delle "azioni" sul gioco stesso specificando, cioè
 * eseguendo, opportuni "comandi" dell'interfaccia utente.
 */
/**
 * Per facilitare le modifiche, si sono tenute il più possibile separate:
 *  1   la logica del gioco:
 *      così è possibile cambiare interfaccia utente senza modificarla
 *  2   l'interfaccia utente:
 *      così è possibile "sostituire"  un tipo ad un altro senza impatti su 1
 */
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

#define DEBUG 0

// The application logic ======================================================
// application configuration (to be precised later)
using configuration = int;
// carica e restituisce la configurazione dell'applicazione
configuration loadConfiguration();
// salva la configurazione dell'applicazione
void saveConfiguration(const configuration &);

// The game logic =============================================================
/**
 * Questa sezione definisce la logica del gioco, le operazioni che si possono
 * effettuare ed i dati necessari alla gestione.
 */
// data to be guessed
using guess = char;
// max number of guesses
#define MAX_GUESSES 5 // fair enough!
// game status (with default initialization)
struct game
{
    guess secret;               // il segreto da indovinare
    int numGuesses{0};          // il numero di tentativi effettuati
    guess guesses[MAX_GUESSES]; // i tentativi effettuati
    bool rightGuess{false};     // l'utente ha indovinato
    bool hidden{true};          // segreto nascosto/mostrato all'utente
};
// actions available on the game (known to the application and the user interface)
// game may be NEW (numGuesses == 0 && hidden), RUNNING, OVER (rightGuess || !hidden || numGuesses == MAX_GUESSES)
// get a new game, with default initialization according to configuration
game newGame(const configuration &);
// check if a guess (supposed valid) equals the secret, updating game
// if game is OVER, return false
bool checkGuess(game &, guess);
// get the secret, updating game
guess getSecret(game &);

// The action logic ============================================================
/**
 * Definizione interna delle operazioni che si possono effettuare.
 * Le azioni sono in numero finito ed identificate internamente da un codice,
 * indipendentemente dalla modalità con cui l'utente le indica; possono
 * essere abilitate o disabilitate a seconda della situazione del gioco.
 * L'abilitazione e la disabilitazione di un'azione dovrebbero essere
 * notificate in qualche modo all'utente tramite l'interfaccia.
 * Per gestire più agevolmente azioni "simili" esse possono avere
 * in alcuni casi un dato (parametro) aggiuntivo.
 * Ad es. anzichè gestire quattro azioni di spostamento (Nord, Sud, Est, Ovest)
 * ne prevedo una sola (Move) con parametro direzione.
 * In questo caso viene usata per l'azione TRY.
 */
// the action codes
enum action_code
{
    NONE,       // fake code to indicate no action at all
    EXIT,       // exit the application
    NEW,        // new game
    TRY,        // make a guess (with guess as parameter)
    SHOW,       // show the secret
    NUM_ACTIONS // fake code: total number of actions (including NONE)
};
// action parameter [optional] data type
using action_param = int;
// definition of no parameter specified
#define PARAM_NONE 0
// action to be processed, maybe returned by user interface
struct action
{
    action_code code;
    action_param param;
};
// status of actions: enabled/disabled
bool isEnabled(action_code, const game &);
// elabora comando utente
void processUserCommand(action, game &, configuration &);

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

// The main logic ==============================================================
int main(int argc, char *argv[])
{
    srand(time(nullptr));
    showWelcomeScreen();
    configuration config = loadConfiguration();
    hideWelcomeScreen();
    action cmd;
    game g = newGame(config);
    do
    {
        updateView(g);
        cmd = getUserCommand(g);
        processUserCommand(cmd, g, config);
    } while (cmd.code != EXIT);
    saveConfiguration(config);
    /// successful termination
    return 0;
}

// Implementations!!!
// application functions
configuration loadConfiguration()
{
    cout << "Loading configuration..." << endl;
    return 42;
}
void saveConfiguration(const configuration &c)
{
    cout << "Saving configuration " << c << endl;
}

// game functions

game newGame(const configuration &c)
{
    game g;
    g.secret = '0' + rand() % ('9' - '0' + 1);
    if (DEBUG)
    {
        cout << "new game " << g.secret << endl;
    }
    gameStarted(g); // notify UI
    return g;
}

guess getSecret(game &g)
{
    g.hidden = false;
    secretShown(g); // notify UI
    gameEnded(g);   // notify UI
    return g.secret;
}

bool checkGuess(game &g, guess tentativo)
{
    bool result = false;
    if (isEnabled(TRY, g))
    {
        g.guesses[g.numGuesses] = tentativo;
        g.numGuesses++;
        result = g.rightGuess = tentativo == g.secret;
        guessChecked(g); // notify UI
        if (g.rightGuess || g.numGuesses == MAX_GUESSES)
        {
            gameEnded(g); // notify UI
        }
    }
    return result;
}

bool isEnabled(action_code code, const game &g)
{
    switch (code)
    {
    case EXIT:
        return true;
    case NEW:
        return g.numGuesses != 0 || !g.hidden;
    case TRY:
        return !g.rightGuess && g.hidden && g.numGuesses < MAX_GUESSES;
    case SHOW:
        return g.hidden && !g.rightGuess;
    default:
        return false;
    }
}

// UI functions
void showWelcomeScreen()
{
    cout << "Welcome to the game!!!" << endl;
}
void hideWelcomeScreen()
{
    cout << "Let's start!!!" << endl;
}
void updateView(const game &g)
{
    if (UPDATE_VIEW)
    {
        cout << endl; // just to separate
        if (g.rightGuess)
        {
            cout << "You guessed right at " << g.numGuesses << "° guess." << endl;
        }
        else if (g.hidden)
        {
            if (g.numGuesses == 0)
            {
                cout << "You haven't guessed yet: you have " << MAX_GUESSES - g.numGuesses << " guesses available." << endl;
            }
            else
            {
                if (g.numGuesses >= MAX_GUESSES)
                {
                    cout << "You haven't guessed right in the " << MAX_GUESSES << " guesses available." << endl;
                }
                else
                {
                    cout << "You haven't guessed right yet: you still have " << MAX_GUESSES - g.numGuesses << " guesses available." << endl;
                }
                cout << "Here are your previous guesses: ";
                for (int i = 0; i < g.numGuesses; ++i)
                {
                    cout << g.guesses[i] << " ";
                }
                cout << endl;
            }
        }
        else
        {
            cout << "You haven't guessed right; as you probably already know, the secret to be guessed was " << g.secret << "." << endl;
        }
    }
}

void showAvailableCommands(const game &g)
{
    for (int a = NONE; a < NUM_ACTIONS; a++)
    {
        if (isEnabled((action_code)a, g))
        {
            for (int i = 0; i < NUM_TRANSLATIONS; ++i)
            {
                if (input_action[i].meaning.code == a)
                {
                    cout << " " << input_action[i].what;
                }
            }
            cout << ": " << UIcommands[a].description << endl;
        }
    }
}

action translateInputToAction(input what)
{
    for (int i = 0; i < NUM_TRANSLATIONS; ++i)
    {
        if (what == input_action[i].what)
        {
            return input_action[i].meaning;
        }
    }
    return {NONE, PARAM_NONE};
}

action getUserCommand(const game &g)
{
    cout << endl; // just to separate
    showAvailableCommands(g);
    cout << inputPrompt;
    input what;
    cin >> what;
    // translation
    return translateInputToAction(what);
}

void guessChecked(const game &g)
{
    if (g.rightGuess)
    {
        cout << "You guessed right at " << g.numGuesses << "° guess (" << g.guesses[g.numGuesses - 1] << ")." << endl;
    }
    else
    {
        cout << "Your " << g.numGuesses << "° guess (" << g.guesses[g.numGuesses - 1] << ") is wrong." << endl;
        if (g.numGuesses >= MAX_GUESSES)
        {
            cout << "You haven't guessed right in the " << MAX_GUESSES << " guesses available." << endl;
        }
        else
        {
            cout << "You haven't guessed right yet: you still have " << MAX_GUESSES - g.numGuesses << " guesses available." << endl;
        }
        cout << "Here are your previous guesses: ";
        for (int i = 0; i < g.numGuesses; ++i)
        {
            cout << g.guesses[i] << " ";
        }
        cout << endl;
    }
}
void gameStarted(const game &g)
{
    cout << "New game!!! You haven't guessed yet: you have " << MAX_GUESSES - g.numGuesses << " guesses available." << endl;
}
void gameEnded(const game &g)
{
    cout
        << "Game over!!!" << endl;
}
void secretShown(const game &g)
{
    cout << "The secret to be guessed was " << g.secret << "." << endl;
}

void processUserCommand(action c, game &g, configuration &config)
{
    if (DEBUG)
    {
        cout << "processing action " << c.code << " with param " << c.param << ": enabled " << isEnabled(c.code, g) << endl;
    }
    if (isEnabled(c.code, g))
    {
        switch (c.code)
        {
        case EXIT:
            break;
        case NEW:
            g = newGame(config);
            break;
        case TRY:
            checkGuess(g, c.param); // ignore result
            break;
        case SHOW:
            getSecret(g); // ignore result
            break;
        default:
            cout << "Should never be here !!!! " << endl;
        }
    }
    else
    {
        cout << "command not available" << endl;
    }
}
