
#include "OnitamaEngine.h"

void OnitamaEngine::_initBoard()
{
    _currentBoardState = std::vector<std::vector<char>>();
    _currentBoardState.push_back(
        {
            _blueDisciple, _blueDisciple, _blueMaster, _blueDisciple, _blueDisciple
        });
    _currentBoardState.push_back(
        {
            '.', '.', '.', '.', '.'
        });
    _currentBoardState.push_back(
        {
            '.', '.', '.', '.', '.'
        });
    _currentBoardState.push_back(
        {
            '.', '.', '.', '.', '.'
        });
    _currentBoardState.push_back(
        {
            _redDisciple, _redDisciple, _redMaster, _redDisciple, _redDisciple
        });
}

void OnitamaEngine::_initAllCards()
{
    Card c01 = Card("Tiger", false);
    c01.AddJumpOption(Point2D(0, -1));
    c01.AddJumpOption(Point2D(0, 2));

    Card c02 = Card("Dragon", true);
    c02.AddJumpOption(Point2D(1, -1));
    c02.AddJumpOption(Point2D(2, 1));
    c02.AddJumpOption(Point2D(-1, -1));
    c02.AddJumpOption(Point2D(-1, 1));

    Card c03 = Card("Frog", true);
    c03.AddJumpOption(Point2D(-1, 1));
    c03.AddJumpOption(Point2D(-2, 0));
    c03.AddJumpOption(Point2D(1, -1));

    Card c04 = Card("Rabbit", false);
    c04.AddJumpOption(Point2D(1, 1));
    c04.AddJumpOption(Point2D(2, 0));
    c04.AddJumpOption(Point2D(-1, -1));

    Card c05 = Card("Crab", false);
    c05.AddJumpOption(Point2D(1, 0));
    c05.AddJumpOption(Point2D(-2, 0));
    c05.AddJumpOption(Point2D(2, 0));

    Card c06 = Card("Elephant", true);
    c06.AddJumpOption(Point2D(1, 0));
    c06.AddJumpOption(Point2D(-1, 0));
    c06.AddJumpOption(Point2D(1, 1));
    c06.AddJumpOption(Point2D(-1, 1));

    Card c07 = Card("Goose", false);
    c07.AddJumpOption(Point2D(1, 0));
    c07.AddJumpOption(Point2D(1, -1));
    c07.AddJumpOption(Point2D(-1, 0));
    c07.AddJumpOption(Point2D(-1, 1));

    Card c08 = Card("Rooster", true);
    c08.AddJumpOption(Point2D(1, 0));
    c08.AddJumpOption(Point2D(1, 1));
    c08.AddJumpOption(Point2D(-1, 0));
    c08.AddJumpOption(Point2D(-1, -1));

    Card c09 = Card("Monkey", false);
    c09.AddJumpOption(Point2D(1, 1));
    c09.AddJumpOption(Point2D(-1, -1));
    c09.AddJumpOption(Point2D(-1, 1));
    c09.AddJumpOption(Point2D(1, -1));

    Card c10 = Card("Mantis", true);
    c10.AddJumpOption(Point2D(1, -1));
    c10.AddJumpOption(Point2D(0, -1));
    c10.AddJumpOption(Point2D(-1, 1));

    Card c11 = Card("Horse", true);
    c11.AddJumpOption(Point2D(0, 1));
    c11.AddJumpOption(Point2D(-1, 0));
    c11.AddJumpOption(Point2D(0, -1));

    Card c12 = Card("Ox", false);
    c12.AddJumpOption(Point2D(0, 1));
    c12.AddJumpOption(Point2D(1, 0));
    c12.AddJumpOption(Point2D(0, -1));

    Card c13 = Card("Crane", false);
    c13.AddJumpOption(Point2D(1, 0));
    c13.AddJumpOption(Point2D(-1, 1));
    c13.AddJumpOption(Point2D(-1, -1));

    Card c14 = Card("Boar", true);
    c14.AddJumpOption(Point2D(1, 0));
    c14.AddJumpOption(Point2D(0, 1));
    c14.AddJumpOption(Point2D(0, -1));

    Card c15 = Card("Eel", false);
    c15.AddJumpOption(Point2D(-1, 1));
    c15.AddJumpOption(Point2D(-1, -1));
    c15.AddJumpOption(Point2D(1, 1));

    Card c16 = Card("Cobra", true);
    c16.AddJumpOption(Point2D(-1, 0));
    c16.AddJumpOption(Point2D(1, -1));
    c16.AddJumpOption(Point2D(1, 1));


    std::vector<Card>_allCards = std::vector<Card>();
    _allCards.push_back(c01);
    _allCards.push_back(c02);
    _allCards.push_back(c03);
    _allCards.push_back(c04);
    _allCards.push_back(c05);
    _allCards.push_back(c06);
    _allCards.push_back(c07);
    _allCards.push_back(c08);
    _allCards.push_back(c09);
    _allCards.push_back(c10);
    _allCards.push_back(c11);
    _allCards.push_back(c12);
    _allCards.push_back(c13);
    _allCards.push_back(c14);
    _allCards.push_back(c15);
    _allCards.push_back(c16);

}

