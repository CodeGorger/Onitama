
#include "OnitamaEngine.h"
#include "../MoveValidator/MoveValidator.h"

#include <algorithm>
#include <random>
#include <iostream>

#include <pybind11/pybind11.h>

void OnitamaEngine::_initBoard()
{
    _currentBoardState = std::vector<std::vector<char>>();
    _currentBoardState.push_back(
        {
            _redDisciple, _redDisciple,
            _redMaster,
            _redDisciple, _redDisciple
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
            _blueDisciple, _blueDisciple,
            _blueMaster,
            _blueDisciple, _blueDisciple
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
    c02.AddJumpOption(Point2D(-2, 1));

    Card c03 = Card("Frog", true);
    c03.AddJumpOption(Point2D(-1, 1));
    c03.AddJumpOption(Point2D(-2, 0));
    c03.AddJumpOption(Point2D(1, -1));

    Card c04 = Card("Rabbit", false);
    c04.AddJumpOption(Point2D(1, 1));
    c04.AddJumpOption(Point2D(2, 0));
    c04.AddJumpOption(Point2D(-1, -1));

    Card c05 = Card("Crab", false);
    c05.AddJumpOption(Point2D(0, 1));
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
    c10.AddJumpOption(Point2D(1, 1));
    c10.AddJumpOption(Point2D(-1, 1));
    c10.AddJumpOption(Point2D(0, -1));

    Card c11 = Card("Horse", true);
    c11.AddJumpOption(Point2D(0, 1));
    c11.AddJumpOption(Point2D(-1, 0));
    c11.AddJumpOption(Point2D(0, -1));

    Card c12 = Card("Ox", false);
    c12.AddJumpOption(Point2D(0, 1));
    c12.AddJumpOption(Point2D(1, 0));
    c12.AddJumpOption(Point2D(0, -1));

    Card c13 = Card("Crane", false);
    c13.AddJumpOption(Point2D(1, -1));
    c13.AddJumpOption(Point2D(0, 1));
    c13.AddJumpOption(Point2D(-1, -1));

    Card c14 = Card("Boar", true);
    c14.AddJumpOption(Point2D(1, 0));
    c14.AddJumpOption(Point2D(-1, 0));
    c14.AddJumpOption(Point2D(0, 1));

    Card c15 = Card("Eel", false);
    c15.AddJumpOption(Point2D(-1, 1));
    c15.AddJumpOption(Point2D(-1, -1));
    c15.AddJumpOption(Point2D(1, 0));

    Card c16 = Card("Cobra", true);
    c16.AddJumpOption(Point2D(-1, 0));
    c16.AddJumpOption(Point2D(1, -1));
    c16.AddJumpOption(Point2D(1, 1));


    _allCards = std::vector<Card>();
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

void OnitamaEngine::_initPlayers()
{
    // pybind11::print("Py OnitamaEngine::_initPlayers");
    _currentCardsRed = std::vector<Card>();
    _currentCardsBlue = std::vector<Card>();

    // pybind11::print("Py _getRandomCards(5)");
    std::vector<Card> c = _getRandomCards(5);
    if (5 > c.size())
    {
        _engineStatus = "Couldn't find 5 Cards";
        return;
    }

    // pybind11::print("Py (5 <= c.size())");
    _currentCardsRed.push_back(c[0]);
    _currentCardsRed.push_back(c[1]);
    _currentCardsBlue.push_back(c[2]);
    _currentCardsBlue.push_back(c[3]);
    _currentCardCenter = c[4];
    _isRedsTurn = _currentCardCenter.IsRedStartPlayer();
}

std::vector<Card> OnitamaEngine::_getRandomCards(unsigned int inAmount)
{
    if (0 == _allCards.size())
    {
        // pybind11::print("Py _initAllCards()");
        _initAllCards();
    }

    if (0 == inAmount || 0 == _allCards.size())
    {
        // pybind11::print("Py (0 == inAmount || 0 == _allCards.size())");
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
    // pybind11::print("Py srand((unsigned int)time(NULL))");

    while (randomIds.size() > inAmount)
    {
        // pybind11::print("(randomIds.size() > inAmount)", randomIds.size(), inAmount);

        int rnd = rand();

        int tmpRandomId = rnd % randomIds.size();
        // pybind11::print("rand, randId ", rnd, tmpRandomId);
        randomIds.erase(randomIds.begin() + tmpRandomId);
    }

    std::vector<Card> ret = std::vector<Card>();
    for (unsigned int i = 0; i < randomIds.size(); i++)
    {
        ret.push_back(_allCards[randomIds[i]]);
    }
    // pybind11::print("Py ret.push_back(_allCards[randomIds[i]]);");

    auto rng = std::default_random_engine{};
    std::shuffle(std::begin(ret), std::end(ret), rng);
    
    return ret;
}


bool OnitamaEngine::_foundBlueMaster()
{
    for (int i = 0; _currentBoardState.size(); i++)
    {
        for (int j = 0; _currentBoardState[i].size(); j++)
        {
            if (_currentBoardState[i][j] == _blueMaster)
            {
                return true;
            }
        }
    }
    return false;
}


bool OnitamaEngine::_foundRedMaster()
{
    for (int i = 0; _currentBoardState.size(); i++)
    {
        for (int j = 0; _currentBoardState[i].size(); j++)
        {
            if (_currentBoardState[i][j] == _redMaster)
            {
                return true;
            }
        }
    }
    return false;
}


Card OnitamaEngine::_getCard(std::string inCardName)
{
    for (int i = 0; i < _allCards.size(); i++)
    {
        if (_allCards[i].GetName() == inCardName)
        {
            return _allCards[i];
        }
    }
    return Card();
}

std::string OnitamaEngine::GetEngineStatus()
{
    return _engineStatus;
}


void OnitamaEngine::SetCurrentCardsRed(std::string inCard1, std::string inCard2)
{
    _currentCardsRed = std::vector<Card>();
    _currentCardsRed.push_back(_getCard(inCard1));
    _currentCardsRed.push_back(_getCard(inCard2));
}


void OnitamaEngine::SetCurrentCardsBlue(std::string inCard1, std::string inCard2)
{
    _currentCardsBlue = std::vector<Card>();
    _currentCardsBlue.push_back(_getCard(inCard1));
    _currentCardsBlue.push_back(_getCard(inCard2));
}


void OnitamaEngine::SetCurrentCardCenter(std::string inCard)
{
    _currentCardCenter = _getCard(inCard);
}


bool OnitamaEngine::ValidateMove(
    bool inIsPlayerRed,
    MoveInformation inMove)
{
    MoveValidator mv = MoveValidator(
        inIsPlayerRed,
        inMove,
        *this);

    bool isValidMove = mv.ValidateMove();
    _engineStatus = mv.GetStatus();
    return isValidMove;
}



//TODO(Simon): What if someone inserts nonsense...
void OnitamaEngine::ApplyMove(MoveInformation inMove)
{
    Point2D s = inMove.GetFigureStartPosition();
    char sField=_currentBoardState[s.GetY()][s.GetX()];
    _currentBoardState[s.GetY()][s.GetX()] = _emptyField;

    Point2D e = inMove.GetFigureEndPosition();
    char eField = _currentBoardState[e.GetY()][e.GetX()];
    _currentBoardState[e.GetY()][e.GetX()] = sField;

    std::string currentP = (_isRedsTurn) ? "Red" : "Blue";
    switch (eField)
    {
    case _blueDisciple:
        _engineStatus = currentP + " has taken a blue disciple.";
        break;
    case _blueMaster:
        _engineStatus = currentP + " has taken a blue master.";
        break;
    case _redDisciple:
        _engineStatus = currentP + " has taken a red disciple.";
        break;
    case _redMaster:
        _engineStatus = currentP + " has taken a red master.";
        break;
    case _emptyField:
        _engineStatus = currentP + " has moved.";
        break;
    default:
        _engineStatus = currentP + " has moved. (Unknown field)";
        break;
    }

    _isRedsTurn = !_isRedsTurn;

}


OnitamaEngine::OnitamaEngine()
{
    _allCards = std::vector<Card>();
    // pybind11::print("Py OnitamaEngine::OnitamaEngine()");
    _initAllCards();
    // pybind11::print("Py 1 _initAllCards");
    _initBoard();
    // pybind11::print("Py 2 _initBoard");
    _initPlayers();
    // pybind11::print("Py 3 _initPlayers");
}


std::string OnitamaEngine::PrintBoard()
{
    std::string ret = "";

    for (int yy = _boardSize, y = _boardSize; yy > 0; yy--, y--)
    {
        for (int x = 0; x < _boardSize; x++)
        {
            ret += _currentBoardState[y][x];
        }
        ret += "\n";
    }

    return ret;
}


std::string OnitamaEngine::PrintBoardAndAxes()
{
    std::string ret = "";

    for (int yy = _boardSize, y = _boardSize-1; yy > 0; yy--, y--)
    {
        ret += '0'+y;
        ret += " ";
        for (int x = 0; x < _boardSize; x++)
        {
            ret += _currentBoardState[y][x];
        }
        ret += "\n";
    }
    ret += "  ";
    for (int x = 0; x < _boardSize; x++)
    {
        ret += 'A'+x;
    }
    ret += "\n";

    return ret;
}


bool OnitamaEngine::IsGameOver()
{
    if (HasRedLost())
    {
        return true;
    }
    if (HasBlueLost())
    {
        return true;
    }
    return false;
}

bool OnitamaEngine::HasRedLost()
{
    if (HasRedLost_MasterTaken())
    {
        return true;
    }
    if (HasRedLost_ThroneTaken())
    {
        return true;
    }
    return false;
}

bool OnitamaEngine::HasBlueLost()
{
    if (HasBlueLost_MasterTaken())
    {
        return true;
    }
    if (HasBlueLost_ThroneTaken())
    {
        return true;
    }
    return false;
}

bool OnitamaEngine::HasRedLost_MasterTaken()
{
    if (!_foundRedMaster())
    {
        return true;
    }
    return false;
}

bool OnitamaEngine::HasBlueLost_MasterTaken()
{
    if (!_foundBlueMaster())
    {
        return true;
    }
    return false;
}

bool OnitamaEngine::HasRedLost_ThroneTaken()
{
    if (_currentBoardState[4][2] == _redMaster)
    {
        return true;
    }
    return false;
}

bool OnitamaEngine::HasBlueLost_ThroneTaken()
{
    if (_currentBoardState[0][2] == _blueMaster)
    {
        return true;
    }
    return false;
}