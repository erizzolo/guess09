#ifndef ACTION_H
#define ACTION_H

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

#endif