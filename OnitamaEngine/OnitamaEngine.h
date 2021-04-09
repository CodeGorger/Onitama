#ifndef _ONITAMAENGINE_H_
#define _ONITAMAENGINE_H_

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
};

void OnitamaEngine::_initBoard()
{
    _currentBoardState = std::vector<std::vector<char>>();
    _currentBoardState.Add(std::vector<char>()
    {
        _blueDisciple, _blueDisciple, _blueMaster, _blueDisciple, _blueDisciple
    });
    _currentBoardState.Add(std::vector<char>()
    {
        '.', '.', '.', '.', '.'
    });
    _currentBoardState.Add(std::vector<char>()
    {
        '.', '.', '.', '.', '.'
    });
    _currentBoardState.Add(std::vector<char>()
    {
        '.', '.', '.', '.', '.'
    });
    _currentBoardState.Add(std::vector<char>()
    {
        _redDisciple, _redDisciple, _redMaster, _redDisciple, _redDisciple
    });
}

std::vector<Card> OnitamaEngine::_getRandomCards(int inAmount)
{
    if (_allCards.size() <= inAmount)
    {
        return _allCards;
    }

    // Starting with a full list of all randoms
    std::vector<int> randomIds = std::vector<int>();
    for (int i = 0; i < _allCards.size(); i++)
    {
        randomIds.push_back(i);
    }

    // Approaching backwards, removing until required amount is given
    srand(time(NULL));
    tmpRandomId = rand() % _allCards.size();
    foundInRet = false;
    for (int i = 0; i < randomIds.size(); i++)
    {
        if (randomIds[i] == tmpRandomId)
        {
            foundInRet = true;
            break;
        }
    }

    if (!foundInRet)
    {
    }

}


std::vector<Card> _allCards

bool _validateMove(? ? ? );

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
