#include <iostream>
#include <conio.h>

using namespace std;

int main()
{
    char in;
    char trash[100];
    char color[100];

    int temp;
    int playerC;

    cin>>trash;
    cin>>trash;
    cin>>trash;
    cin>>temp;
    cin>>trash;
    cin>>trash;
    cin>>trash;
    cin>>playerC;

    int* tabh = new int [playerC];
    int* tabd = new int [playerC];
    for(int i=0 ; i<playerC ; i++)
    {
        tabh[i]=0;
        tabd[i]=0;
    }

        for(int i=0 ; i<playerC ; i++)
        {
            cin>>temp;
            cin>>trash;
            cin>>trash;
            cin>>trash;

            for(;;)
            {
                if(cin.get()=='\n') { break; }
                cin>>temp;
                cin>>color;
                tabh[i]++;
            }
            cin>>temp;
            cin>>trash;
            cin>>trash;
            cin>>trash;

            for(;;)
            {
                if(cin.get()=='\n') { break; }
                cin>>temp;
                cin>>color;
                tabd[i]++;
            }
        }

    for(int i=0 ; i<playerC ; i++)
    {
        cout<<i+1<<" player has "<<tabh[i]<<" cards on hand"<<endl;
        cout<<i+1<<" player has "<<tabd[i]<<" cards in front of him"<<endl;
    }


    return 0;
}
