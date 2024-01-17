#include <iostream>
#include <random>
#include <time.h>
#include <cstdlib>
#include "header.h"

using namespace std;

int main()
{
    int player_chips{};
    int still_playing = 1;
    int buy_more{};
    int bet{};
    int size = 10;
    int *player_card_number = new int[size];
    int *croupier_card_number = new int[size];
    char *player_card_figure = new char[size];
    char *croupier_card_figure = new char[size];
    int player_choice{};
    int rebuy{}; 

    cout << "Witaj przy stole do blackjacka. \n Ile zetonow chcesz zakupic? ";
    cin >> player_chips;

    do
    {
        cout << "Obstawiasz: ";
        cin >> bet;
        cout << endl;
        if (bet <= 0)
        {
            cout << "Musisz cos obstawic." << endl;
        }
        else
        {
            if (player_chips - bet < 0)
            {
                cout << "Brak srodkow." << endl;
                cout << "Chcesz dokupic[1-tak, 0-nie]?" << endl;
                cin >> buy_more;
                if (buy_more == 0)
                {
                    break;
                }
                else
                {
                    cout << "Ile? ";
                    cin >> rebuy;
                    player_chips += rebuy;
                }
            }
            else if (player_chips - bet >= 0)
            {
                int player_sum{};
                int croupier_sum{};
                int croupier_hit = 2;
                int player_hit = 2;
                bool hand_not_over = true;
                int loops{};
                int temp_value{};
                char temp_figure{};
                int temp_number{};
                bool split_hand_not_over = true;
                int player_split_sum1{};
                int player_split_sum2{};
                int split_loops{};
                bool blackjack_split1{};
                bool blackjack_split2{};

                player_chips -= bet;

                //generating first and second card for player and croupier
                generate_card(player_card_number, player_card_figure, 0);
                player_sum = value_of_card(player_card_figure, 0);
                generate_card(croupier_card_number, croupier_card_figure, 0);
                croupier_sum = value_of_card(croupier_card_figure, 0);
                generate_card(player_card_number, player_card_figure, 1);
                player_sum += value_of_card(player_card_figure, 1);
                generate_card(croupier_card_number, croupier_card_figure, 1);
                croupier_sum += value_of_card(croupier_card_figure, 1);
             
                //cards display 
                cout << "Twoje karty: " << player_card_figure[0] << " " << player_card_figure[1] << " | Suma: " << player_sum << endl;
                cout << "Karta krupiera: " << croupier_card_figure[0] << " | Suma " << croupier_sum - value_of_card(croupier_card_figure, 1) << endl;
                do {
                    cout << "Twoje srodki: " << player_chips << endl;
                    cout << "Stand [1], Hit [2]";
                    if (loops < 1)
                    {
                        cout << ", Double down [3]";
                    }
                    if (player_card_figure[loops] == player_card_figure[loops+1])
                    {
                        cout << ", Split [4]";
                    }
                    cout << endl;
                    cin >> player_choice;
                    cout << endl;
                    if (player_choice == 1)         //Stand
                    {
                        if (player_sum != 21)
                        {
                            while (croupier_sum <= 16)  //generating croupier cards
                            {
                                generate_card(croupier_card_number, croupier_card_figure, croupier_hit);
                                croupier_sum += value_of_card(croupier_card_figure, croupier_hit);
                                croupier_hit++;
                            }
                        }

                        //cards display
                        cout << "Twoje karty: ";
                        cards_display(player_card_figure, player_hit, player_sum);
                        cout << "Karty krupiera: ";
                        cards_display(croupier_card_figure, croupier_hit, croupier_sum);               
                        cout << endl << endl;

                        if (player_sum == 21 && croupier_sum != 21) //blackjack(stand)
                        {
                            cout << "Blackjack! Wygrales " << 1.5 * bet;
                            player_chips += bet;
                            player_chips += 1.5 * bet;
                            hand_not_over = false;
                        }
                        else if (player_sum == croupier_sum && player_sum <= 21)    //draw(stand)
                        {
                            cout << "Remis";
                            player_chips += bet;
                            hand_not_over = false;
                        }
                        else if ((player_sum > croupier_sum && player_sum < 21) || (player_sum < 21 && croupier_sum > 21))  //win(stand)
                        {
                            cout << "Wygrales " << bet;
                            player_chips += bet;
                            player_chips += bet;
                            hand_not_over = false;
                        }
                        else if ((player_sum < croupier_sum && croupier_sum <= 21) || (player_sum > 21))   //lose(stand)
                        {
                            cout << "Przegrales " << bet;
                            hand_not_over = false;
                        }
                    }
                    else if (player_choice == 2)    //Hit
                    {
                        //generating player card
                        generate_card(player_card_number, player_card_figure, player_hit);
                        player_sum += value_of_card(player_card_figure, player_hit);
                        player_hit++;

                        //cards display
                        cout << "Twoje karty: ";
                        cards_display(player_card_figure, player_hit, player_sum);
                        cout << "Karta krupiera: " << croupier_card_figure[0] << " | Suma " << croupier_sum - value_of_card(croupier_card_figure, 1) << endl;

                        if (player_sum > 21) //lose(hit)
                        {
                            cout << "Przegrales " << bet;
                            hand_not_over = false;
                        }
                    }
                    else if (player_choice == 3 && loops < 1)    //Double down
                    {
                        if (player_chips - bet < 0)
                        {
                            cout << "Brak srodkow. ";
                            cout << "Chcesz dokupic[1-tak, 0-nie]?" << endl;
                            cin >> buy_more;
                            if (buy_more == 0)
                            {
                                break;
                            }
                            else
                            {
                                cout << "Ile? ";
                                cin >> rebuy;
                                player_chips += rebuy;
                            }
                        }
                        player_chips -= bet;

                        //generating player card
                        generate_card(player_card_number, player_card_figure, player_hit);
                        player_sum += value_of_card(player_card_figure, player_hit);
                        player_hit++;

                        //player cards display
                        cout << "Twoje karty: ";
                        cards_display(player_card_figure, player_hit, player_sum);
                        if (!player_sum > 21)//lose(dd)
                        {
                            while (croupier_sum <= 16)  // generating croupier cards 
                            {
                                generate_card(croupier_card_number, croupier_card_figure, croupier_hit);
                                croupier_sum += value_of_card(croupier_card_figure, croupier_hit);
                                croupier_hit++;
                            }
                        }

                        //croupier cards display
                        cout << "Karty krupiera: ";
                        cards_display(croupier_card_figure, croupier_hit, croupier_sum);
                        cout << endl << endl;

                        if (player_sum == croupier_sum && player_sum <= 21) //draw(dd)
                        {
                            cout << "Remis";
                            player_chips += 2 * bet;
                            hand_not_over = false;
                        }
                        else if ((player_sum > croupier_sum && player_sum <= 21) || (player_sum <= 21 && croupier_sum > 21))    //win(dd)
                        {
                            cout << "Wygrales " << 2 * bet;
                            player_chips += 2 * bet;
                            player_chips += 2 * bet;
                            hand_not_over = false;
                        }
                        else if ((player_sum < croupier_sum && croupier_sum <= 21) || (player_sum > 21))  //lose(dd)
                        {
                            cout << "Przegrales " << 2 * bet;
                            hand_not_over = false;
                        }
                    }
                    else if ((player_choice == 4) && (player_card_figure[loops] == player_card_figure[loops + 1]))    //Split
                    {
                        if (player_chips - bet < 0)
                        {
                            cout << "Brak srodkow. ";
                            cout << "Chcesz dokupic[1-tak, 0-nie]?" << endl;
                            cin >> buy_more;
                            if (buy_more == 0)
                            {
                                break;
                            }
                            else
                            {
                                cout << "Ile? ";
                                cin >> rebuy;
                                player_chips += rebuy;
                            }
                        }
                        player_chips -= bet;

                        
                        temp_value = value_of_card(player_card_figure, 1);
                        temp_figure = player_card_figure[1];
                        temp_number = player_card_number[1];
                        player_split_sum1 = value_of_card(player_card_figure, 0);
                        generate_card(player_card_number, player_card_figure, 1);
                        player_split_sum1 += value_of_card(player_card_figure, 1);

                        cout << "Pierwsze rozdanie" << endl;
                        //player cards display
                        cout << "Twoje karty: ";
                        cards_display(player_card_figure, player_hit, player_split_sum1);
                        
                        //croupier card display
                        cout << "Karta krupiera: " << croupier_card_figure[0] << " | Suma " << croupier_sum - value_of_card(croupier_card_figure, 1) << endl;

                        do {
                            cout << "Stand [1], Hit [2]";
                            cout << endl;
                            cin >> player_choice;
                            
                            if (player_choice == 1)         //Split Stand 1
                            {
                                if (player_split_sum1 == 21 && split_loops < 1)
                                {
                                    blackjack_split1 = true;
                                }
                                split_hand_not_over = false;
                            }
                            else if (player_choice == 2)    //Split Hit 1
                            {
                                //generating player card
                                generate_card(player_card_number, player_card_figure, player_hit);
                                player_split_sum1 += value_of_card(player_card_figure, player_hit);
                                player_hit++;

                                //cards display
                                cout << "Twoje karty: ";
                                cards_display(player_card_figure, player_hit, player_split_sum1);
                                cout << "Karta krupiera: " << croupier_card_figure[0] << " | Suma " << croupier_sum - value_of_card(croupier_card_figure, 1) << endl;

                                if (player_split_sum1 > 21) //lose(hit)
                                {
                                    cout << "Przegrales " << bet;
                                    split_hand_not_over = false;
                                }
                            }
                            split_loops++;
                        } while (split_hand_not_over);

                        cout << endl << endl;
                        split_loops = 0;
                        split_hand_not_over = true; 
                        player_hit = 2;
                        clean_table_char(player_card_figure, size);
                        clean_table_int(player_card_number, size);

                        player_card_figure[0] = temp_figure;
                        player_card_number[0] = temp_number;
                        player_split_sum2 = temp_value;

                        generate_card(player_card_number, player_card_figure, 1);
                        player_split_sum2 += value_of_card(player_card_figure, 1);

                        cout << "Drugie rozdanie" << endl;
                        //player cards display
                        cout << "Twoje karty: ";
                        cards_display(player_card_figure, player_hit, player_split_sum2);

                        //croupier card display
                        cout << "Karta krupiera: " << croupier_card_figure[0] << " | Suma " << croupier_sum - value_of_card(croupier_card_figure, 1) << endl;

                        do {
                            cout << "Stand [1], Hit [2]";
                            cout << endl;
                            cin >> player_choice;
                            cout << endl;
                            if (player_choice == 1)         //Split Stand 2
                            {
                                if (player_split_sum2 == 21 && split_loops < 1)
                                {
                                    blackjack_split2 = true;
                                }

                                split_hand_not_over = false;
                            }
                            else if (player_choice == 2)    //Split Hit 2
                            {
                                //generating player card
                                generate_card(player_card_number, player_card_figure, player_hit);
                                player_split_sum2 += value_of_card(player_card_figure, player_hit);
                                player_hit++;

                                //cards display
                                cout << "Twoje karty: ";
                                cards_display(player_card_figure, player_hit, player_split_sum2);
                                cout << "Karta krupiera: " << croupier_card_figure[0] << " | Suma " << croupier_sum - value_of_card(croupier_card_figure, 1) << endl;

                                if (player_split_sum2 > 21) //lose(hit)
                                {
                                    cout << "Przegrales " << bet;
                                    split_hand_not_over = false;
                                }
                            }
                            split_loops++;
                        } while (split_hand_not_over);
                        while (croupier_sum <= 16)  // generating croupier cards 
                        {
                            generate_card(croupier_card_number, croupier_card_figure, croupier_hit);
                            croupier_sum += value_of_card(croupier_card_figure, croupier_hit);
                            croupier_hit++;
                        }

                        cout << endl;
                        //croupier_cards_display
                        cout << "Karty krupiera: ";
                        cards_display(croupier_card_figure, croupier_hit, croupier_sum);
                        cout << endl ;

                        cout << "Pierwsze rozdanie: ";
                        if (blackjack_split1 == true && croupier_sum != 21) //blackjack(split 1)
                        {
                            cout << "Blackjack! Wygrales " << 1.5 * bet;
                            player_chips += bet;
                            player_chips += 1.5 * bet;
                            hand_not_over = false;
                        }
                        else if (player_split_sum1 == croupier_sum && player_split_sum1 <= 21)    //draw(split 1)
                        {
                            cout << "Remis";
                            player_chips += bet;
                            hand_not_over = false;
                        }
                        else if ((player_split_sum1 > croupier_sum && player_split_sum1 <= 21) || (player_split_sum1 <= 21 && croupier_sum > 21))  //win(split 1)
                        {
                            cout << "Wygrales " << bet;
                            player_chips += bet;
                            player_chips += bet;
                            hand_not_over = false;
                        }
                        else if ((player_split_sum1 < croupier_sum && croupier_sum <= 21) || (player_split_sum2 > 21))   //lose(split 1)
                        {
                            cout << "Przegrales " << bet;
                            hand_not_over = false;
                        }

                        cout << endl;
                        cout << "Drugie rozdanie: ";

                        if (blackjack_split2 == true && croupier_sum != 21) //blackjack(split 2)
                        {
                            cout << "Blackjack! Wygrales " << 1.5 * bet;
                            player_chips += bet;
                            player_chips += 1.5 * bet;
                            hand_not_over = false;
                        }
                        else if (player_split_sum2 == croupier_sum && player_split_sum2 <= 21)    //draw(split 2)
                        {
                            cout << "Remis";
                            player_chips += bet;
                            hand_not_over = false;
                        }
                        else if ((player_split_sum2 > croupier_sum && player_split_sum2 <= 21) || (player_split_sum2 <= 21 && croupier_sum > 21))  //win(split 2)
                        {
                            cout << "Wygrales " << bet;
                            player_chips += bet;
                            player_chips += bet;
                            hand_not_over = false;
                        }
                        else if ((player_split_sum2 < croupier_sum && croupier_sum <= 21) || (player_split_sum2 > 21))   //lose(split 2)
                        {
                            cout << "Przegrales " << bet;
                            hand_not_over = false;
                        }     
                    }
                    else    //wrong data
                    {
                        cout << "Bledne dane"<< endl;
                        cout << "Omijasz rozdanie";
                        player_chips += bet;
                        hand_not_over = false;
                    }
                    cout << endl;
                    loops++;
                } while (hand_not_over);
            }
        }
        cout << "Twoje srodki: " << player_chips << endl;
        cout << "Grasz dalej?[1-tak 0-nie]" << endl;
        cin >> still_playing;
        while (still_playing != 0 && still_playing != 1)
        {
            cout << "Bledne dane" << endl;
            cout << "Grasz dalej?[1-tak, 0-nie]" << endl;
            cin >> still_playing;
        }
    } while (still_playing);
}