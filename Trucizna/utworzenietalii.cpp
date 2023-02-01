#include <iostream>

using namespace std;

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

int main()
{
    ///////////////////////////////// INPUT //

    int colorC,greenC,greenV,speccolorC;    //
    cin>>colorC;                            // colorC     - number of colors/cauldrons          (k)  <1-6>      // colors queue - green, blue, red, violet, yellow, white, black
    cin>>greenC;                            // greenC     - number of green cards               (g)  <1-9>      // id:              0      1    2      3       4      5      6
    cin>>greenV;                            // greenV     - value of green cards                (gv) <1-10>     //
    cin>>speccolorC;                        // speccolorC - number of cards in specific color   (o)  <1-20>     //



    int* cardvalues;                        // cardvalues[] - array of color card values                        //
    cardvalues = new int [speccolorC];

    for(int i=0 ; i<speccolorC ; i++)       // inserting color card values //
    {
        cin>>cardvalues[i];
    }                                       //

    //////////////////////////////////////////

    for(int i=0 ; i<greenC ; i++)                       // printing green cards //
    {
        cout<<greenV<<" "; printcolor(0);
    }                                                   //
    for(int i=1 ; i<=colorC ; i++)                      // printing color cards //
    {
        for(int j=0 ; j<speccolorC ; j++)
        {
            cout<<cardvalues[j]<<" "; printcolor(i);
        }
    }                                                   //
    return 0;
}
