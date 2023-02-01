#include <iostream>

#define OVERALL_COLORS_COUNT 7
#define MAX_COLOR_NAME_LENGTH 10
#define MAX_INPUT_LINE_LENGTH 10000
#define ASCII_TABLE_0_SPOT 48

using namespace std;


struct card
{
    int value;
    int color_id;
};

struct available_colors
{
    int ids[ OVERALL_COLORS_COUNT ];
    char names [ OVERALL_COLORS_COUNT ][ MAX_COLOR_NAME_LENGTH ]=
    {
        {'g','r','e','e','n',0},
        {'b','l','u','e',0},
        {'r','e','d',0},
        {'v','i','o','l','e','t',0},
        {'y','e','l','l','o','w',0},
        {'w','h','i','t','e',0},
        {'b','l','a','c','k',0}
    };

} available_colors;

struct game_settings
{
    int players_C;
    int color_C;
    int green_C;
    int green_V;
    int spec_color_C;
    int explosion_threshold;

} game_settings;

////////////////////////////////////////////////////////////////////////////////////

bool is_digit(char c)
{
    if( c >= 48 && c <= 57) { return true; }
    return false;
}

void array_sort( int* tab , int length)
{
    //cout<<"array received:  \t";
    for(int i=0 ; i<length ; i++)
    {
        //cout<<tab[i]<<" ";
    }
    //cout<<endl;

    int temp1=0,temp2=0,x;
    for(int i=length-1 ; i>0 ; i--)
    {
        temp1 = tab[i];
        temp2 = i;
        for(int j=i-1 ; j>=0 ; j--)
        {
            if( tab[j] > temp1 ) { temp2 = j ; temp1 = tab[j]; }
        }
        x = tab[i];
        tab[i] = temp1;
        tab[temp2] = x;
    }

    //cout<<"array sorted:   \t";
    for(int i=0 ; i<length ; i++)
    {
        //cout<<tab[i]<<" ";
    }
    //cout<<endl;
}

void insert_string( char* rec, int string_length , char* send )
{
    for(int i=0 ; i<string_length ; i++)
    {
        rec[i] = send[i];
    }
}

void insert_available_colors()
{
    for(int i=0 ; i<OVERALL_COLORS_COUNT ; i++)
    {
        available_colors.ids[ i ] = i;
    }
}

int color_to_id( char* c )
{
    for(int i=0 ; i<OVERALL_COLORS_COUNT ; i++)
    {
        for(int j=0 ; j<MAX_COLOR_NAME_LENGTH ; j++)
        {
            if(c[ j ] == 0) { return i; break; }
            if(c[ j ] != available_colors.names[ i ][ j ]) { break; }
        }
    }
    //cout<<"error: color not found"<<endl;
    return 0;
}

void find_colors( bool* tab , card* cards , int cards_C )
{
    for(int i=0 ; i<cards_C ; i++)
    {
        tab[ cards[i].color_id ] = true;
    }
}

int count_colors( bool* tab)
{
    int colors_found=0;
    for(int i=1 ; i<OVERALL_COLORS_COUNT ; i++) // not counting green //
    {
        if(tab[i]==true) { colors_found++; }
    }
    return colors_found;
}

int count_colors_by_num ( int* tab )
{
    int colors_found=0;
    for(int i=1 ; i<OVERALL_COLORS_COUNT ; i++) // not counting green //
    {
        if(tab[i] >= 1) { colors_found++; }
    }
    return colors_found;
}

void count_colors_number( int* tab , card* cards , int cards_C )
{
    //cout<<"LOG: colors found: ";
    for(int i=0 ; i<cards_C ; i++)
    {
        tab[ cards[i].color_id ]++;
        //cout<<available_colors.names[ cards[i].color_id ]<<" ";
    }
    //cout<<endl;
}

int find_last_char_address( char* c )
{
    for(int i=0 ; ; i++)
    {
        if(c[i]==0) { return i-1; }
    }
    return 0;
}

void set_game_settings(int task_id)
{
    if(task_id==1)
    {
        cin>>game_settings.color_C;
        cin>>game_settings.green_C;
        cin>>game_settings.green_V;
        cin>>game_settings.spec_color_C;
    }
    if(task_id==2)
    {
        cin>>game_settings.players_C;
        cin>>game_settings.color_C;
        cin>>game_settings.green_C;
        cin>>game_settings.green_V;
        cin>>game_settings.spec_color_C;
    }
}

int interpret_input( char* c , card* output, int start_point )       // c - input line //
{

    int cards_found=0;
    int value=0;
    int color_id;
    char* color = new char [MAX_COLOR_NAME_LENGTH];
    int color_address=0;
    bool found_end_of_input=false;

    for(int i=start_point ; ; )                                                         // i=21 => before there is no important input //
    {                                                                                   //cout<<"i: "<<i<<"  : "<<int(c[i])<<endl;
        if(found_end_of_input==true)    { break;            }
        if(c[ i ]==0)                   { break;            }
        if(c[ i ]=='\n')                { break;            }
        if(c[ i ]==' ')                 { i++; continue;    }

        if( is_digit( c[i] ) )
        {
            for(int j=i ; ; j++)
            {                                                                           //cout<<"j1: "<<j<<"  : "<<int(c[j])<<endl;
                if( c[j] == ' ' )       { i=j+1; break;     }                           // i=j+1 => i starts after space is found //
                value=value*10;                                                         // increasing value as finding next digits of number //
                value+= c[j] - ASCII_TABLE_0_SPOT;
            }
            output[ cards_found ].value = value;                                        //cout<<"found: "<<value;
            value=0;                                                                    // resets value for next card //
            if(c[ i ]==' ') { i++; }

            for(int j=i ; ; j++)
            {                                                                           //cout<<"j2: "<<j<<"  : "<<int(c[j])<<endl;
                if( c[j] == ' ' )       { i=j+1; break;     }                           // i=j+1 => i starts after space is found //
                if(c[j]==0)             { i=j+1; found_end_of_input=true; break; }

                color[ color_address ] = c[ j ];
                color_address++;
            }
            color[ color_address ] = 0;                                                 // setting end point on char array //
            color_id = color_to_id( color );                                            //cout<<" "<<color<<endl;
            output[ cards_found ] .color_id = color_id;

            cards_found++;
            color_address=0;                                                            // resets color address for next card //
        }
    }
    //cout<<"returned: "<<cards_found<<endl;
    return cards_found;
}

int interpret_last_digits( char* c )
{
    //cout<<c;
    int temp;
    int value=0;
    for(int i=0 ; ; i++)
    {
        //cout<<c[i];
        if(c[i]=='=') { temp=i; break; }
    }
    temp+=2;
    for(int i=temp; ; i++)
    {
        if(c[i]==0) { return value; }
        value=value*10;
        value += c[i] - ASCII_TABLE_0_SPOT;
    }
    return 0;
}

void initiate_deck( card** tab )
{
    tab = new card *[ game_settings.players_C ];
    for(int i=0 ; i<game_settings.players_C ; i++)
    {
        tab[i] = new card [ game_settings.color_C * game_settings.spec_color_C + game_settings.green_C ];
    }
}

