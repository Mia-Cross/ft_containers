#include <iostream>

int main()
{
    int yearsPassedSinceToday;
    int dogTrueAge;
    int catAge = 9;

    for (int dogAge = 9; dogAge < 20; dogAge++)
    {
        for (int years = 2; years < 10; years++)
        {
            if (dogAge - years == 2 * (catAge - years)
            && 2 * (dogAge - years + 1) == 3 * (catAge - years + 1))
            {
                dogTrueAge = dogAge;
                yearsPassedSinceToday = years;
            }
        }
    }
    std::cout << "The dog is " << dogTrueAge << " y/o today." << std::endl;
    std::cout << yearsPassedSinceToday << " years passed since." << std::endl;
}