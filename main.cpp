#include <iostream>
#include <fstream>

using namespace std;

int n = 1;
fstream file;

void print(int* a, bool f) {
	if(f == false){
		file.open("permutacje.txt", ios::out|ios::app);
	}
	else{
		file.open("permutacje.txt", ios::out);
	}
	cout << '\t';
	for (int i = 0; i < n; i++) {
		cout << a[i] << " ";
		file << a[i] << " ";
	}
	cout << endl;
	file << endl;
	file.close();
}

void generate_next(int* next){
	int index = n - 2;
	for(int i=n-2; i>=index; i--){
		if(i>=0){
			if(next[i] < i+1){
				next[i]++;
				break;
			}
			else{
				next[i] = 0;
				index--;
			}
		}
		else{
			cout << "Generacja NEXT poza zakresem." << endl;
			break;
		}
	}
}

void generate_perm(){
	bool first = true;
	int* arr = new int [n];
	for(int i=0; i<n; i++){
		arr[i] = i+1;
	}
	print(arr, first);
	first = false;
	
	int* next = new int [n-1];
	for(int i = 0; i<n-1; i++){
		next[i] = 0;
	}
	
	int nr = 1;
	int number = 1;
	for(int i=1;i<=n;i++){
		number*=i;
	}
	
	int i = n-1;
	int temp = 0;
	while(nr<number){
		generate_next(next);
		for(int i=0; i<n; i++){
			arr[i] = i+1;
		}
		for(int i=0; i<n-1; i++){
			if(next[i] > 0){
				temp = arr[i+1];
				arr[i+1] = arr[next[i]-1];
				arr[next[i]-1] = temp;
			}
		}
		print(arr, first);
		nr++;
	}

	
	delete [] next;
	delete [] arr;
}

int main() {

	cout << "Program do generowania podzialow zbioru n-elementowego." << endl;
	cout << "Wprowadz liczbe elementow zbioru: ";
	cin >> n;
	while(!n){
		cout << "Wprowadzono niepoprawna wartosc. Sprobuj jeszcze raz." << endl;
		cout << "Wprowadz liczbe elementow zbioru: ";
		cin >> n;
	}
	cout << "Generuje permutacje...\n" << endl;
	generate_perm();
	cout << "\nWyniki generacji zostaly zapisane w pliku permutacje.txt" << endl;
	return 0;
}