void print_cards( card* cards , int card_C )
{
    int id;
    for(int i=0 ; i<card_C ; i++)
    {
        if(cards[i].value == -1) { continue; }
        cout<<cards[ i ].value<<" ";
        id = cards[ i ].color_id;
        cout<<available_colors.names[ id ]<<" ";
    }
}

bool check_cauldron_color( card* cauldron , int cauldron_size)
{
    int color_id=-1;                                            // -1 => not set yet //
    for(int i=0 ; i<cauldron_size ; i++)
    {
        if(cauldron[i].color_id != 0)
        {
            if(color_id == -1) { color_id = cauldron[i].color_id; }
            if(cauldron[i].color_id != color_id) { return false; }
        }
    }
    return true;
}

bool check_cauldron_tnt( card* cauldron , int cauldron_size, int tnt_threshold)
{
    int sum_value=0;
    for(int i=0 ; i<cauldron_size ; i++)
    {
        sum_value += cauldron[i].value;
    }
    //cout<<"thr: "<<tnt_threshold<<" sum: "<<sum_value<<endl;
    if(sum_value >= tnt_threshold) { return false; }
    return true;
}

int check_cauldron_color_id( card* cauldron , int cauldron_size)
{
    for(int i=0 ; ; i++)
    {
        if(cauldron[i].color_id != 0)
        {
            return cauldron[i].color_id;
            break;
        }
    }
    return 0;
}

void add_to_deck( card* deck , card active_card , int &deck_size)
{
    bool found_slot=false;
    for(int i=0 ; i<deck_size ; i++)
    {
        if(deck[i].value == -1)
        {
            deck[i].value    = active_card.value;
            deck[i].color_id = active_card.color_id;
            found_slot=true;
        }
    }
    if(found_slot == false )
    {
        deck[ deck_size ].value    = active_card.value;
        deck[ deck_size ].color_id = active_card.color_id;
        deck_size++;
    }
}

void print_game_state( card** players_cards , int* players_card_C , card** cauldrons_cards , int* cauldrons_cards_C , int active_player)
{
    cout<<"active player = "<<active_player<<endl;
    cout<<"players number = "<<game_settings.players_C<<endl;
    cout<<"explosion threshold = "<<game_settings.explosion_threshold<<endl;
    for(int i=0 ; i<game_settings.players_C * 2 ; i++)
    {
        cout<<(i/2)+1<<" player ";
        if(i%2==0) { cout<<"hand"; }
        else       { cout<<"deck"; }
        cout<<" cards: ";

        print_cards( players_cards[i] , players_card_C[i]);
        cout<<endl;
    }
    for(int i=0 ; i<game_settings.color_C ; i++)
    {
        cout<<i+1<<" pile cards: ";

        print_cards( cauldrons_cards[i] , cauldrons_cards_C[i]);
        cout<<endl;
    }
}

void card_array_sort( card* deck , int deck_size)
{
    card active_card;
    int ac_address;
    for(int i=deck_size-1 ; i>0 ; i--)
    {
        active_card.color_id    = deck[i].color_id;
        active_card.value       = deck[i].value;
        ac_address = i;

        for(int j=i-1 ; j>=0 ; j--)
        {
            if( deck[j].color_id > deck[i].color_id )
            {
                ac_address = j;
            }
            if( deck[j].color_id = active_card.color_id)
            {
                if( deck[j].value > deck[i].value )
                {
                    ac_address = j;
                }
            }

            active_card.color_id = deck[i].color_id;
            active_card.value    = deck[i].value;

            deck[i].color_id = deck[ ac_address ].color_id;
            deck[i].value    = deck[ ac_address ].value;

            deck[ ac_address ].color_id = active_card.color_id;
            deck[ ac_address ].value    = active_card.value;
        }
    }
}

void sort_game_arrays( card** players_cards , int* players_card_C , card** cauldrons_cards , int* cauldrons_cards_C )
{
    for(int i=0 ; i<game_settings.players_C * 2 ; i++)
    {
        card_array_sort( players_cards[i] , players_card_C[i] );
    }
    for(int i=0 ; i<game_settings.color_C ; i++)
    {
        card_array_sort( cauldrons_cards[i] , cauldrons_cards_C[i] );
    }
}

void cauldron_explosion( card* cauldron , int cauldron_size , card* player , int &player_size )
{
    for(int i=0 ; i<cauldron_size ; i++)
    {
        add_to_deck( player , cauldron[i] , player_size);
        cauldron[i].value = -1;                                     // -1 => empty slot //
    }
}

void count_points( card** players_cards , int* players_cards_C )
{
    //cout<<"TAK"<<endl;
    int* score = new int [ game_settings.players_C ];
    int** tab = new int *[ game_settings.players_C ];
    for(int i=0 ; i<game_settings.players_C ; i++)
    {
        //cout<<"NIETAK"<<endl;
        tab[i] = new int [ game_settings.color_C + 1 ];
        for(int j=0 ; j<game_settings.color_C + 1 ; j++)
        {
            tab[i][j]=0;
        }
    }
    //cout<<"noelo"<<endl;


    for(int i=0 ; i<game_settings.players_C ; i++)
    {
        for(int j=0 ; j<players_cards_C[(i+1)*2-1] ; j++)
        {
            //cout<<"line: "<<(i+1)*2-1<<endl;
            tab[i][ players_cards[ (i+1)*2-1 ][j].color_id ]++;                 // to land on right slot //
        }
    }

    /*
    for(int i=0 ; i<game_settings.players_C ; i++)
    {
        for(int j=0 ; j<game_settings.color_C + 1 ; j++)
        {
            cout<<tab[i][j]<<" ";
        }
        cout<<endl;
    }*/
    //cout<<"LOG: colors counted"<<endl;
    //cout<<"COLROS: "<<game_settings.color_C<<endl;

    int* immunity = new int [ game_settings.color_C  ];
    for(int i=0 ; i<game_settings.color_C ; i++)
    {
        immunity[i]=-1;
    }

    int max_color=0, curr_color=0;

    //cout<<"shufling max colors"<<endl;
    for(int i=0 ; i<game_settings.color_C ; i++)
    {
        max_color=0;
        //cout<<"curr color: "<<i<<endl;
        for(int j=0 ; j<game_settings.players_C ; j++)
        {
            //cout<<"pl: "<<j+1<<endl;
            curr_color=0;
            for(int k=0 ; k<players_cards_C[j*2+1] ; k++)
            {
                //cout<<players_cards[j*2+1][k].color_id<<endl;
                if(players_cards[ j*2+1 ][k].value == -1) { continue; }
                if(players_cards[j*2+1][k].color_id == i+1)
                {
                    curr_color++;
                }
            }
            //cout<<"curr_count: "<<curr_color<<endl;
            if(curr_color == max_color)
            {
                immunity[i]=-1;
            }
            if(curr_color > max_color)
            {
                max_color = curr_color;
                immunity[i]=j;
                //cout<<"imm "<<i<<" get: "<<immunity[i]<<" with: "<<max_color<<endl;
            }
        }
    }

    //cout<<"max colors shuffled"<<endl;
    for(int i=0 ; i<game_settings.color_C ; i++)
    {
        if(immunity[i] != -1)
        {
            cout<<"Na kolor ";
            cout<<available_colors.names[ i+1 ];
            cout<<" odporny jest gracz "<<immunity[i]+1<<endl;
        }
    }

    //cout<<"color immunity set"<<endl;
    //cout<<"calculating player score"<<endl;

    for(int i=0 ; i<game_settings.players_C ; i++)
    {
        score[i]=0;
        for(int j=0 ; j<=game_settings.color_C ; j++)
        {
            //cout<<i+1<<" score: "<<score[i]<<endl;
            if(j>0&&immunity[j-1] == i) { continue; }
            if(j==0)
            {
                score[i] += tab[i][j]*2;
            }
            else
            {
                score[i] += tab[i][j];
            }
        }
    }

    //cout<<"LOG: scores set"<<endl;
    for(int i=0 ; i<game_settings.players_C ; i++)
    {
        cout<<"Wynik gracza "<<i+1<<" = "<<score[i]<<endl;
    }

}

