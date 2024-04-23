#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;

char maximum(long long int count[], int n){
    long long int max = count[n-1];
    int index = n-1;
    for(int i = n-1; i >= 0; i--){
        if (count[i] >= max){
            max = count[i];
            index = i;
        }
    }
    return char(index+97);
}

char minimum(long long int count[], int n){
    long long int min = LLONG_MAX;
    int index = n-1;
    for(int i = n-1; i >= 0; i--){
        if (count[i] <= min && count[i] != 0){
            min = count[i];
            index = i;
        }
    }
    return char(index+97);
}


int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    char letter;
    long long int count[26] = {0};
    for(int i = 0; i < 2000000; i++){
        cin >> noskipws >> letter;
        letter = tolower(letter);
        if(int(letter) > 96 && int(letter) < 123){
                count[int(letter)-97]++;
           }
        if(letter == '^'){
            break;
        }
    }
    cout << maximum(count, 26)<< " " << minimum(count, 26);
    return 0;
}
