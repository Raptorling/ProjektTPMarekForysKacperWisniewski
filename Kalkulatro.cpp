#include <iostream>
#include <stack>
#include <vector>
#include<cmath>
using namespace std;

int main()
{
    
    stack<char> ciag = { };
    stack<char> backup = {};
    vector<char> znaki = { '+', '-', '*', '/' };
    stack<int> liczby = {};
    stack<int> plecak = {};
    stack<char> plecak2 = {};
    //
    const int MAKS = 100;
    char wyrazenie[MAKS];
    char stack[MAKS];
    char wynik[MAKS];
    int top = -1, w = 0;
    int score = 0;
    int kroki = 0;

    cout << "Podaj wyrazenie (bez spacji): ";
    cin.getline(wyrazenie, MAKS);

    // Przetwarzanie wyrażenia znak po znaku
    for (int i = 0; wyrazenie[i]; i++) {
        char znak = wyrazenie[i];

        if (znak >= '0' && znak <= '9') {
            wynik[w++] = znak;
            if (!(wyrazenie[i + 1] >= '0' && wyrazenie[i + 1] <= '9')) {
                wynik[w++] = ' ';
            }
        }
        else if (znak == '(') {
            stack[++top] = znak;
        }
        else if (znak == ')') {
            while (top >= 0 && stack[top] != '(') {
                wynik[w++] = stack[top--];
                wynik[w++] = ' ';
            }
            if (top >= 0) top--;
        }
        else {
            while (top >= 0 && ((stack[top] == '*' || stack[top] == '/') ||
                ((stack[top] == '+' || stack[top] == '-') && (znak == '+' || znak == '-')))) {
                wynik[w++] = stack[top--];
                wynik[w++] = ' ';
            }
            stack[++top] = znak;
        }
    }

    // Wrzucenie reszty operatorów ze stosu do wyniku
    while (top >= 0) {
        wynik[w++] = stack[top--];
        wynik[w++] = ' ';
    }

    wynik[w] = '\0'; // zakończenie napisu

    // Wyświetlenie wyniku
    cout << "Wyrazenie w odwrotnej notacji polskiej: " << wynik << endl;
     
 
    //
    
    //wrzucenie wyrażenia na stos 
    for (int i = w; i >= 0; i--) {
        if(wynik[i] == ' ')
            ciag.push('#');
        else
            ciag.push(wynik[i]);
        
        
    }


    while (!ciag.empty()) {
        while (!ciag.empty() && ciag.top() == '#');
            ciag.pop();

        if (find(znaki.begin(), znaki.end(), ciag.top()) != znaki.end()) {
            int wynik = 0;
            char znak = ciag.top();
            ciag.pop();
            int a = liczby.top();
            liczby.pop();
            int b = liczby.top();
            liczby.pop();
            if (znak == '-')
                wynik = b - a;
            if (znak == '+')
                wynik = b + a;
            if (znak == '*')
                wynik = b * a;
            if (znak == '/')
                wynik = b / a;
            score = wynik;
            liczby.push(wynik);
        }



        int stopien = 0;
        int liczba = 0;
        bool czy_licz = 0;
        while ( !ciag.empty() && ciag.top() != '#') {
            backup.push(ciag.top());
            ciag.pop();
            stopien += 1;
            czy_licz = 1;
        }
        for (int i = 0; i < stopien && czy_licz; i++) {
            liczba += (int(backup.top()) - 48) * int(pow(10,i));
            backup.pop();
        }
        if (czy_licz) {
            liczby.push(liczba);

      
        }
        
        

        
    }
    cout << "wynik: " << score << endl;
    
}
