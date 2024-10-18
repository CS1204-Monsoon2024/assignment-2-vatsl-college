#include <iostream>
#include <string>
using namespace std;

bool primeCheck(int num){//sieve of erasthoneses
    if (num<=1) return false;
    if (num==2) return true; 
    if (num%2==0) return false; 

    for (int i=3; i*i<=num; i+=2) {
        if (num%i == 0) return false;
    }
    return true;
}
int findNextPrime(int num){
    if (num<=2) return 2; 
    if (num%2==0) num++;
    while (!primeCheck(num)){
        num += 2;
    }
    return num;
}
class HashTable{
private:
    int n;
    int hash(int key){
        return key % this->m;
    }
    int* t;
    int* occupied;
    int m;

    void resizeTable() {
        int oldSize = m;
        m = findNextPrime(2*m); 
        int* oldT = t;       
        int* oldOccupied = occupied;
        t = new int[m]();
        occupied = new int[m]();
        n = 0; 

        for (int i=0; i<oldSize; i++){
            if (oldOccupied[i]==1){  
                insert(oldT[i]);
            }
        }
        delete[] oldT;
        delete[] oldOccupied;
    }

public: 
    HashTable(int initialSize){
        m = initialSize;
        n = 0;
        t=new int[initialSize]();
        occupied=new int[initialSize]();
        for (int i=0; i< initialSize;i++){
            occupied[i] = 0;
        }
    }

    void insert(int key){
        if (n/(float)m >= 0.8){
                resizeTable();
        } 
        if (n==m){//check if the table is full
            cout<<"Table is already full"<<"\n";
            return;
        }
        if (search(key)>-1){
            cout<<"Duplicate key insertion is not allowed"<<"\n";
        }
        
        int index = hash(key);  // Compute initial index
        int i = 0;
        while (occupied[index] == 1 &&  i<m) {  // Quadratic probing
            i++;
            index = (hash(key) + i * i) % m;  // Compute new index: h(k) + i^2
        }
        if (i>=m){
            cout<<"Max probing limit reached!"<<"\n";//if we attempted m slots, probing limit reached.
        } else {
            t[index] = key;    // Insert the key at the found index
            occupied[index] = 1; // Mark the slot as occupied
            n++;   
        }
    }
    int search(int key){
        int index = hash(key);
        int i = 0;
        while (occupied[index]!=0 && i<m){//loop continues till we find a empty slot in the probe sequence of we have checked all slots
            if (occupied[index]==1 && t[index]==key) {
                return index;
            }
            i++;
            index = (hash(key) + i*i) % m;
        }
        return -1;
    }
    void remove(int key){
        int index = search(key);
        if (index==-1){
            cout<<"Element not found"<<"\n";
        } else{
            occupied[index]=-1;
        }
    }
    void printTable(){
        string s;
        for (int i=0;i<m;i++){
            if (occupied[i]!=1){
                s += "- ";
            } else{
                string num = to_string(t[i]);
                s+= num + " ";
            }
        }
        cout<<s<<endl;
    }
};
