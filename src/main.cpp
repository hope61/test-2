#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>
#include <string>

using namespace std;

// read an int from the user, asks again if the input is not a number
int readInt(const char *prompt) {
  int x;
  while (true) {
    cout << prompt;
    if (cin >> x) return x;
    if (cin.eof()) exit(1);
    cout << "invalid input, please enter a whole number" << endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }
}

// generate a random num array
void randArr(int *arr, int n, int min, int max) {
  for (int i = 0; i < n; i++)
    arr[i] = rand() % (max - min + 1) + min;
}

// function that prints the array
void printArr(int *arr, int n) {
  cout << "[";
  for (int i = 0; i < n; i++)
    if (i != 0) cout << ", " << arr[i];
    else cout << arr[i];
  cout << "]" << endl;
}

// function to get the size of an array from the user until the user inputs a positive value
void getSize(int &n) {
  while (true) {
    n = readInt("input the size of the array n: ");
    if (n <= 0) {
      cout << "invalid input, please enter a positive integer" << endl;
    } else break;
  }
}

// function to get integers from the user with checks
void getArr(int *arr, int n, int min, int max) {
  for (int i = 0; i < n; i++) {
    string prompt = "element " + to_string(i + 1) + "/" + to_string(n) + ": ";
    while (true) {
      arr[i] = readInt(prompt.c_str());
      if (arr[i] < min || arr[i] > max) {
        cout << "invalid input, please enter a value between " << min << " and " << max << endl;
      } else break;
    }
  }
}

// function to find the first big drop in the array
void findBigDrop(int *arr, int n, double average) {
  for (int i = 1; i < n; i++) {
    if (arr[i] < average && arr[i - 1] > average) {
      cout << "big drop found at index " << i << ": " << arr[i - 1] << " -> " << arr[i] << endl;
      return;
    }
  }
  cout << "no big drop found" << endl;
}

// function to find the smallest number in an array
void findSmallest(int *arr, int n) {
  int smallest = arr[0];
  for (int i = 1; i < n; i++) {
    if (arr[i] < smallest) {
      smallest = arr[i];
    }
  }
  cout << "smallest number:  " << smallest << endl;
}

// function that fills in an array with numbers that are less than 25
void fillFilteredArr(int *arr, int *filteredArr, int n, int &j) {
  j = 0;
  for (int i = 0; i < n; i++) {
    if (arr[i] < 25) {
      filteredArr[j++] = arr[i];
    }
  }
}

// function to print the pointers of index n-2 of array1 and index 0 of array2
void printPointers(int *arr1, int n1, int *arr2, int n2) {
  if (n1 < 2) {
    cout << "array1 does not have enough elements" << endl;
    return;
  }
  if (n2 == 0) {
    cout << "array2 is empty" << endl;
    return;
  }
  cout << "address of array1[n-2]: " << &arr1[n1 - 2] << endl;
  cout << "address of array2[0]:   " << &arr2[0] << endl;
}

void printHeader(int zad) {
  cout << endl << "================================" << endl;
  cout << "           Zadanie " << zad << endl;
  cout << "================================" << endl;
}

int main() {
  srand(time(0));

  // zad 1
  printHeader(1);

  // generate an array of 7 random values between -5000 and 5000
  int n = 7;
  int *arr = new int[n];
  randArr(arr, n, -5000, 5000);

  // count the values that are divisible by 3 and greater than 15
  int counter = 0;
  for (int i = 0; i < n; i++) {
    if (arr[i] % 3 == 0 && arr[i] > 15) {
      counter++;
    }
  }
  // filter out the values that are divisible by 3 and greater than 15
  int *filteredArr = new int[counter];
  int j = 0;
  for (int i = 0; i < n; i++) {
    if (arr[i] % 3 == 0 && arr[i] > 15) {
      filteredArr[j++] = arr[i];
    }
  }
  cout << "original array: ";
  printArr(arr, n);
  cout << "filtered array: ";
  printArr(filteredArr, counter);

  delete[] arr;
  delete[] filteredArr;

  // zad 2
  printHeader(2);

  getSize(n);
  arr = new int[n];
  getArr(arr, n, -100, 100);

  cout << endl << "original array: ";
  printArr(arr, n);

  // find the average value of the array
  int sum = 0;
  for (int i = 0; i < n; i++) {
    sum += arr[i];
  }
  double average = (double)sum / n;

  cout << "average: " << average << endl;

  // filter out the values that are above the average
  filteredArr = new int[n];
  counter = 0;
  for (int i = 0; i < n; i++) {
    if (abs(arr[i]) > average) {
      filteredArr[counter++] = arr[i];
    }
  }
  cout << "above average (" << counter << "): ";
  printArr(filteredArr, counter);

  findBigDrop(arr, n, average);

  delete[] arr;
  delete[] filteredArr;

  // zad 3
  printHeader(3);

  // get the size of the array, needs at least 2 elements for index n-2
  while (true) {
    getSize(n);
    if (n < 2) {
      cout << "invalid input, please enter a value of at least 2" << endl;
    } else break;
  }
  arr = new int[n];
  filteredArr = new int[n];

  // fill the array with random ints from 15 to 55
  randArr(arr, n, 15, 55);
  cout << endl << "original array:   ";
  printArr(arr, n);

  findSmallest(arr, n);

  // finding the numbers that are less than 25
  fillFilteredArr(arr, filteredArr, n, j);
  if (j == 0) {
    cout << "no numbers less than 25 found" << endl;
  } else {
    cout << "less than 25 (" << j << "): ";
    printArr(filteredArr, j);
  }

  printPointers(arr, n, filteredArr, j);

  delete[] arr;
  delete[] filteredArr;

  return 0;
}
