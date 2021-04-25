import OnitamaEngine

if __name__ == "__main__":
    x=OnitamaEngine.OnitamaEngine()
    
    r=x.GetCurrentCardsRed()
    print( "Red has ", len(r), "Cards" );
    print( r[0].GetName() )
    print( r[0].GetGridStringRed() )
    print( r[1].GetName() )
    print( r[1].GetGridStringRed() )
    print( " " );
    
    b=x.GetCurrentCardsBlue()
    print( "Blue has ", len(b), "Cards" );
    print( b[0].GetName() )
    print( b[0].GetGridStringBlue() )
    print( b[1].GetName() )
    print( b[1].GetGridStringBlue() )
    print( " " );
    
    c=x.GetCenterCard()
    print( "The center card is ", c.GetName() );
    print( " " );
    
    # print(x.GetCurrentBoardState())
    # print(x.PrintBoard())
    print(x.PrintBoardAndAxes())
    
    