void task_1()
{
    set_game_settings( 1 );
    int* card_values = new int [ game_settings.spec_color_C ];

    for(int i=0 ; i<game_settings.spec_color_C ; i++)
    {
        cin>>card_values[i];
    }


    for(int i=0 ; i<game_settings.green_C ; i++)
    {
        cout<<game_settings.green_V<<" "<<available_colors.names[ 0 ]<<" ";
    }

    for(int i=1 ; i<=game_settings.color_C ; i++) // i=1 => without green //
    {
        for(int j=0 ; j<game_settings.spec_color_C ; j++)
        {
            cout<<card_values[j]<<" "<<available_colors.names[ i ]<<" ";
        }
    }
}

void task_2()
{
    set_game_settings( 2 );

    card** players_hands;
    //initiate_deck( players_hands );
    players_hands = new card *[ game_settings.players_C ];
    for(int i=0 ; i<game_settings.players_C ; i++)
    {
        players_hands[i] = new card [ game_settings.color_C * game_settings.spec_color_C + game_settings.green_C ];
    }

    int* card_values = new int [ game_settings.spec_color_C ];
    for(int i=0 ; i<game_settings.spec_color_C ; i++)
    {
        cin>>card_values[i];
    }
    //cout<<"cards values acquired"<<endl;

    int* player_hand_C = new int [ game_settings.players_C ];
    for(int i=0 ; i<game_settings.players_C ; i++)
    {
        player_hand_C[ i ] = 0;                             // each player starts with no cards //
    }
    //cout<<"player_hand_C array zeroed"<<endl;


    int temp=0;
    for(int i=0 ; i<game_settings.green_C ; i++)
    {
        players_hands[ temp ][ player_hand_C[temp] ].value = game_settings.green_V;
        players_hands[ temp ][ player_hand_C[temp] ].color_id = 0;                    // 0 - green id //
        player_hand_C[ temp ]++;
        temp++;
        if( temp==game_settings.players_C ) { temp=0; }    // temp=0 to start giving cards to first player again //
    }
    //cout<<"green cards dealt"<<endl;

    for(int i=1 ; i<=game_settings.color_C ; i++)           // i=1 => without green //
    {
        for(int j=0 ; j<game_settings.spec_color_C ; j++)
        {
            players_hands[ temp ][ player_hand_C[temp] ].value = card_values[ j ];
            players_hands[ temp ][ player_hand_C[temp] ].color_id = i;              // i - color id //
            player_hand_C[ temp ]++;
            temp++;
            if( temp==game_settings.players_C ) { temp=0; } // temp=0 to start giving cards to first player again //
        }
    }

    /////////////////////////

    cout<<"active player = 1"<<endl;
    cout<<"players number = "<<game_settings.players_C<<endl;
    for(int i=0 ; i<game_settings.players_C ; i++)
    {
        cout<<i+1<<" player hand cards: ";
        print_cards( players_hands[ i ], player_hand_C[ i ] );
        cout<<endl<<i+1<<" player deck cards:"<<endl;
    }
    for(int i=0 ; i<game_settings.color_C ; i++)
    {
        cout<<i+1<<" pile cards:"<<endl;
    }
}

void task_3a()
{
    int line_L = MAX_INPUT_LINE_LENGTH;
    char* input_line = new char [ line_L ];
    int temp;

    cin.getline( input_line , line_L );
    cin.getline( input_line , line_L );
    temp = find_last_char_address( input_line );
    game_settings.players_C = input_line[ temp ]-ASCII_TABLE_0_SPOT;

    int* players_hands_C = new int [ game_settings.players_C ];
    int* players_decks_C = new int [ game_settings.players_C ];
    for(int i=0 ; i<game_settings.players_C ; i++)
    {
        players_hands_C[ i ] = 0;
        players_decks_C[ i ] = 0;
    }

    for(int i=0 ; i<game_settings.players_C ; i++)
    {
        cin.getline( input_line , line_L );
        for(int j=1 ; ; j++)                            // j=1 => dont count first digit on input //
        {
            if( input_line[ j ]==0 ) { break; }
            if( is_digit( input_line[ j ] ) && !is_digit( input_line[ j-1 ] )) { players_hands_C[ i ]++; }
        }

        cin.getline( input_line , line_L );
        for(int j=1 ; ; j++)                            // j=1 => dont count first digit on input //
        {
            if( input_line[ j ]==0 ) { break; }
            if( is_digit( input_line[ j ] ) && !is_digit( input_line[ j-1 ] )) { players_decks_C[ i ]++; }
        }
    }

    for(int i=0 ; i<game_settings.players_C ; i++)
    {
        cout<<i+1<<" player has "<<players_hands_C[ i ]<<" cards on hand"<<endl;
        cout<<i+1<<" player has "<<players_decks_C[ i ]<<" cards in front of him"<<endl;
    }
}

