#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
using namespace std;
class MergeClass
{
private:
    void Merge(vector<int>& array, vector<int>& partL, vector<int>& partR) {
        int i = 0; int j = 0; int w = 0;
        while (i < partL.size() || j < partR.size()) {
            if (j >= partR.size() || (i < partL.size() && partL[i] <= partR[j])) {
                array[w++] = partL[i++];
            }
            else {
                array[w++] = partR[j++];
            }
        }
        int a = partL.size();
        int b = partR.size();
        while (i < a) {
            i++;
            w++;
            array[w] = partL[i];
        }
        while (j < b) {
            j++;
            w++;
            array[w] = partR[j];
        }
       

    }

public:
    void MerrgeSort(vector<int>& array) {
        if (array.size() <= 1) 
        {
            return; 
        }

        size_t seredin = array.size() / 2;
        vector<int> partL(array.begin(), array.begin() + seredin);
        vector<int> partR(array.begin() + seredin, array.end());

        auto leftSort = [&partL, this]() { MerrgeSort(partL);};
        thread goSortLeft(leftSort);

        auto rightSort = [&partR, this]() { MerrgeSort(partR);};
        thread goSortRight(rightSort);

        goSortLeft.join();
        goSortRight.join();
        Merge(array, partL, partR);
    }
};

int main() 
{
    setlocale(LC_ALL, "Rus");

    vector<int> exampleArr;
    int Counter = 0;
    while (Counter < 10)
    {
        std::cout << "Введите элемент массива - ";
        int user_choice;
        std::cin >> user_choice;
        exampleArr.push_back(user_choice);

        Counter++;
    };
    MergeClass mergeClass;
    auto funcResult = [&exampleArr, &mergeClass]()
        {
            mergeClass.MerrgeSort(exampleArr);
        };
    thread Sorting(funcResult);
    Sorting.join();
    std::cout << "Новый массив - ";
    for (int i : exampleArr) 
    {
        std::cout << "\n";
        std::cout << i;
    }
}

