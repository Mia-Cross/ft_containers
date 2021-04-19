#include <map>
#include <iostream>

int main ()
{
    std::map<int, char> map;

    map[2] = '$';
    map[5] = '#';
    map[1] = '%';

    std::map<int,char>::iterator iter = map.begin();
    std::pair<int,char> pair = *iter;
    std::cout << "[expected] begin -> " << pair.first << "-" << pair.second << std::endl;
    iter--;
    pair = *iter;
    std::cout << "[expected] decrement begin -> " << pair.first << "-" << pair.second << std::endl;
    iter++;
    pair = *iter;
    std::cout << "[expected] reincrement begin -> " << pair.first << "-" << pair.second << std::endl;

}