void task_3b()
{
    int line_L = MAX_INPUT_LINE_LENGTH;
    char* input_line = new char [ line_L ];
    int temp;

    cin.getline( input_line , line_L );
    cin.getline( input_line , line_L );
    temp = find_last_char_address( input_line );
    game_settings.players_C = input_line[ temp ]-ASCII_TABLE_0_SPOT;
    card* cards_received = new card [ 1000000 ];

    //cout<<"aquired players number: "<<game_settings.players_C<<endl;

    int* players_hands_C = new int [ game_settings.players_C ];
    int* players_decks_C = new int [ game_settings.players_C ];

    bool* colors_found = new bool [ OVERALL_COLORS_COUNT ];
    for(int i=0 ; i<OVERALL_COLORS_COUNT ; i++)
    {
        colors_found[ i ] = false;
    }

    //cout<<"initialized first section"<<endl;

    for(int i=0 ; i<game_settings.players_C ; i++)
    {
        cin.getline( input_line , line_L );
        temp = interpret_input( input_line , cards_received , 20 );             // 21 is starting point for reading players hand and deck cards //
        //cout<<"cards found: "<<temp<<endl;
        players_hands_C[ i ] = temp;
        find_colors( colors_found , cards_received , players_hands_C[ i ] );              // marking which colors appeared in input //

        cin.getline( input_line , line_L );
        temp = interpret_input( input_line , cards_received , 20 );
        //cout<<"cards found: "<<temp<<endl;
        players_decks_C[ i ] = temp;
        find_colors( colors_found , cards_received , players_decks_C[ i ] );
    }

    game_settings.color_C = count_colors( colors_found );
    int* cauldrons_cards_C = new int [ game_settings.color_C ];

    for(int i=0 ; i<game_settings.color_C ; i++)                                          // not counting green //
    {
        cin.getline( input_line , line_L );
        temp = interpret_input( input_line , cards_received , 13 );         // 13 is starting point for reading pile cards //
        cauldrons_cards_C[ i ] = temp;
        //cout<<"cards  found: "<<temp<<endl;
    }

    for(int i=0 ; i<game_settings.players_C ; i++)
    {
        cout<<i+1<<" player has "<<players_hands_C[ i ]<<" cards on hand"<<endl;
        cout<<i+1<<" player has "<<players_decks_C[ i ]<<" cards in front of him"<<endl;
    }
    for(int i=0 ; i<game_settings.color_C ; i++)                                          // not counting green //
    {
        cout<<"there are "<<cauldrons_cards_C[ i ]<<" cards on "<<i+1<<" pile"<<endl;
    }
}

void task_4a()
{
    int line_L = MAX_INPUT_LINE_LENGTH;
    char* input_line = new char [ line_L ];
    int temp;

    game_settings.green_C = 0;
    game_settings.green_V = -1;                             // -1 => sign that no green values has been found yet //
    bool diff_green_found = false;

    cin.getline( input_line , line_L );
    cin.getline( input_line , line_L );
    temp = find_last_char_address( input_line );
    game_settings.players_C = input_line[ temp ]-ASCII_TABLE_0_SPOT;
    card* cards_received = new card [ 1000000 ];

    //cout<<"aquired players number: "<<game_settings.players_C<<endl;

    int* players_hands_C = new int [ game_settings.players_C ];
    int* players_decks_C = new int [ game_settings.players_C ];

    bool* colors_found = new bool [ OVERALL_COLORS_COUNT ];
    for(int i=0 ; i<OVERALL_COLORS_COUNT ; i++)
    {
        colors_found[ i ] = false;
    }

    //cout<<"initialized first section"<<endl;

    for(int i=0 ; i<game_settings.players_C ; i++)
    {
        cin.getline( input_line , line_L );
        temp = interpret_input( input_line , cards_received , 20 );             // 21 is starting point for reading players hand and deck cards //
        //cout<<"cards found: "<<temp<<endl;
        players_hands_C[ i ] = temp;
        find_colors( colors_found , cards_received , players_hands_C[ i ] );              // marking which colors appeared in input //

        if( diff_green_found==false )
        {
            for(int j=0 ; j<players_hands_C[ i ] ; j++)
            {
                if(cards_received[ j ].color_id == 0)
                {
                    game_settings.green_C++;
                    //cout<<"greenC: "<<game_settings.green_C<<" : "<<cards_received[j].value<<endl;
                    if( game_settings.green_V == -1 ) { game_settings.green_V = cards_received[ j ].value; }
                    if( cards_received[ j ].value != game_settings.green_V )
                    {
                        diff_green_found=true;
                        break;
                    }
                }
            }
        }

        cin.getline( input_line , line_L );
        temp = interpret_input( input_line , cards_received , 20 );
        //cout<<"cards found: "<<temp<<endl;
        players_decks_C[ i ] = temp;
        find_colors( colors_found , cards_received , players_decks_C[ i ] );

        if( diff_green_found==false )
        {
            for(int j=0 ; j<players_decks_C[ i ] ; j++)
            {
                if(cards_received[ j ].color_id == 0)
                {
                    game_settings.green_C++;
                    //cout<<"greenC: "<<game_settings.green_C<<" : "<<cards_received[j].value<<endl;
                    if( game_settings.green_V == -1 ) { game_settings.green_V = cards_received[ j ].value; }
                    if( cards_received[ j ].value != game_settings.green_V )
                    {
                        diff_green_found=true;
                        break;
                    }
                }
            }
        }
    }

    game_settings.color_C = count_colors( colors_found );
    int* cauldrons_cards_C = new int [ game_settings.color_C ];

    for(int i=0 ; i<game_settings.color_C ; i++)                                          // not counting green //
    {
        cin.getline( input_line , line_L );
        temp = interpret_input( input_line , cards_received , 13 );         // 13 is starting point for reading pile cards //
        cauldrons_cards_C[ i ] = temp;

        if( diff_green_found==false )
        {
            for(int j=0 ; j<cauldrons_cards_C[ i ] ; j++)
            {
                if(cards_received[ j ].color_id == 0)
                {
                    game_settings.green_C++;
                    //cout<<"greenC: "<<game_settings.green_C<<" : "<<cards_received[j].value<<endl;
                    if( game_settings.green_V == -1 ) { game_settings.green_V = cards_received[ j ].value; }
                    if( cards_received[ j ].value != game_settings.green_V )
                    {
                        diff_green_found=true;
                        break;
                    }
                }
            }
        }
        //cout<<"cards  found: "<<temp<<endl;
    }

    if( diff_green_found==false )
    {
        if(game_settings.green_C == 0 ) { cout<<"Green cards does not exist"<<endl; }
        else                            { cout<<"Found "<<game_settings.green_C<<" green cards, all with "<<game_settings.green_V<<" value"<<endl; }
    }
    else                                { cout<<"Different green cards values occurred"<<endl; }
}

