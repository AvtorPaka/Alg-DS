#include <iostream>
#include <vector>
#include <string>
#include <cstdint>

size_t CustomHash(std::string key, int32_t p) {
    size_t h = 0;
    int64_t p_pow = 1;
    for (size_t i = 0; i < key.length(); ++i) {
        h += (key[i] - 'a' + 1) * p_pow;
        p_pow *= p;
    }

    return h;
}

// Функция проверки принадлежность символа (его кода ascii)
// заданым условием границам - строчные/прописные латинские буквы и цифры
// 48-57 - цифры
// 65-90, 97-122 - прописные и строчные латинские символы
bool IsCharCodeAllowed(uint32_t charCode) {
    return (48 <= charCode && charCode <= 57) || (65 <= charCode && charCode <= 90) ||
           (97 <= charCode && charCode <= 122);
}

// Алгоритм поиска нейтральных элементов(строк), состоящих из двух символов
// allowedCodes - массив с кодами допустимых символов: [48...57,65...90,97...122] - 62 элемента
std::vector<std::string> FindNeutralHashedForP(const std::vector<uint32_t>& allowedCodes, int32_t p) {
    std::vector<std::string> neutralElements;

    for (int32_t i = 0; i < allowedCodes.size(); ++i) {
        uint32_t secondCharCode = allowedCodes[i];
        uint32_t firstCharCode = 96 - (secondCharCode - 96) * p;

        if (IsCharCodeAllowed(firstCharCode)) {
            std::string curNeutralElement(1, firstCharCode);
            curNeutralElement += (char)secondCharCode;
            neutralElements.push_back(curNeutralElement);
        }
    }

    return neutralElements;
}

// Функция для нахождения всех нейтральных элементов
// для всех значений параметра p <= maxP
void FindAllNeutralElementsForPRange(int32_t maxP) {

    std::vector<uint32_t> allowedCodes;
    for (int32_t i = 48; i < 123; ++i) {
        if (IsCharCodeAllowed(i)) {
            allowedCodes.push_back(i);
        }
    }

    std::string delimiter(30, '-');
    std::vector<std::string> neutralEl;
    for (int32_t p = 0; p <= maxP; ++p) {
        std::cout << delimiter << '\n' << "Neutral hash elements for p = " << p << '\n';

        neutralEl = FindNeutralHashedForP(allowedCodes, p);
        if (neutralEl.empty()) {
            std::cout << "No such elements" << '\n';
        }
        for (int32_t i = 0; i < neutralEl.size(); ++i) {
            std::cout << neutralEl[i] << " => Calculated hash: " << CustomHash(neutralEl[i], p) << '\n';
        }

    }
}