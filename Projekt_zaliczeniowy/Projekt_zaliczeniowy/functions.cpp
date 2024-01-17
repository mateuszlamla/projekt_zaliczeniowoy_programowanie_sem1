#include <iostream>
#include <random>
#include <time.h>
#include <cstdlib>
using namespace std;

mt19937 generator(time(nullptr));
uniform_int_distribution<> distribution(1, 13);

void generate_card(int card_number[], char card_figure[], int idx)
{
    card_number[idx] = distribution(generator);
    //card_number[idx] = (rand() % 13) + 1;

    if (card_number[idx] == 11)
    {
        card_figure[idx] = 'J';
    }
    else if (card_number[idx] == 12)
    {
        card_figure[idx] = 'D';
    }
    else if (card_number[idx] == 13)
    {
        card_figure[idx] = 'K';
    }
    else if (card_number[idx] == 1)
    {
        card_figure[idx] = 'A';
    }
    else if (card_number[idx] == 10)
    {
        card_figure[idx] = 'T';
    }
    else if (card_number[idx] == 9)
    {
        card_figure[idx] = '9';
    }
    else if (card_number[idx] == 8)
    {
        card_figure[idx] = '8';
    }
    else if (card_number[idx] == 7)
    {
        card_figure[idx] = '7';
    }
    else if (card_number[idx] == 6)
    {
        card_figure[idx] = '6';
    }
    else if (card_number[idx] == 5)
    {
        card_figure[idx] = '5';
    }
    else if (card_number[idx] == 4)
    {
        card_figure[idx] = '4';
    }
    else if (card_number[idx] == 3)
    {
        card_figure[idx] = '3';
    }
    else if (card_number[idx] == 2)
    {
        card_figure[idx] = '2';
    }
}

int value_of_card(char card_figure[], int idx)
{
    int card_value{};
    if (card_figure[idx] == 'K' || card_figure[idx] == 'D' || card_figure[idx] == 'J' || card_figure[idx] == 'T')
    {
        card_value = 10;
    }
    else if (card_figure[idx] == '9')
    {
        card_value = 9;
    }
    else if (card_figure[idx] == '8')
    {
        card_value = 8;
    }
    else if (card_figure[idx] == '7')
    {
        card_value = 7;
    }
    else if (card_figure[idx] == '6')
    {
        card_value = 6;
    }
    else if (card_figure[idx] == '5')
    {
        card_value = 5;
    }
    else if (card_figure[idx] == '4')
    {
        card_value = 4;
    }
    else if (card_figure[idx] == '3')
    {
        card_value = 3;
    }
    else if (card_figure[idx] == '2')
    {
        card_value = 2;
    }
    else if (card_figure[idx] == 'A')
    {
        card_value = 11;
    }
    return card_value;
}

void cards_display(char card_figure[], int hit, int sum) 
{
    for (int i = 0; i < hit; i++)
    {
        cout << card_figure[i] << " ";
    }
    cout << "| Suma " << sum;
    cout << endl;
}

void clean_table_char(char tab[], int size)
{
    for (int i = 0; i < size; i++)
    {
        tab[i] = NULL;
    }
}

void clean_table_int(int tab[], int size)
{
    for (int i = 0; i < size; i++)
    {
        tab[i] = NULL;
    }
}
