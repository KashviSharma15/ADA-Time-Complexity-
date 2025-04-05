#include <iostream>
#include <cmath>
using namespace std;

int sum(int n){
    if (n< 10){
        return n;
    }else{
    int count = log10(n) + 1;
    int mid = count/2;
    int divisor = pow(10,mid);
    int left = n/divisor;
    int right = n%divisor;
    return (sum( left ) + sum (right ));
}
}

int countNo(int n){
    if (n < 10){
        if (n % 2 == 0){   //even
            return 1;
        }else{
            return 0;
        }
    }else{
        int count = log10(n) + 1;
        int mid = count/2;
        int divisor = pow (10,mid);
        int left = n/divisor;
        int right = n%divisor;
        return (countNo(left)+countNo(right));
    }
}
int maximum(int n){
    if(n< 10){
        return n;
    }else{
        int count = log10(n) + 1;
        int mid = count/2;
        int divisor = pow(10,mid);
        int left = n/divisor;
        int right = n%divisor;
        return max (maximum(left),maximum(right));
    }
}

int minimum(int n){
    if(n< 10){
        return n;
    }else{
        int count = log10(n) + 1;
        int mid = count/2;
        int divisor = pow(10,mid);
        int left = n/divisor;
        int right = n%divisor;
        return min (minimum(left),minimum(right));
    }
}

int sumOfOdd(int n){
    if ( n < 10){
        if (n % 2 != 0){    //odd
        return n;
    }else{
        return 0;
    }
    }else {
        int count = log10(n) + 1;
        int mid = count/2;
        int divisor = pow(10,mid);
        int left = n/divisor;
        int right = n%divisor;
        return (sumOfOdd(left) + sumOfOdd(right));
    }
}

int LessThanFive(int n){
    if ( n < 10){
        if (n < 5 ){    //less
        return 1 ;
    }else{
        return 0;
    }
    }else {
        int count = log10(n) + 1;
        int mid = count/2;
        int divisor = pow(10,mid);
        int left = n/divisor;
        int right = n%divisor;
        return (LessThanFive(left) + LessThanFive(right));
    }
}

int LessThanFiveSum(int n){
    if ( n < 10){
        if (n < 5 ){    //less
        return n ;
    }else{
        return 0;
    }
    }else {
        int count = log10(n) + 1;
        int mid = count/2;
        int divisor = pow(10,mid);
        int left = n/divisor;
        int right = n%divisor;
        return (LessThanFiveSum(left) + LessThanFiveSum(right));
    }
}

int Reverse( int n){
    if (n < 10 ){
        return n;
    }
    int count = log10(n)+1;
    int mid = count/2;
    int divisor = pow(10,mid);
    int left = n/divisor;
    int right = n%divisor;
    int noLeft = log10(left)+1;
    return (Reverse(right)* pow (10,noLeft) + Reverse(left));
}

bool Palindrome (int n){
    if (n == Reverse(n)) return true;
    else return false;
}

int mul(int n){
    if (n < 10 ){
        return n;
    }
    int count = log10(n)+1;
    int mid = count/2;
    int divisor = pow(10,mid);
    int left = n/divisor;
    int right = n%divisor;
    return (mul(left) * mul(right));
}

int mulOfOdd(int n){
    if ( n < 10){
        if (n % 2 != 0){    //odd
        return n;
    }else{
        return 1;
    }
    }else {
        int count = log10(n) + 1;
        int mid = count/2;
        int divisor = pow(10,mid);
        int left = n/divisor;
        int right = n%divisor;
        return (mulOfOdd(left) * mulOfOdd(right));
    }
}
int main(){
    cout << "Enter the no." << endl;
    int n;
    cin >> n ;
    cout << sum(n) << endl;
    cout << countNo(n) << endl;
    cout << maximum(n) << endl;
    cout << minimum(n) << endl;
    cout << sumOfOdd(n) << endl;
    cout << LessThanFive(n) << endl;
    cout << LessThanFiveSum(n) << endl;
    cout << "reverse is " << Reverse(n) << endl;
    cout << "Palindrome " << Palindrome(n) << endl;
    cout << mul(n) << endl;
    cout << mulOfOdd(n) << endl;

    return 0;

}