void task_4b()
{
    int line_L = MAX_INPUT_LINE_LENGTH;
    char* input_line = new char [ line_L ];
    int temp;

    cin.getline( input_line , line_L );
    cin.getline( input_line , line_L );
    temp = find_last_char_address( input_line );
    game_settings.players_C = input_line[ temp ]-ASCII_TABLE_0_SPOT;
    card* cards_received = new card [ 1000000 ];

    int* players_hands_C = new int [ game_settings.players_C ];
    int* players_decks_C = new int [ game_settings.players_C ];

    int* colors_C = new int [ OVERALL_COLORS_COUNT ];
    bool* colors_found = new bool [ OVERALL_COLORS_COUNT ];
    for(int i=0 ; i<OVERALL_COLORS_COUNT ; i++)
    {
        colors_C[ i ] = 0;
        colors_found[ i ] = false;
    }

    //cout<<"initialized first section"<<endl;

    for(int i=0 ; i<game_settings.players_C ; i++)
    {
        cin.getline( input_line , line_L );
        temp = interpret_input( input_line , cards_received , 20 );             // 21 is starting point for reading players hand and deck cards //
        //cout<<"cards found: "<<temp<<endl;
        players_hands_C[ i ] = temp;
        find_colors( colors_found , cards_received , players_hands_C[ i ] );
        count_colors_number( colors_C , cards_received , players_hands_C[ i ] );              // marking which colors appeared in input //

        cin.getline( input_line , line_L );
        temp = interpret_input( input_line , cards_received , 20 );
        //cout<<"cards found: "<<temp<<endl;
        players_decks_C[ i ] = temp;
        find_colors( colors_found , cards_received , players_decks_C[ i ] );
        count_colors_number( colors_C , cards_received , players_decks_C[ i ] );
    }

    game_settings.color_C = count_colors( colors_found );
    int* cauldrons_cards_C = new int [ game_settings.color_C ];

    for(int i=0 ; i<game_settings.color_C ; i++)                                          // not counting green //
    {
        cin.getline( input_line , line_L );
        temp = interpret_input( input_line , cards_received , 13 );         // 13 is starting point for reading pile cards //
        cauldrons_cards_C[ i ] = temp;
        count_colors_number( colors_C , cards_received , cauldrons_cards_C[ i ] );
    }

    temp=-1;
    bool diff_number_found=false;
    for(int i=1 ; i<OVERALL_COLORS_COUNT ; i++)                             // i=1 => without green //
    {
        if(colors_C[ i ] != 0)
        {
            if(temp == -1) { temp = colors_C[ i ]; }
            if(colors_C[ i ] != temp) { diff_number_found=true; break; }
        }
        if(diff_number_found==true) { break; }
    }

    if(diff_number_found==true)
    {
        cout<<"At least two colors with a different number of cards were found:"<<endl;
        for(int i=1 ; i<OVERALL_COLORS_COUNT ; i++)
        {
            if(colors_C[ i ] != 0) { cout<<available_colors.names[ i ]<<" cards are "<<colors_C[ i ]<<endl;}
        }
    }
    else { cout<<"The number cards of all colors is equal: "<<colors_C[ 1 ]<<endl; }
}

void task_5()
{
    int line_L = MAX_INPUT_LINE_LENGTH;
    char* input_line = new char [ line_L ];
    int temp;                                                                   // additional variable                  //

    cin.getline( input_line , line_L );                                       //// first to lines of input              //
    cin.getline( input_line , line_L );                                         //
    temp = find_last_char_address( input_line );                                //
    game_settings.players_C = input_line[ temp ]-ASCII_TABLE_0_SPOT;          //// setting number of players in game    //

    //cout<<"input gathered"<<endl;

    card** players_cards = new card *[ game_settings.players_C * 2 ];         //// all players cards array              //
    for(int i=0 ; i<game_settings.players_C * 2 ; i++)                          //
    {                                                                           //
        players_cards[ i ] = new card [ 10000 ];                                //
    }                                                                         ////

    int* players_cards_C = new int [ game_settings.players_C * 2 ];             // number of cards in players hands     //

    int* spec_color_C = new int [ OVERALL_COLORS_COUNT ];                     //// number of specific cards in each color   //
    for(int i=0 ; i<OVERALL_COLORS_COUNT ; i++)                                 //
    {                                                                           //
        spec_color_C[ i ] = 0;                                                  //
    }                                                                         ////

    //cout<<"data generated"<<endl;
    ////////////////////////////////////////////////////////////////////

    for(int i=0 ; i<game_settings.players_C * 2 ; i++)
    {
        cin.getline( input_line , line_L );                                                   // reads input lines //
        players_cards_C[i] = interpret_input( input_line , players_cards[i] , 20 );           // counts cards in input & interprets it //                  // count how many times colors appeared in input //
    }

    for(int i=0 ; i<game_settings.players_C * 2 ; i++)
    {
        count_colors_number( spec_color_C , players_cards[i] , players_cards_C[i] );           // counts number of each card in specific color //
    }

    game_settings.color_C = count_colors_by_num( spec_color_C );                               // count how many color are in game without green//

    //cout<<"LOG: players input gathered"<<endl;
    //////////////////////////////////////////////////////////////////////////////////

    card** cauldrons_cards = new card *[ game_settings.color_C ];                         //// all cauldrons cards array                //
    for(int i=0 ; i<game_settings.color_C ; i++)                                            //
    {                                                                                       //
        cauldrons_cards[i] = new card [ 10000 ];                                            //
    }                                                                                     ////
    int* cauldrons_cards_C = new int   [ game_settings.color_C ];                         //// number of cards in each cauldron array   //
    for(int i=0 ; i<game_settings.color_C ; i++)                                            //
    {                                                                                       //
        cauldrons_cards_C[i] = 0;                                                           //
    }                                                                                     ////

    //cout<<"LOG: cauldrons generated"<<endl;
    //////////////////////////////////////////////////////////////////////////////////

    for(int i=0 ; i<game_settings.color_C ; i++)
    {
        cin.getline( input_line , line_L );
        cauldrons_cards_C[i] = interpret_input( input_line , cauldrons_cards[i] , 13 );     // 13 is starting point for reading pile cards //
    }

    for(int i=0 ; i<game_settings.color_C ; i++)
    {
        count_colors_number( spec_color_C , cauldrons_cards[i] , cauldrons_cards_C[i] );        // counts number of each card in specific color //
    }

    //cout<<"LOG: cauldrons input gathered"<<endl;

    //cout<<"LOG: colors found:"<<endl;
    for(int i=0 ; i<=game_settings.color_C ; i++)
    {
        //cout<<available_colors.names[i]<<" "<<spec_color_C[i]<<endl;
    }
    /////////////////////////////////////////////////

    temp=0;                                                                                   ////
    for(int i=0 ; i<OVERALL_COLORS_COUNT ; i++)                                                 // setting highest number of cards in same color //
    {                                                                                           //
        if(spec_color_C[i]>temp) { temp = spec_color_C[i]; }                                    //
    }                                                                                         ////

    int ** value_tab = new int *[OVERALL_COLORS_COUNT];                                       //// card values in specific colors array //
    for(int i=0 ; i<OVERALL_COLORS_COUNT ; i++)                                                 //
    {                                                                                           //
        value_tab[i] = new int [temp];                                                          //
    }                                                                                         ////



    for(int i=1 ; i<=game_settings.color_C ; i++)                                                // i=1 => without green //
    {
        //cout<<"color: "<<available_colors.names[i]<<" \t :";
        temp=0;                                                                                 // will account for putting card values into right addresses //
        for(int j=0 ; j<game_settings.players_C * 2 ; j++)
        {
            for(int k=0 ; k<players_cards_C[j] ; k++)
            {
                if( players_cards[j][k].color_id == i )
                {
                    value_tab[i][temp] = players_cards[j][k].value;
                    //cout<<value_tab[i][temp]<<" ";
                    temp++;
                }
            }
        }
        for(int j=0 ; j<game_settings.color_C ; j++)
        {
            for(int k=0 ; k<cauldrons_cards_C[j] ; k++)
            {
                if( cauldrons_cards[j][k].color_id == i )
                {
                    value_tab[i][temp] = cauldrons_cards[j][k].value;
                    //cout<<value_tab[i][temp]<<" ";
                    temp++;
                }
            }
        }
        //cout<<endl;
    }
    //cout<<"LOG: color cards scanned"<<endl;

    for(int i=1 ; i<=game_settings.color_C ; i++)
    {
        array_sort( value_tab[i] , spec_color_C[i] );
    }

    //////////////////////////////////////////////////

    bool different_values_found=false;
    for(int i=2 ; i<game_settings.color_C ; i++)
    {
        if(spec_color_C[i] != spec_color_C[i-1])
        {
            different_values_found=true;
            cout<<"The values of cards of all colors are not identical:"<<endl;
            break;
        }
    }

    if(different_values_found==false)
    {
        for(int i=0 ; i<spec_color_C[1] ; i++)
        {
            for(int j=2 ; j<game_settings.color_C ; j++)                          // j< ...[1] => every color has same count //
            {
                if( value_tab[j][i] != value_tab[j-1][i] )
                {
                    //cout<<"LOG: "<<j<<" "<<i<<" "<<value_tab[j][i]<<" "<<value_tab[j-1][i]<<endl;
                    different_values_found=true;
                    cout<<"The values of cards of all colors are not identical:"<<endl;
                    break;
                }
            }
            if(different_values_found==true) { break; }
        }
    }

    if(different_values_found==true)
    {
        for(int i=1 ; i<=game_settings.color_C ; i++)
        {
            cout<<available_colors.names[i]<<" cards values: ";
            for(int j=0 ; j<spec_color_C[i] ; j++)
            {
                cout<<value_tab[i][j]<<" ";
            }
            cout<<endl;
        }
    }
    else
    {
        cout<<"The values of cards of all colors are identical:"<<endl;
        for(int i=0 ; i<spec_color_C[1] ; i++)
        {
            cout<<value_tab[1][i]<<" ";
        }
    }

}

