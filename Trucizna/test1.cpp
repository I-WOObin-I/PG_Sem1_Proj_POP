#include <iostream>
#include <conio.h>


using namespace std;
/*
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

struct card
{
    int value;
    int color;
};
*/

int chartoint(char c)
{
    if(c=='0') { return 0; }
    if(c=='1') { return 1; }
    if(c=='2') { return 2; }
    if(c=='3') { return 3; }
    if(c=='4') { return 4; }
    if(c=='5') { return 5; }
    if(c=='6') { return 6; }
    if(c=='7') { return 7; }
    if(c=='8') { return 8; }
    if(c=='9') { return 9; }
}

void loadgame()
{
    char input;
    int inputint;
    int value=0;
    bool gotint=false;
    int temp=0;
    char color[3];

    for(;;)
    {
        cin>>input;
        if(input=='0'||input=='1'||input=='2'||input=='3'||input=='4'||input=='5'||input=='6'||input=='7'||input=='8'||input=='9')
        {
            inputint=chartoint(input);
            value=value*10;
            value=value+inputint;
            gotint=true;
        }
        else
        {
            if(gotint==true)
            {
                color[temp]=input;
                temp++;
            }
            if(temp==3)
            {
                cout<<value<<" "<<color[0]<<color[1]<<color[2]<<endl;
                temp=0;
                gotint=false;
                value=0;
            }
        }
    }
}

int pow10(int a, int b)
{
    for(int i=0 ; i<b ; i++)
    {
        a=a*10;
    }
    return a;
}

void insert_string(char* c, char* b)
{
    //cout<<"log: received by f()"<<endl;
    for(int i=0 ; i<10 ; i++)
    {
        //cout<<"log: c["<<i<<"] = "<<c[i]<<endl;
        //cout<<"log: b["<<i<<"] = "<<b[i]<<endl;

        //if(b[i]=='\n') { cout<<"log: break"<<endl; break; }
        c[i]=b[i];
    }
}

int main()
{
    int tab[5]={5,2,3,1,4};
    int length = 5;
    cout<<"array received:  \t";
    for(int i=0 ; i<length ; i++)
    {
        cout<<tab[i]<<" ";
    }
    cout<<endl;

    int temp1=0,temp2=0,x;
    for(int i=length-1 ; i>0 ; i--)
    {
        temp1 = tab[i];
        temp2 = i;
        for(int j=i-1 ; j>=0 ; j--)
        {
            if( tab[j] > temp1 ) { temp2 = j ; temp1 = tab[j]; }
        }
        x = tab[i]; cout<<"x: "<<x<<endl;
        tab[i] = temp1; cout<<" tab[i]: "<<tab[i]<<endl;
        tab[temp2] = x;
        for(int i=0 ; i<length ; i++)
    {
        cout<<tab[i]<<" ";
    }
    cout<<endl;
    }

    cout<<"array sorted:   \t";
    for(int i=0 ; i<length ; i++)
    {
        cout<<tab[i]<<" ";
    }
    cout<<endl;

    /*
    1 player hand cards: 1 red 4 white 15 blue 8 white 17 blue 18 blue 1 violet 11 black 2 yellow 17 red 18 white 7 violet 19 red 3 red 4 blue
1 player deck cards: 11 blue 2 violet 20 violet 10 green 6 violet 5 red
2 player hand cards: 6 blue 1 yellow 3 blue 10 white 9 white 11 yellow 8 red 11 red 2 white 18 red 8 yellow 10 green 14 yellow 10 green 9 black 7 yellow 14 blue 14 white 10 green 3 violet 16 white 5 black
2 player deck cards: 20 blue 19 violet 20 white
3 player hand cards: 19 black 15 red 15 white 12 white 9 blue 16 yellow
3 player deck cards: 19 white 14 red 18 yellow 1 blue 7 white 12 violet 16 violet 13 red 15 violet 20 yellow 14 violet 4 black 10 violet 8 black 12 blue 3 white
4 player hand cards: 9 red 5 white 10 green 7 blue 10 green 16 black 4 violet 13 violet 1 white
4 player deck cards: 8 blue 10 red 6 black 10 blue 15 yellow 6 yellow 3 yellow 10 yellow 10 green 12 red 14 black
5 player hand cards: 5 blue 13 white 11 violet 9 yellow 6 red 4 red 9 violet 10 black 5 violet 7 black 18 black 5 yellow 20 red 17 yellow 16 blue
5 player deck cards: 17 black
1 pile cards: 15 black 10 green
2 pile cards: 8 violet
3 pile cards: 2 red
4 pile cards:
5 pile cards: 6 white
6 pile cards: 19 yellow 12 yellow

    /*
    cout<<endl;
    for(int i=0; i<n; i++)
    {
        cout<<trash[i];
    }
    //cout<<trash<<endl;
    /*
    for(int i=0 ; i<n*2 ; i++)
    {
        cin>>plnumber;
        cin>>trash;
    }
    cout<<endl<<"done"<<endl;
    for(int i=0 ; i<n ; i++)
    {
        cout<<tab[i]<<endl;
    }
    */


    /*
    int playerC;
    cin>>playerC;
    int n;
    cin>>n;

    card** tab;
    tab = new card *[playerC];
    for(int i=0 ; i<playerC ; i++)
    {
        tab[i] = new card[n];
    }

    for(int i=0 ; i<playerC ; i++)
    {
        cout<<"player: "<<i+1<<endl;
        for(int j=0 ; j<n ; j++)
        {
            cin>>tab[i][j].value>>tab[i][j].color;
        }
    }

    for(int i=0 ; i<playerC ; i++)
    {
        cout<<"player: "<<i+1<<endl;
        for(int j=0 ; j<n ; j++)
        {
            cout<<tab[i][j].value<<" ";
            printcolor(tab[i][j].color);
        }
    }
    */

    return 0;
}
