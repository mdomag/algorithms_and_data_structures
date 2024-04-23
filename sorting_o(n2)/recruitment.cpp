#include <iostream>
#include <cmath>
using namespace std;

struct person{
    string name;
    long int t; //czas do przekonania
};

void insertion_sort(person arr[], int n){
    int j, tkey;
    string namekey;
    for (int i = 1; i < n; i++) {
        tkey = arr[i].t;
        namekey = arr[i].name;
        j = i - 1;
        while (j >= 0 && (arr[j].t < tkey || (arr[j].t == tkey && arr[j].name > namekey))) {
            arr[j+1] = arr[j];
            j = j - 1;
        }
        arr[j+1].t = tkey;
        arr[j+1].name = namekey;
    }
}

void time(person arr[], int n, int p){
    insertion_sort(arr, n);
    long long int count = 0;
    for(int i = 0; i < n; i++){
        if(i == 0){
            count += 1;
        }
        else{
            count += 1+arr[i].t*i;
        }
    }
    count = count%((long long int)(pow(10, 6)+3));
    for(int i = 0; i < p; i++){
        cout << arr[i].name << " ";
    }
    cout << "\n" << count << "\n";
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t; //liczba zestawow danych
    int n; // liczba nazwisk
    int p; //liczba nazwisk do wyswietlenia

    cin >> t;

    for(int i = 0; i < t; i++){
        cin >> n >> p;
        person *arr = new person[n];
        for(int j = 0; j < n; j++){
            cin >> arr[j].name >> arr[j].t;
        }
        time(arr, n, p);
        delete[] arr;
    }
    return 0;
}