void task_6()
{
    int line_L = MAX_INPUT_LINE_LENGTH;
    char* input_line = new char [ line_L ];
    int temp;                                                                   // additional variable                  //

    cin.getline( input_line , line_L );                                       //// first two lines of input              //
    int active_player = interpret_last_digits( input_line );

    cin.getline( input_line , line_L );
    temp = interpret_last_digits( input_line );                                 //
    game_settings.players_C = temp;
                                                                                //// setting number of players in game    //
    cin.getline( input_line , line_L );                                         //
    temp = interpret_last_digits( input_line );                                //
    int tnt_threshold = temp;                                                 //// setting explosion threshold          //

    //cout<<"input gathered"<<endl;

    card** players_cards = new card *[ game_settings.players_C * 2 ];         //// all players cards array              //
    for(int i=0 ; i<game_settings.players_C * 2 ; i++)                          //
    {                                                                           //
        players_cards[ i ] = new card [ 10000 ];                                //
    }                                                                         ////

    int* players_cards_C = new int [ game_settings.players_C * 2 ];             // number of cards in players hands     //

    int* spec_color_C = new int [ OVERALL_COLORS_COUNT ];                     //// number of specific cards in each color   //
    for(int i=0 ; i<OVERALL_COLORS_COUNT ; i++)                                 //
    {                                                                           //
        spec_color_C[ i ] = 0;                                                  //
    }                                                                         ////

    //cout<<"data generated"<<endl;
    ////////////////////////////////////////////////////////////////////

    for(int i=0 ; i<game_settings.players_C * 2 ; i++)
    {
        cin.getline( input_line , line_L );                                                   // reads input lines //
        players_cards_C[i] = interpret_input( input_line , players_cards[i] , 20 );           // counts cards in input & interprets it //                  // count how many times colors appeared in input //
    }

    for(int i=0 ; i<game_settings.players_C * 2 ; i++)
    {
        count_colors_number( spec_color_C , players_cards[i] , players_cards_C[i] );           // counts number of each card in specific color //
    }

    game_settings.color_C = count_colors_by_num( spec_color_C );                               // count how many color are in game without green//

    //cout<<"LOG: players input gathered"<<endl;
    //////////////////////////////////////////////////////////////////////////////////

    card** cauldrons_cards = new card *[ game_settings.color_C ];                         //// all cauldrons cards array                //
    for(int i=0 ; i<game_settings.color_C ; i++)                                            //
    {                                                                                       //
        cauldrons_cards[i] = new card [ 10000 ];                                            //
    }                                                                                     ////
    int* cauldrons_cards_C = new int   [ game_settings.color_C ];                         //// number of cards in each cauldron array   //
    for(int i=0 ; i<game_settings.color_C ; i++)                                            //
    {                                                                                       //
        cauldrons_cards_C[i] = 0;                                                           //
    }                                                                                     ////

    //cout<<"LOG: cauldrons generated"<<endl;
    //////////////////////////////////////////////////////////////////////////////////

    for(int i=0 ; i<game_settings.color_C ; i++)
    {
        cin.getline( input_line , line_L );
        cauldrons_cards_C[i] = interpret_input( input_line , cauldrons_cards[i] , 13 );     // 13 is starting point for reading pile cards //
    }

    bool state_ok=true;
    int cards_used=0;
    int cards_all=0;
    for(int i=0 ; i<game_settings.players_C * 2 ; i++)
    {
        if(i%2==1) {cards_used += players_cards_C[i]; }
        cards_all += players_cards_C[i];
    }
    for(int i=0 ; i<game_settings.color_C ; i++)
    {
        cards_used += cauldrons_cards_C[i];
        cards_all  += cauldrons_cards_C[i];
    }
    //cout<<"LOG: all: "<<cards_all<<" used: "<<cards_used<<endl;

    int start_cards_count = cards_all / game_settings.players_C;
    int start_plus_one = cards_all % game_settings.players_C;

    int* start_count = new int [ game_settings.players_C ];
    for(int i=0 ; i<game_settings.players_C ; i++)
    {
        start_count[i] = start_cards_count;
        if(i < start_plus_one) { start_count[i]++; }
    }

    int end_cards_count = cards_used / game_settings.players_C;
    int end_plus_one = cards_used % game_settings.players_C;

    int* end_count = new int [ game_settings.players_C ];
    for(int i=0 ; i<game_settings.players_C ; i++)
    {
        end_count[i] = players_cards_C[i*2];
        end_count[i] += end_cards_count;
    }

    temp=0;
    for(int i=active_player-2 ; ; i--)
    {
        if(temp>=end_plus_one) { break; }
        if(i<0) { i=game_settings.players_C-1; }
        end_count[i]++;
        temp++;
    }


    for(int i=0 ; i<game_settings.players_C ; i++)
    {
        //cout<<"LOG: "<<start_count[i]<<" "<<end_count[i]<<endl;
        if(start_count[i] != end_count[i]) { state_ok=false; cout<<"The number of players cards on hand is wrong"<<endl; break; }
    }


    for(int i=0 ; i<game_settings.color_C ; i++)                                          //// checking if more than 1 color appeared //
    {                                                                                       // in one cauldron
        if(check_cauldron_color(cauldrons_cards[i] , cauldrons_cards_C[i]) == false)        //
        {                                                                                   //
            cout<<"Two different colors were found on the "<<i+1<<" pile"<<endl;            //
            state_ok=false;                                                                 //
        }                                                                                   //
    }                                                                                     ////

    for(int i=0 ; i<game_settings.color_C ; i++)
    {
        if( check_cauldron_tnt(cauldrons_cards[i] , cauldrons_cards_C[i] , tnt_threshold) == false )
        {
            cout<<"Pile number "<<i+1<<" should explode earlier"<<endl;
            state_ok=false;
        }
    }
    if(state_ok == true ) { cout<<"Current state of the game is ok"<<endl; }
}

