#include <iostream>

using namespace std;

struct card
{
    int value;
    int color;
};

void printcolor(int n) // prints color by id //
{
    switch (n)
    {
        case 0: cout<<"green ";  break;
        case 1: cout<<"blue ";   break;
        case 2: cout<<"red ";    break;
        case 3: cout<<"violet "; break;
        case 4: cout<<"yellow "; break;
        case 5: cout<<"white ";  break;
        case 6: cout<<"black ";  break;
    }
}

void printplayercards(int plid , int plhandC , int pldeckC , card* plhand , card* pldeck )
{
    cout<<plid+1<<" player hand cards: ";
    for(int i=0 ; i<plhandC ; i++)
    {
        cout<<plhand[i].value<<" ";
        printcolor(plhand[i].color);
    }
    cout<<endl;

    cout<<plid+1<<" player deck cards: ";
    for(int i=0 ; i<pldeckC ; i++)
    {
        cout<<pldeck[i].value<<" ";
        printcolor(pldeck[i].color);
    }
    cout<<endl;
}

int main()
{
    ///////////////////////////////// INPUT //

    int playerC,colorC,greenC,greenV,speccolorC;  //
    cin>>playerC;                                 // playerC    - number of players                   (n)  <2-6>      // colors queue - green, blue, red, violet, yellow, white, black
    cin>>colorC;                                  // colorC     - number of colors/cauldrons          (k)  <1-6>      // id:              0      1    2      3       4      5      6
    cin>>greenC;                                  // greenC     - number of green cards               (g)  <1-9>      //
    cin>>greenV;                                  // greenV     - value of green cards                (gv) <1-10>     //
    cin>>speccolorC;                              // speccolorC - number of cards in specific color   (o)  <1-20>     //

    int* cardvalues;                              // cardvalues[] - array of color card values                        //
    cardvalues = new int [speccolorC];

    for(int i=0 ; i<speccolorC ; i++ )            // inserting color card values //
    {
        cin>>cardvalues[i];
    }                                             //


    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    card** plhands;                                             // 2D array of each player cards in hand plhands[ player ][ number on stack ][ card values, card colors ] //
    plhands = new card *[playerC];
    for(int i=0 ; i<playerC ; i++)
    {
        plhands[i] = new card [greenC+colorC*speccolorC];
    }                                                          //

    card** pldecks;                                             // 2D array of each player cards on deck pldecks[ player ][ number on stack ][ card values, card colors ] //
    pldecks = new card *[playerC];
    for(int i=0 ; i<playerC ; i++)
    {
        pldecks[i] = new card [greenC+colorC*speccolorC];
    }                                                          //

    int* plhandC;                       // array of number of cards in each player hand //
    int* pldeckC;                       // array of number of cards on each player deck //
    plhandC = new int [playerC];
    pldeckC = new int [playerC];
    for(int i=0 ; i<playerC ; i++)      // setting 0 to every cell of both arrays, as players don't have cards just yet //
    {
        plhandC[i] = 0;
        pldeckC[i] = 0;
    }                                   //


    int temp = 0;
    for(int i=0 ; i<greenC ; i++)                                       // green cards deal                                             //
    {                                                                   // 'temp' - current player to receive card                      //
        plhands[ temp ] [ plhandC[temp] ].value = greenV;
        plhands[ temp ] [ plhandC[temp] ].color = 0;                    // <- 0 is the green color id                                   //
        plhandC[ temp ]++;
        temp++;
        //cout<<"log: player "<<temp<<" given by: "<<greenV<<" green"<<endl;
        if(temp==playerC) { temp=0; }                                   // 'temp' starts from beginning when reaches the last player    //
    }                                                                   //

    for(int i=1 ; i<=colorC ; i++)                                      // color cards deal
    {
        for(int j=0 ; j<speccolorC ; j++)
        {
            plhands[ temp ] [ plhandC[temp] ].value = cardvalues[j];
            plhands[ temp ] [ plhandC[temp] ].color = i;                // in this case 'i' is the color id                             //
            plhandC[ temp ]++;
            temp++;
            //cout<<"log: player "<<temp<<" given by: "<<cardvalues[j]<<" "; printcolor(i); cout<<endl;
            if(temp==playerC) { temp=0; }                               // 'temp' starts from beginning when reaches the last player    //
        }
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    cout<<endl<<endl;
    cout<<"active player = 1"<<endl;
    cout<<"players number = "<<playerC<<endl;


    for(int i=0 ; i<playerC ; i++)
    {
        printplayercards(i,plhandC[i],pldeckC[i],plhands[i],pldecks[i]);
    }


    for(int i=0 ; i<colorC ; i++)
    {
        cout<<i+1<<" pile cards:"<<endl;
    }







    return 0;
}

