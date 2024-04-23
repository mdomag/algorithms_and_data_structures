#include <iostream>
#include <algorithm>

using namespace std;

struct car{
    string name;
    long int mileage;
};

bool compare(car &a, car &b) {
    if (a.mileage < b.mileage) {
        return true;
    } else if (a.mileage == b.mileage) {
        return a.name < b.name;
    }
    return false;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n = 0;
    string name;
    long int d;
    long double p;
    bool flag;
    long int mileage;
    car array[4];
    cin >> n;

    for(int i = 0; i < n; i++){
        flag = false;
        cin.ignore();
        getline(cin, name);
        cin >> p >> d;
        mileage = p/(d*0.0000254*3.141593);
       if(i < 3){
            array[i].name = name;
            array[i].mileage = mileage;
            if(i == 2){
                    sort(array, array+3, compare);
            }
        }
        else{
            for(int i = 0; i < 3; i++){
                if(mileage < array[i].mileage || (mileage == array[i].mileage && name < array[i].name)){
                    array[3].name = name;
                    array[3].mileage = mileage;
                    sort(array, array+4, compare);
                    break;
                }
            }

        }
    }

    for(int i = 0; i < 3; i++){
        cout << array[i].name << "\n" << array[i].mileage << "\n";
     }

    return 0;
}