void task_7a()
{
    int line_L = MAX_INPUT_LINE_LENGTH;
    char* input_line = new char [ line_L ];
    int temp;                                                                   // additional variable                  //

    cin.getline( input_line , line_L );                                       //// first two lines of input              //
    temp = interpret_last_digits( input_line );
    int active_player = temp;

    cin.getline( input_line , line_L );
    temp = interpret_last_digits( input_line );                                 //
    game_settings.players_C = temp;
                                                                                //// setting number of players in game    //
    cin.getline( input_line , line_L );                                         //
    temp = interpret_last_digits( input_line );                                //
    game_settings.explosion_threshold = temp;                                                 //// setting explosion threshold          //

    //cout<<"input gathered"<<endl;

    card** players_cards = new card *[ game_settings.players_C * 2 ];         //// all players cards array              //
    for(int i=0 ; i<game_settings.players_C * 2 ; i++)                          //
    {                                                                           //
        players_cards[ i ] = new card [ 10000 ];                                //
    }                                                                         ////

    int* players_cards_C = new int [ game_settings.players_C * 2 ];             // number of cards in players hands     //

    int* spec_color_C = new int [ OVERALL_COLORS_COUNT ];                     //// number of specific cards in each color   //
    for(int i=0 ; i<OVERALL_COLORS_COUNT ; i++)                                 //
    {                                                                           //
        spec_color_C[ i ] = 0;                                                  //
    }                                                                         ////

    //cout<<"data generated"<<endl;
    ////////////////////////////////////////////////////////////////////

    for(int i=0 ; i<game_settings.players_C * 2 ; i++)
    {
        cin.getline( input_line , line_L );                                                   // reads input lines //
        players_cards_C[i] = interpret_input( input_line , players_cards[i] , 20 );           // counts cards in input & interprets it //                  // count how many times colors appeared in input //
    }

    for(int i=0 ; i<game_settings.players_C * 2 ; i++)
    {
        count_colors_number( spec_color_C , players_cards[i] , players_cards_C[i] );           // counts number of each card in specific color //
    }

    game_settings.color_C = count_colors_by_num( spec_color_C );                               // count how many color are in game without green//

    //cout<<"LOG: players input gathered"<<endl;
    //////////////////////////////////////////////////////////////////////////////////

    card** cauldrons_cards = new card *[ game_settings.color_C ];                         //// all cauldrons cards array                //
    for(int i=0 ; i<game_settings.color_C ; i++)                                            //
    {                                                                                       //
        cauldrons_cards[i] = new card [ 10000 ];                                            //
    }                                                                                     ////
    int* cauldrons_cards_C = new int   [ game_settings.color_C ];                         //// number of cards in each cauldron array   //
    for(int i=0 ; i<game_settings.color_C ; i++)                                            //
    {                                                                                       //
        cauldrons_cards_C[i] = 0;                                                           //
    }                                                                                     ////

    //cout<<"LOG: cauldrons generated"<<endl;
    //////////////////////////////////////////////////////////////////////////////////

    for(int i=0 ; i<game_settings.color_C ; i++)
    {
        cin.getline( input_line , line_L );
        cauldrons_cards_C[i] = interpret_input( input_line , cauldrons_cards[i] , 13 );     // 13 is starting point for reading pile cards //
    }

    /////////////////////////////////////////

    card active_card;
    for(int i=0 ; i<players_cards_C[ (active_player-1)*2 ]; i++)                        // players_cards_C is array for both hands and decks //
    {
        if(players_cards[ (active_player-1)*2 ][i].value != -1)
        {
            active_card.value    = players_cards[ (active_player-1)*2 ][i].value;
            active_card.color_id = players_cards[ (active_player-1)*2 ][i].color_id;
            players_cards [ (active_player-1)*2 ][i].value = -1;                              // -1 => empty slot //
            break;
        }
    }

    if(active_card.color_id==0) { add_to_deck( cauldrons_cards[0] , active_card , cauldrons_cards_C[0]); }
    else
    {
        int cauldron_id;
        for(int i=0 ; i<game_settings.color_C ; i++)
        {
            cauldron_id = check_cauldron_color_id( cauldrons_cards[i] , cauldrons_cards_C[i]);
            if(cauldron_id == 0 || cauldron_id == active_card.color_id)
            {
                add_to_deck( cauldrons_cards[i] , active_card , cauldrons_cards_C[i]);
            }
        }
    }

    if(active_player == game_settings.players_C) { active_player=0; }
    active_player++;
    print_game_state( players_cards , players_cards_C , cauldrons_cards , cauldrons_cards_C , active_player);

}