std::vector<Card> OnitamaEngine::_getRandomCards(unsigned int inAmount)
{
    if (0 == inAmount)
    {
        return std::vector<Card>();
    }

    // Starting with a full list of all randoms
    std::vector<int> randomIds = std::vector<int>();
    for (unsigned int i = 0; i < _allCards.size(); i++)
    {
        randomIds.push_back(i);
    }
    // randomIds := { 0, 1, 2, ..., 15, 16 }

    // Approaching backwards, removing until required amount is given
    srand((unsigned int)time(NULL));

    while (randomIds.size() > inAmount)
    {
        int tmpRandomId = rand() % _allCards.size();
        randomIds.erase(randomIds.begin() + tmpRandomId);
    }

    std::vector<Card> ret = std::vector<Card>();
    for (unsigned int i = 0; i < randomIds.size(); i++)
    {
        ret.push_back(_allCards[randomIds[i]]);
    }
    return ret;
}





bool OnitamaEngine::_checkIfCardExists(std::string inCardName)
{
    for (unsigned int i = 0; i < _allCards.size(); i++)
    {
        if (_allCards[i].GetName() == inCardName)
        {
            return true;
        }
    }
    return false;
}

bool OnitamaEngine::_checkIfPlayerOwnsCard(
    bool inIsPlayerRed,
    std::string inCardName)
{
    std::vector<unsigned int> playersCards;
    if (inIsPlayerRed)
    {
        playersCards = _currentCardsRed;
    }
    else
    {
        playersCards = _currentCardsBlue;
    }

    for (unsigned int i = 0; i < playersCards.size(); i++)
    {
        if (_allCards[playersCards[i]].GetName() == inCardName)
        {
            return true;
        }
    }
    return false;
}

Card OnitamaEngine::_getCard(std::string inCardName)
{
    for (unsigned int i = 0; i < _allCards.size(); i++)
    {
        if (_allCards[i].GetName() == inCardName)
        {
            return _allCards[i];
        }
    }
    return Card("HÄBÄDÄBÄDÄH!",true);
}

std::vector<Point2D> OnitamaEngine::_calculateJumpEndOptions(
    Point2D inFigureStartPosition, 
    std::vector<Point2D> inJumpOptions)
{
    std::vector<Point2D> ret = std::vector<Point2D>();
    for (unsigned int i = 0; i < inJumpOptions.size(); i++)
    {
        ret.push_back(inFigureStartPosition+inJumpOptions[i]);
    }
    return ret;
}

bool OnitamaEngine::_isOnBoard(Point2D inPoint)
{
    if (inPoint.GetX() < 0 || 
        inPoint.GetX() > _boardSize - 1 ||
        inPoint.GetY() < 0 ||
        inPoint.GetY() > _boardSize - 1)
    {
        return false;
    }
    else
    {
        return true;
    }
}


