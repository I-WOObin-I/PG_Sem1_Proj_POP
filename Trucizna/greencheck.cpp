#include <iostream>

using namespace std;

int colortoid(char c[100])
{
    if(c[0]=='g' && c[1]=='r' && c[2]=='e') { return 0; } // green
    if(c[0]=='b' && c[1]=='l' && c[2]=='u') { return 1; } // blue
    if(c[0]=='r' && c[1]=='e' && c[2]=='d') { return 2; } // red
    if(c[0]=='v' && c[1]=='i' && c[2]=='o') { return 3; } // violet
    if(c[0]=='y' && c[1]=='e' && c[2]=='l') { return 4; } // yellow
    if(c[0]=='w' && c[1]=='h' && c[2]=='i') { return 5; } // white
    if(c[0]=='b' && c[1]=='l' && c[2]=='a') { return 6; } // black
    return 0;
}

int main()
{
    char trash[100];
    char color[100];
    int temp;
    int playerC;
    int greenV=0;
    int greenC=0;
    bool greenfound=false;

    bool colortab[7];
    colortab[0]=0;
    colortab[1]=0;
    colortab[2]=0;
    colortab[3]=0;
    colortab[4]=0;
    colortab[5]=0;
    colortab[6]=0;

    cin>>trash;     // active
    cin>>trash;     // player
    cin>>trash;     // =
    cin>>temp;
    cin>>trash;     // players
    cin>>trash;     // number
    cin>>trash;     // =
    cin>>playerC;
    //cout<<"player count: "<<playerC<<endl;

    for(int i=0 ; i<playerC*2 ; i++)
    {
        //cout<<"log: i = "<<i<<endl;
        cin>>temp;
        cin>>trash;
        cin>>trash;
        cin>>trash;
        for(;;)
        {
            if(cin.get()=='\n') { break; }
            //cout<<"temp: "<<endl;
            cin>>temp;
            //cout<<" (temp acc: "<<temp<<") "<<endl;
            cin>>color;
            //cout<<" (color acc: "<<color[0]<<") "<<endl;

            colortab[ colortoid(color) ] = true;
            //cout<<"colortab[id]: "<<colortab[ colortoid(color) ]<<endl;
            //cout<<"color id: "<<colortoid(color)<<endl;
            if(colortoid(color)==0)
            {
                greenC++;
                //cout<<"green found: "<<temp<<endl;
                if(greenfound==true)
                {
                    if(temp!=greenV)
                    {
                        cout<<"Different green cards values occurred"<<endl;
                        return 0;
                    }
                }
                else
                {
                greenV=temp;
                greenfound=true;
                }
            }
        }
    }

    int colorC=0;
    for(int i=1 ; i<7 ; i++)
    {
        if(colortab[i]==true) { colorC++; }
    }
    //cout<<"found colors: "<<colorC<<endl;

    for(int i=0 ; i<colorC ; i++)
    {
        //cout<<"log: i = "<<i<<endl;
        cin>>temp;
        cin>>trash;
        cin>>trash;
        for(;;)
        {
            if(cin.get()=='\n') { break; }
            //cout<<"temp: "<<endl;
            cin>>temp;
            //cout<<" (temp acc: "<<temp<<") "<<endl;
            cin>>color;
            //cout<<" (color acc: "<<color[0]<<") "<<endl;
            if(color[0]==p&&color[1]==l&&color[2]==a) { break; }
            if(colortoid(color)==0)
            {
                greenC++;
                //cout<<"green found: "<<temp<<endl;
                if(greenfound)
                {
                    if(temp!=greenV)
                    {
                        cout<<"Different green cards values occurred"<<endl;
                        return 0;
                    }
                }
                else
                {
                greenV=temp;
                greenfound=true;
                }
            }
        }
    }

    if(greenC==0) { cout<<"Green cards does not exist"<<endl; }
    else { cout<<"Found "<<greenC<<" green cards, all with "<<greenV<<" value"<<endl;}
    return 0;
}

