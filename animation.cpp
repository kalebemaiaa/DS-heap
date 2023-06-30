#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

// Bubble

void bubbleSortAnimation(int arr[], int size)
{
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            // Limpa a tela
            cout << "\033[2J\033[1;1H";
            
            // Atualiza a exibição do estado atual do array durante a ordenação
            for (int k = 0; k < size; k++) {
                if (k == j || k == j + 1) {
                    cout << "\033[1;31m" << arr[k] << " ";
                } else {
                    cout << "\033[0m" << arr[k] << " ";
                }
            }
            cout << endl;

            // Atraso para animação
            this_thread::sleep_for(chrono::milliseconds(1500));

            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}


// Insert 

void insertionSortAnimation(int arr[], int size)
{
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;

        // Mostra o estado atual do array durante a ordenação
        for (int k = 0; k < size; k++) {
            if (k == i) {
                cout << "\033[1;31m" << arr[k] << " ";
            } else {
                cout << "\033[0m" << arr[k] << " ";
            }
        }
        cout << endl;

        // Atraso para animação
        this_thread::sleep_for(chrono::milliseconds(1500));

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;

            // Mostra o estado atual do array durante a ordenação
            for (int k = 0; k < size; k++) {
                if (k == j + 1 || k == i) {
                    cout << "\033[1;31m" << arr[k] << " ";
                } else {
                    cout << "\033[0m" << arr[k] << " ";
                }
            }
            cout << endl;

            // Atraso para animação
            this_thread::sleep_for(chrono::milliseconds(1500));
        }

        arr[j + 1] = key;
    }
}

// Select

void selectionSortAnimation(int arr[], int size)
{
    for (int i = 0; i < size - 1; i++) {
        int minIndex = i;

        // Mostra o estado atual do array durante a ordenação
        for (int k = 0; k < size; k++) {
            if (k == i || k == minIndex) {
                cout << "\033[1;31m" << arr[k] << " ";
            } else {
                cout << "\033[0m" << arr[k] << " ";
            }
        }
        cout << endl;

        // Atraso para animação
        this_thread::sleep_for(chrono::milliseconds(1500));

        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        swap(arr[i], arr[minIndex]);
    }
}

// Shell 

void shellSortAnimation(int arr[], int size)
{
    for (int gap = size / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < size; i++) {
            int temp = arr[i];
            int j;

            // Mostra o estado atual do array durante a ordenação
            for (int k = 0; k < size; k++) {
                if (k == i || k == i - gap) {
                    cout << "\033[1;31m" << arr[k] << " ";
                } else {
                    cout << "\033[0m" << arr[k] << " ";
                }
            }
            cout << endl;

            // Atraso para animação
            this_thread::sleep_for(chrono::milliseconds(1500));

            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }

            arr[j] = temp;
        }
    }
}

int main()
{

    int arr[] = {5, 9, 3, 1, 7};
    int size = sizeof(arr) / sizeof(arr[0]);

    // Bubble 
    bubbleSortAnimation(arr, size);

    // Mostra o array final após a ordenação
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    cout << "======================="<< endl;
    cout << endl;

    // Insert 

    insertionSortAnimation(arr, size);

    // Mostra o array final após a ordenação
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    cout << "======================="<< endl;
    cout << endl;

    // Select 

    selectionSortAnimation(arr, size);

    // Mostra o array final após a ordenação
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    cout << "======================="<< endl;
    cout << endl;

    // Shell 

    shellSortAnimation(arr, size);

    // Mostra o array final após a ordenação
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
