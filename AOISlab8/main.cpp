#include <iostream>
#include <vector>
#include <random>
#include <string>
using namespace std;

class Memory {
private:
    vector<vector<int>> __memory;
    vector<vector<int>> __normal_view;

public:
    Memory() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dis(0, 1);

        for (int i = 0; i < 16; i++) {
            vector<int> row;
            for (int j = 0; j < 16; j++) {
                row.push_back(dis(gen));
            }
            __memory.push_back(row);
        }

        for (int i = 0; i < 16; i++) {
            __normal_view.push_back(read(i));
        }
    }

    void f4_function(int address_1, int address_2, int address_3) {
        vector<int> word_1 = read(address_1);
        vector<int> word_2 = read(address_2);
        vector<int> word_3;
        for (int i = 0; i < 16; i++) {
            word_3.push_back((word_1[i] == 0 && word_2[i] == 1) ? 1 : 0);
        }
        add(address_3, word_3);
    }

    void f6_function(int address_1, int address_2, int address_3) {
        vector<int> word_1 = read(address_1);
        vector<int> word_2 = read(address_2);
        vector<int> word_3;
        for (int i = 0; i < 16; i++) {
            word_3.push_back((word_1[i] != word_2[i]) ? 1 : 0);
        }
        add(address_3, word_3);
    }

    void f9_function(int address_1, int address_2, int address_3) {
        vector<int> word_1 = read(address_1);
        vector<int> word_2 = read(address_2);
        vector<int> word_3;
        for (int i = 0; i < 16; i++) {
            word_3.push_back((word_1[i] == word_2[i]) ? 1 : 0);
        }
        add(address_3, word_3);
    }

    void f11_function(int address_1, int address_2, int address_3) {
        vector<int> word_1 = read(address_1);
        vector<int> word_2 = read(address_2);
        vector<int> word_3;
        for (int i = 0; i < 16; i++) {
            word_3.push_back((word_1[i] == 0 && word_2[i] == 1) ? 0 : 1);
        }
        add(address_3, word_3);
    }

    void ordered_selection(bool descending) {
        for (int i = 0; i < 16; i++) {
            for (int j = 0; j < 15 - i; j++) {
                if (greater(read(j), read(j + 1))) {
                    vector<int> word_copy = read(j);
                    add(j, read(j + 1));
                    add(j + 1, word_copy);
                }
            }
        }
        if (descending) {
            normalView();
            reverse(__normal_view.begin(), __normal_view.end());
            diagonalView();
        }
    }

    void sum(const vector<int>& V) {
        cout << "\nFound words for V = ";
        for (int i = 0; i < 3; i++) {
            cout << V[i];
        }
        cout << ":" << endl;
        for (int i = 0; i < 16; i++) {
            if (vectorEqual(__normal_view[i], V, 3)) {
                cout << vectorToString(__normal_view[i]) << endl;
                vector<int> word = __normal_view[i];
                vector<int> sum_result = binary_sum(vector<int>(word.begin() + 3, word.end()));
                vector<int> new_word(word.begin(), word.begin() + 11);
                new_word.insert(new_word.end(), sum_result.begin(), sum_result.end());
                add(i, new_word);
                cout << vectorToString(new_word) << endl;
                cout << vectorToString(__normal_view[i]) << endl;
            }
        }
    }

    vector<int> binary_sum(const vector<int>& word) {
        vector<int> first_part(word.begin(), word.begin() + 4);
        vector<int> second_part(word.begin() + 4, word.begin() + 8);
        reverse(first_part.begin(), first_part.end());
        reverse(second_part.begin(), second_part.end());
        vector<int> result;
        int carry = 0;
        for (int i = 0; i < 4; i++) {
            int first_bit = first_part[i];
            int second_bit = second_part[i];
            if (first_bit + second_bit + carry == 3) {
                result.push_back(1);
            }
            else if (first_bit + second_bit + carry == 2) {
                result.push_back(0);
                carry = 1;
            }
            else if (first_bit + second_bit + carry == 1) {
                result.push_back(1);
                carry = 0;
            }
            else {
                result.push_back(0);
            }
        }
        result.push_back(carry);
        reverse(result.begin(), result.end());
        return result;
    }

    void diagonalView() {
        for (int i = 0; i < 16; i++) {
            add(i, __normal_view[i]);
        }
    }

    void normalView() {
        __normal_view.clear();
        for (int i = 0; i < 16; i++) {
            __normal_view.push_back(read(i));
        }
    }

    bool greater(const vector<int>& word_1, const vector<int>& word_2) {
        bool g = false;
        bool l = false;
        for (int i = 0; i < 16; i++) {
            g = g || (!word_2[i] && word_1[i] && !l);
            l = l || (word_2[i] && !word_1[i] && !g);
        }
        return (g && !l);
    }

    vector<int> readLine(int address) {
        return __memory[address];
    }

    vector<int> read(int address) {
        vector<int> word;
        for (int j = address; j < 16; j++) {
            word.push_back(__memory[j][address]);
        }
        for (int j = 0; j < address; j++) {
            word.push_back(__memory[j][address]);
        }
        return word;
    }

    void add(int address, const vector<int>& _word) {
        vector<int> word = _word;
        reverse(word.begin(), word.end());
        for (int j = address; j < 16; j++) {
            __memory[j][address] = word.back();
            word.pop_back();
        }
        for (int j = 0; j < address - 1; j++) {
            __memory[j][address] = word.back();
            word.pop_back();
        }
    }

    void print() {
        cout << "\n";
        cout << "Diagonal view:\n" << endl;
        for (const vector<int>& row : __memory) {
            for (int value : row) {
                cout << value << " ";
            }
            cout << endl;
        }
        normalView();
        cout << "\n";
        cout << "Normal view:\n" << endl;
        for (const vector<int>& row : __normal_view) {
            for (int value : row) {
                cout << value << " ";
            }
            cout << endl;
        }
    }

