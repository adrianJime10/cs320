#include "generator.h"

int* no_locality()
{
    int* array = new int[10000];
    int i;
    for(i = 0; i < 10000; i++)
    {
        array[i] = rand() % 100;
    }
    return array;
}

int* eighty_twenty()
{
    int* array = new int[10000];
    int i;
    int rand_num;
    for(i = 0; i < 10000; i++)
    {
        rand_num = rand() % 100;
        if(rand_num < 20)
        {
            array[i] = rand() % (80) + 20;
        }
        else
        {
            array[i] = rand() % 20;
        }
    }
    return array;
}

int* looping()
{
    int* array = new int[10000];
    int i;
    int counter = 0;
    for(i = 0; i < 10000; i++)
    {
        if(counter == 50)
        {
            counter = 0;
        }
        array[i] = counter;
        counter++;
    }
    return array;
}
