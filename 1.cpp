#include <iostream>
#include <string>
using namespace std;

// 对给定的密文进行移位解密
string caesarDecrypt(const string& ciphertext, int shift) {
    string plaintext = "";
    for (char c : ciphertext) {
        if (isalpha(c)) {
            // 将字符移位，确保在A-Z范围内
            char decrypted = ((c - 'A' - shift + 26) % 26) + 'A';
            plaintext += decrypted;
        }
        else {
            plaintext += c;
        }
    }
    return plaintext;
}

// 计算字符串中的字母频率
void calculateFrequency(const string& text, double* freq) {
    int total = 0;
    for (char c : text) {
        if (isalpha(c)) {
            freq[c - 'A']++;
            total++;
        }
    }
    // 转换为百分比
    for (int i = 0; i < 26; i++) {
        freq[i] = (freq[i] / total) * 100;
    }
}

// 计算与英语字母频率的差异得分
double getScore(const string& text) {
    // 英语字母频率（百分比）
    const double englishFreq[26] = {
        8.2, 1.5, 2.8, 4.3, 13, 2.2, 2.0, 6.1, 7.0, 0.15,
        0.77, 4.0, 2.4, 6.7, 7.5, 1.9, 0.095, 6.0, 6.3, 9.1,
        2.8, 0.98, 2.4, 0.15, 2.0, 0.074
    };

    double textFreq[26] = { 0 };
    calculateFrequency(text, textFreq);

    // 计算差异得分（越小越接近英语文本）
    double score = 0;
    for (int i = 0; i < 26; i++) {
        score += abs(textFreq[i] - englishFreq[i]);
    }
    return score;
}

int main() {
    string ciphertext = "BEEAKFYDJXUQYHYJIQRYHTYJIQFBQDUYJIIKFUHCQD";
    cout << "密文: " << ciphertext << endl << endl;

    // 尝试所有可能的移位（0-25）
    double bestScore = 999999;
    int bestShift = 0;
    string bestPlaintext;

    cout << "尝试所有可能的移位：" << endl;
    for (int shift = 0; shift < 26; shift++) {
        string plaintext = caesarDecrypt(ciphertext, shift);
        double score = getScore(plaintext);

        cout << "移位 " << shift << ": " << plaintext;
        cout << " (得分: " << score << ")" << endl;

        if (score < bestScore) {
            bestScore = score;
            bestShift = shift;
            bestPlaintext = plaintext;
        }
    }

    cout << "\n最可能的解密结果：" << endl;
    cout << "移位量: " << bestShift << endl;
    cout << "明文: " << bestPlaintext << endl;
    cout << "得分: " << bestScore << endl;

    return 0;
}