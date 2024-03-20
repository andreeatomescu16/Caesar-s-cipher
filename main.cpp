#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

ifstream f("/Users/Asus/Library/Application Support/JetBrains/CLion2023.3/scratches/distribution.txt");

float ChiSqDist(float e[], float c[], int n) {

    float s = 0;
    for (int i = 0; i < 26; i++)
        if (c[i] != 0) {
            float exp = e[i] / 100 * n;
            float res;
            res = ((c[i] - exp) * (c[i] - exp)) / exp;
            s += res;
        }

    return s;
}

void NormFrequency(char s[], float fr[]) {
    for (int i = 0; i < strlen(s); i++)
        if (s[i] >= 'A' && s[i] <= 'Z')
            fr[s[i]-'A'] ++;
}

void shift(char v[]) {
    for (int i = 0; i < strlen(v); i++)
        if (v[i] >= 'A' && v[i] < 'Z') {
            v[i] = v[i] + 1;
        }
        else if (v[i] == 'Z') {
            v[i] = 'A';
        }
}

void frequencies(float v[]) {
    for (int i = 0; i < 26; i++) {
        char c;
        float n;
        f>>c>>n;
        v[c-'A'] = n;
    }
}

void upper_text(char t[], char s[]) {
    for (int i = 0; i < strlen(t); i++) {
        if (t[i] >= 'a' &&  t[i] <= 'z')
            s[i] = t[i] - 32;
        else
            s[i] = t[i];
    }
}

int nr_letters(char s[]) {
    int nrc = 0;
    for (int i = 0; i < strlen(s); i++)
        if (s[i] >= 'A' && s[i] <= 'Z')
            nrc++;
    return nrc;
}

void create_text(char t[], char s[], char res[]) {

    for (int j = 0; j < strlen(s); j++)
        if (t[j] >= 'a' && t[j] <='z')
            res[j] = s[j] + 32;
        else
            res[j] = s[j];
}

void result(char t[]) {

    char s[1001];
    upper_text(t, s);
    float v[27];
    frequencies(v);

    float fr[100] = {0};
    NormFrequency(s, fr);

    int nrc = nr_letters(s);

    int i = 0;
    float minim = 999999;
    char res[1001];

    while (i < 26) {
        if (ChiSqDist(v, fr, nrc) < minim) {
            minim = ChiSqDist(v, fr, nrc);
            create_text(t, s, res);
        }
        for (int j = 0; j < 30; j++)
            fr[j] = 0;
        shift(s);
        NormFrequency(s, fr);
        i++;
    }

    res[strlen(t)] = '\0';
    cout<<res;
}

int main() {

    char t[1001];
    cin.getline(t,1001);
    result(t);

    return 0;
}

