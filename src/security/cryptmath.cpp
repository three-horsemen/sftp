#include <time.h>
int custom_rand()
{
	return (((time(NULL)%10)*(time(NULL)%100))%80)+1;
}
int mpmod(int base, int exponent, int modulus)
{
    if ((base < 1) || (exponent < 0) || (modulus < 1))
    {
        return(-1);
    }
    long result = 1;
    while (exponent > 0)
    {
        if ((exponent % 2) == 1)
        {
            result = (result * base) % modulus;
        }
        base = (base * base) % modulus;
        exponent = (int)(exponent / 2);
    }
    return (result);
}
int is_prime(int num)
{
    if((num & 1)==0)
        return num == 2;
    else
    {
        int i, limit = num/2 + 1;
        for (i = 3; i <= limit; i+=2){
            if (num % i == 0)
                return 0;
        }
    }
    return 1;
}
int next_pr(int num)
{
    int c;
    if(num < 2)
        c = 2;
    else if (num == 2)
        c = 3;
    else if(num & 1)
    {
        num += 2;
        c = is_prime(num) ? num : next_pr(num);
    }
    else
        c = next_pr(num-1);
    return c;
}
int rand_prime()
{
    int a = custom_rand()+2;
    do
    {
        a++;
        if(is_prime(a))
            break;
    }while(true);
    return a;
}

int rand_prime(int upper_limit)
{
    if(upper_limit <= 2)
        return 2;
    do
    {
        if(is_prime(upper_limit))
            break;
        upper_limit--;
    }while(true);
    return upper_limit;
}
