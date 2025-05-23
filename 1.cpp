#include <iostream>
#include <string>
using namespace std;

// �Ը��������Ľ�����λ����
string caesarDecrypt(const string& ciphertext, int shift) {
    string plaintext = "";
    for (char c : ciphertext) {
        if (isalpha(c)) {
            // ���ַ���λ��ȷ����A-Z��Χ��
            char decrypted = ((c - 'A' - shift + 26) % 26) + 'A';
            plaintext += decrypted;
        }
        else {
            plaintext += c;
        }
    }
    return plaintext;
}

// �����ַ����е���ĸƵ��
void calculateFrequency(const string& text, double* freq) {
    int total = 0;
    for (char c : text) {
        if (isalpha(c)) {
            freq[c - 'A']++;
            total++;
        }
    }
    // ת��Ϊ�ٷֱ�
    for (int i = 0; i < 26; i++) {
        freq[i] = (freq[i] / total) * 100;
    }
}

// ������Ӣ����ĸƵ�ʵĲ���÷�
double getScore(const string& text) {
    // Ӣ����ĸƵ�ʣ��ٷֱȣ�
    const double englishFreq[26] = {
        8.2, 1.5, 2.8, 4.3, 13, 2.2, 2.0, 6.1, 7.0, 0.15,
        0.77, 4.0, 2.4, 6.7, 7.5, 1.9, 0.095, 6.0, 6.3, 9.1,
        2.8, 0.98, 2.4, 0.15, 2.0, 0.074
    };

    double textFreq[26] = { 0 };
    calculateFrequency(text, textFreq);

    // �������÷֣�ԽСԽ�ӽ�Ӣ���ı���
    double score = 0;
    for (int i = 0; i < 26; i++) {
        score += abs(textFreq[i] - englishFreq[i]);
    }
    return score;
}

int main() {
    string ciphertext = "BEEAKFYDJXUQYHYJIQRYHTYJIQFBQDUYJIIKFUHCQD";
    cout << "����: " << ciphertext << endl << endl;

    // �������п��ܵ���λ��0-25��
    double bestScore = 999999;
    int bestShift = 0;
    string bestPlaintext;

    cout << "�������п��ܵ���λ��" << endl;
    for (int shift = 0; shift < 26; shift++) {
        string plaintext = caesarDecrypt(ciphertext, shift);
        double score = getScore(plaintext);

        cout << "��λ " << shift << ": " << plaintext;
        cout << " (�÷�: " << score << ")" << endl;

        if (score < bestScore) {
            bestScore = score;
            bestShift = shift;
            bestPlaintext = plaintext;
        }
    }

    cout << "\n����ܵĽ��ܽ����" << endl;
    cout << "��λ��: " << bestShift << endl;
    cout << "����: " << bestPlaintext << endl;
    cout << "�÷�: " << bestScore << endl;

    return 0;
}