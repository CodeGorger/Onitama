#ifndef _ONITAMAENGINE_H_
#define _ONITAMAENGINE_H_

#include <vector>
#include "Card.h"
#include <time.h>
#include <cstdlib>

class OnitamaEngine
{
private:
    static const char _blueDisciple = 'b';
    static const char _blueMaster = 'B';
    static const char _redDisciple = 'r';
    static const char _redMaster = 'R';

    // _currentBoardState inited as:
    // 5 bbBbb
    // 4 .....
    // 3 .....
    // 2 .....
    // 1 rrRrr
    //   ABCDE
    std::vector<std::vector<char>> _currentBoardState;
    void _initBoard();

    std::vector<unsigned int> _currentCardsRed;
    std::vector<unsigned int> _currentCardsBlue;
    unsigned int _currentCardCenter;

    std::vector<Card> _allCards;
    std::vector<Card> _getRandomCards(int inAmount);

public:
    void InitAllCards();
};


bool _validateMove(bool inIsPlayerRed, Point2D FigureStartPosition, FigureEndPosition );

void _rejectMove(? ? ? );

public:
    // Returns 4 x 2D Board [5x5] bool; disciples red, master red, disciples blue, master blue
    // TODO(Simon) example comment
    ? ? ? GetBordStateDiscrete()

    // Returns 4 x 2D Board [5x5] bool; all red figures, all blue figures, all disciples, all masters
    // TODO(Simon): comment showing an example output
    ? ? ? GetBordStateCathegory()

    // Returns 3 x 12 bool; red cards, blue cards, center card
    // TODO(Simon): comment showing an example output
    ? ? ? GetCardState()

    // Returns 2 x 2D jump options [5x5] bool; Card 1 jumping options; Card 2 jumping options; 
    // TODO(Simon): comment showing an example output
    ? ? ? GetCardsRedCards(bool inMirrored)

    // Returns 2 x 2D jump options [5x5] bool; Card 1 jumping options; Card 2 jumping options; 
    // TODO(Simon): comment showing an example output
    ? ? ? GetCardsBlueCards(bool inMirrored)

    //
    void ReceiveMove(? ? ? )

#endif