void task_7b()
{
    int line_L = MAX_INPUT_LINE_LENGTH;
    char* input_line = new char [ line_L ];
    int temp;                                                                   // additional variable                  //

    cin.getline( input_line , line_L );                                       //// first two lines of input              //
    temp = interpret_last_digits( input_line );
    int active_player = temp;

    cin.getline( input_line , line_L );
    temp = interpret_last_digits( input_line );                                 //
    game_settings.players_C = temp;
                                                                                //// setting number of players in game    //
    cin.getline( input_line , line_L );                                         //
    temp = interpret_last_digits( input_line );                                //
    game_settings.explosion_threshold = temp;                                                 //// setting explosion threshold          //

    //cout<<"input gathered"<<endl;

    card** players_cards = new card *[ game_settings.players_C * 2 ];         //// all players cards array              //
    for(int i=0 ; i<game_settings.players_C * 2 ; i++)                          //
    {                                                                           //
        players_cards[ i ] = new card [ 10000 ];                                //
    }                                                                         ////

    int* players_cards_C = new int [ game_settings.players_C * 2 ];             // number of cards in players hands     //

    int* spec_color_C = new int [ OVERALL_COLORS_COUNT ];                     //// number of specific cards in each color   //
    for(int i=0 ; i<OVERALL_COLORS_COUNT ; i++)                                 //
    {                                                                           //
        spec_color_C[ i ] = 0;                                                  //
    }                                                                         ////

    //cout<<"data generated"<<endl;
    ////////////////////////////////////////////////////////////////////

    for(int i=0 ; i<game_settings.players_C * 2 ; i++)
    {
        cin.getline( input_line , line_L );                                                   // reads input lines //
        players_cards_C[i] = interpret_input( input_line , players_cards[i] , 20 );           // counts cards in input & interprets it //                  // count how many times colors appeared in input //
    }

    for(int i=0 ; i<game_settings.players_C * 2 ; i++)
    {
        count_colors_number( spec_color_C , players_cards[i] , players_cards_C[i] );           // counts number of each card in specific color //
    }

    game_settings.color_C = count_colors_by_num( spec_color_C );                               // count how many color are in game without green//

    //cout<<"LOG: players input gathered"<<endl;
    //////////////////////////////////////////////////////////////////////////////////

    card** cauldrons_cards = new card *[ game_settings.color_C ];                         //// all cauldrons cards array                //
    for(int i=0 ; i<game_settings.color_C ; i++)                                            //
    {                                                                                       //
        cauldrons_cards[i] = new card [ 10000 ];                                            //
    }                                                                                     ////
    int* cauldrons_cards_C = new int   [ game_settings.color_C ];                         //// number of cards in each cauldron array   //
    for(int i=0 ; i<game_settings.color_C ; i++)                                            //
    {                                                                                       //
        cauldrons_cards_C[i] = 0;                                                           //
    }                                                                                     ////

    //cout<<"LOG: cauldrons generated"<<endl;
    //////////////////////////////////////////////////////////////////////////////////

    for(int i=0 ; i<game_settings.color_C ; i++)
    {
        cin.getline( input_line , line_L );
        cauldrons_cards_C[i] = interpret_input( input_line , cauldrons_cards[i] , 13 );     // 13 is starting point for reading pile cards //
    }

    /////////////////////////////////////////

    card active_card;
    for(int i=0 ; i<players_cards_C[ (active_player-1)*2 ]; i++)                        // players_cards_C is array for both hands and decks //
    {
        if(players_cards[ (active_player-1)*2 ][i].value != -1)
        {
            active_card.value    = players_cards[ (active_player-1)*2 ][i].value;
            active_card.color_id = players_cards[ (active_player-1)*2 ][i].color_id;
            players_cards [ (active_player-1)*2 ][i].value = -1;                              // -1 => empty slot //
            break;
        }
    }

    temp = 0;       // cauldron to check if exploded //
    if(active_card.color_id==0) { add_to_deck( cauldrons_cards[0] , active_card , cauldrons_cards_C[0]); temp=0; }
    else
    {
        int cauldron_id;
        for(int i=0 ; i<game_settings.color_C ; i++)
        {
            cauldron_id = check_cauldron_color_id( cauldrons_cards[i] , cauldrons_cards_C[i]);
            if(cauldron_id == 0 || cauldron_id == active_card.color_id)
            {
                add_to_deck( cauldrons_cards[i] , active_card , cauldrons_cards_C[i]);
                temp = i;
            }
        }
    }

    if ( check_cauldron_tnt(cauldrons_cards[ temp ] , cauldrons_cards_C[ temp ] , game_settings.explosion_threshold ) == false )
    {
        cauldron_explosion( cauldrons_cards[ temp ] , cauldrons_cards_C[ temp ] , players_cards[ (active_player-1)*2+1 ] , players_cards_C [ (active_player-1)*2+1 ]);
    }


    if(active_player == game_settings.players_C) { active_player=0; }
    active_player++;
    print_game_state( players_cards , players_cards_C , cauldrons_cards , cauldrons_cards_C , active_player);
}

void task_8()
{
    int line_L = MAX_INPUT_LINE_LENGTH;
    char* input_line = new char [ line_L ];
    int temp;                                                                   // additional variable                  //

    cin.getline( input_line , line_L );                                       //// active player input                  //
    temp = interpret_last_digits( input_line );                                 //
    int active_player = temp;                                                 ////

    cin.getline( input_line , line_L );                                       //// players number input                 //
    temp = interpret_last_digits( input_line );                                 //
    game_settings.players_C = temp;                                           ////

    cin.getline( input_line , line_L );                                       //// explosion threshold input            //
    temp = interpret_last_digits( input_line );                                 //
    game_settings.explosion_threshold = temp;                                 ////

    //cout<<"input gathered"<<endl;

    card** players_cards = new card *[ game_settings.players_C * 2 ];         //// all players cards array              //
    for(int i=0 ; i<game_settings.players_C * 2 ; i++)                          //
    {                                                                           //
        players_cards[ i ] = new card [ 10000 ];                                //
    }                                                                         ////

    int* players_cards_C = new int [ game_settings.players_C * 2 ];             // number of cards in players hands     //

    int* spec_color_C = new int [ OVERALL_COLORS_COUNT ];                     //// number of specific cards in each color   //
    for(int i=0 ; i<OVERALL_COLORS_COUNT ; i++)                                 //
    {                                                                           //
        spec_color_C[ i ] = 0;                                                  //
    }                                                                         ////

    //cout<<"data generated"<<endl;
    ////////////////////////////////////////////////////////////////////

    for(int i=0 ; i<game_settings.players_C * 2 ; i++)
    {
        cin.getline( input_line , line_L );                                                   // reads input lines //
        players_cards_C[i] = interpret_input( input_line , players_cards[i] , 20 );           // counts cards in input & interprets it //                  // count how many times colors appeared in input //
    }

    for(int i=0 ; i<game_settings.players_C * 2 ; i++)
    {
        count_colors_number( spec_color_C , players_cards[i] , players_cards_C[i] );           // counts number of each card in specific color //
    }

    game_settings.color_C = count_colors_by_num( spec_color_C );                               // count how many color are in game without green//

    //cout<<"LOG: players input gathered"<<endl;
    //////////////////////////////////////////////////////////////////////////////////

    card** cauldrons_cards = new card *[ game_settings.color_C ];                         //// all cauldrons cards array                //
    for(int i=0 ; i<game_settings.color_C ; i++)                                            //
    {                                                                                       //
        cauldrons_cards[i] = new card [ 10000 ];                                            //
    }                                                                                     ////
    int* cauldrons_cards_C = new int   [ game_settings.color_C ];                         //// number of cards in each cauldron array   //
    for(int i=0 ; i<game_settings.color_C ; i++)                                            //
    {                                                                                       //
        cauldrons_cards_C[i] = 0;                                                           //
    }                                                                                     ////

    //cout<<"LOG: cauldrons generated"<<endl;
    //////////////////////////////////////////////////////////////////////////////////

    for(int i=0 ; i<game_settings.color_C ; i++)
    {
        cin.getline( input_line , line_L );
        cauldrons_cards_C[i] = interpret_input( input_line , cauldrons_cards[i] , 13 );     // 13 is starting point for reading pile cards //
    }

    count_points( players_cards , players_cards_C );


}

int main()
{
    insert_available_colors();

    //task_1();
    //task_2();
    //task_3a();
    //task_3b();
    //task_4a();
    //task_4b();
    //task_5();
    //task_6();
    //task_7a();
    //task_7b();
    task_8();


    return 0;
}