bool OnitamaEngine::_hasOwnPieceAtLocation(
    bool inIsPlayerRed, 
    Point2D inPoint)
{
    char pieceOnPoint = _currentBoardState[inPoint.GetY()][inPoint.GetX()];
    char ownDisciple;
    char ownMaster;
    if (inIsPlayerRed)
    {
        ownDisciple = _redDisciple;
        ownMaster = _redMaster;
    }
    else
    {
        ownDisciple = _blueDisciple;
        ownMaster = _blueMaster;
    }
    if (pieceOnPoint != ownDisciple && pieceOnPoint != ownMaster)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool OnitamaEngine::_endpointIsInEndPositionOptions(
    std::vector<Point2D> inEndPositionOptions, 
    Point2D inFigureEndPosition)
{
    for (unsigned int i = 0; i < inEndPositionOptions.size(); i++)
    {
        if (inFigureEndPosition == inEndPositionOptions[i])
        {
            return true;
        }
    }
    return false;
}

bool OnitamaEngine::_cardHasEndpositionAsOption(
    bool inIsPlayerRed,
    MoveInformation inMove)
{
    Card usedCard = _getCard(inMove.GetCardName());
    std::vector<Point2D> jumpOptions =
        usedCard.GetJumpOptions(inIsPlayerRed);
    std::vector<Point2D> endPositionOptions =
        _calculateJumpEndOptions(inMove.GetFigureStartPosition(), jumpOptions);

    return _endpointIsInEndPositionOptions(
        endPositionOptions,
        inMove.GetFigureEndPosition());
}





bool OnitamaEngine::ValidateMove(
    bool inIsPlayerRed,
    MoveInformation inMove)
{
    std::string cardName = inMove.GetCardName();
    Point2D figureStartPosition = inMove.GetFigureStartPosition();
    Point2D figureEndPosition = inMove.GetFigureEndPosition();

    if (!_isOnBoard(figureStartPosition))
    {
        _engineState = "The start point isn't on the game board (";
        _engineState += figureStartPosition.ToChessString() + ").";
        return false;
    }
    if (!_hasOwnPieceAtLocation(inIsPlayerRed, figureStartPosition))
    {
        _engineState = "No piece of player ";
        _engineState += ((inIsPlayerRed) ? "red" : "blue");
        _engineState += " found at start point (";
        _engineState += figureStartPosition.ToChessString() + ").";
        return false;
    }
    if (!_checkIfCardExists(cardName))
    {
        _engineState = "The cardname ";
        _engineState += cardName;
        _engineState += " wasn't found at all.";
        return false;
    }
    if (!_checkIfPlayerOwnsCard(inIsPlayerRed, cardName))
    {
        _engineState = "The player ";
        _engineState += ((inIsPlayerRed) ? "red" : "blue");
        _engineState += " doesn't have the card ";
        _engineState += cardName;
        _engineState += ".";
        return false;
    }
    if (!_isOnBoard(figureEndPosition))
    {
        _engineState = "The end point isn't on the board (";
        _engineState += figureEndPosition.ToChessString() + ").";
        return false;
    }
    if (_hasOwnPieceAtLocation(inIsPlayerRed, figureEndPosition))
    {
        _engineState = "The end point is already occupied by a piece of player(";
        _engineState += ((inIsPlayerRed) ? "red" : "blue");
        _engineState += ".";
        return false;
    }
    if (_cardHasEndpositionAsOption(
        inIsPlayerRed, inMove))
    {
        _engineState = "The choosen card (" + cardName;
        _engineState += ") doesn't allow a jump from ";
        _engineState += figureStartPosition.ToChessString() + " to ";
        _engineState += figureEndPosition.ToChessString() + ".";
        return false;
    }
    return true;
}



void OnitamaEngine::ApplyMove(MoveInformation inMove)
{

}


OnitamaEngine::OnitamaEngine()
{
    _initBoard();
    _initAllCards();
}