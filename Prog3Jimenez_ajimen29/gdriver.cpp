#include "generator.cpp"
#include "pgr.cpp"

int main()
{
    srand(time(NULL));
    int i;
    
    int* nums;
    
    nums = no_locality();
    cout << "NO LOCALITY" << endl;

    writeNoLocal(nums, opt(nums), lru(nums), fifo(nums), random_pgr(nums), clock_pgr(nums));

    cout << endl;
    cout << "80-20" << endl;
    nums = eighty_twenty();

    write8020(nums, opt(nums), lru(nums), fifo(nums), random_pgr(nums), clock_pgr(nums));

    cout << endl;
    cout << "LOOPING" << endl;
    nums = looping();

    writeLooping(nums, opt(nums), lru(nums), fifo(nums), random_pgr(nums), clock_pgr(nums));

    cout << endl;
    
    delete nums;
    return 0;
}
