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

#include "game.h"
#include "action.h"
#include "ui.h"

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

#include "game.cpp"
#include "action.cpp"
#include "ui.cpp"