private:
    bool vectorEqual(const vector<int>& v1, const vector<int>& v2, int n) {
        for (int i = 0; i < n; i++) {
            if (v1[i] != v2[i]) {
                return false;
            }
        }
        return true;
    }

    string vectorToString(const vector<int>& vec) {
        string result = "";
        for (int value : vec) {
            result += to_string(value);
        }
        return result;
    }
};

int main() {
    Memory memory;
    memory.print();
    memory.add(15, { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 });

    memory.print();
    std::cout << "Reading line 12: ";
    std::vector<int> line12 = memory.readLine(14);
    for (int value : line12) {
        std::cout << value << " ";
    }
    std::cout << "\n";
    std::cout << "Ordered Selection: " << std::endl;
    memory.ordered_selection(true);
    memory.print();
    std::cout << std::endl;
    std::cout << "function_4 for words 0x00 and 0x01 in 0x02:" << std::endl;
    std::cout << "0x00: ";
    for (int value : memory.read(0)) {
        std::cout << value << " ";
    }
    cout << "\n";
    std::cout << "0x01: ";
    for (int value : memory.read(1)) {
        std::cout << value << " ";
    }
    cout << "\n";
    cout << "\n";
    memory.f4_function(0, 1, 2);
    std::cout << "0x02: ";
    for (int value : memory.read(2)) {
        std::cout << value << " ";
    }
    memory.print();
    std::cout << std::endl;
    std::cout << "function_6 for words 0x03 and 0x04 in 0x05:" << std::endl;
    std::cout << "0x03: ";
    for (int value : memory.read(3)) {
        std::cout << value << " ";
    }
    cout << "\n";
    std::cout << "0x04: ";
    for (int value : memory.read(4)) {
        std::cout << value << " ";
    }
    cout << "\n";
    cout << "\n";
    memory.f6_function(3, 4, 5);
    std::cout << "0x05: ";
    for (int value : memory.read(5)) {
        std::cout << value << " ";
    }
    memory.print();
    std::cout << std::endl;
    std::cout << "function_9 for words 0x06 and 0x07 in 0x08:" << std::endl;
    std::cout << "0x06: ";
    for (int value : memory.read(6)) {
        std::cout << value << " ";
    }
    cout << "\n";
    std::cout << "0x07: ";
    for (int value : memory.read(7)) {
        std::cout << value << " ";
    }
    cout << "\n";
    cout << "\n";
    memory.f9_function(6, 7, 8);
    std::cout << "0x08: ";
    for (int value : memory.read(8)) {
        std::cout << value << " ";
    }
    memory.print();
    std::cout << std::endl;
    std::cout << "function_11 for words 0x09 and 0x010 in 0x11:" << std::endl;
    std::cout << "0x09: ";
    for (int value : memory.read(6)) {
        std::cout << value << " ";
    }
    cout << "\n";
    std::cout << "0x010: ";
    for (int value : memory.read(7)) {
        std::cout << value << " ";
    }
    cout << "\n";
    cout << "\n";
    memory.f9_function(6, 7, 8);
    std::cout << "0x011: ";
    for (int value : memory.read(8)) {
        std::cout << value << " ";
    }
    memory.print();
    std::vector<int> V = { 0, 1, 1 };
    memory.sum(V);
    std::cout << "Memory after sum: ";
    for (int value : V) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
    memory.print();

}