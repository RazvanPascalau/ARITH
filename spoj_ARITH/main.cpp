//
//  main.cpp
//  simpleTest
//
//  Created by Razvan Pascalau on 13/07/14.
//  Copyright (c) 2014 Razvan Pascalau. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <deque>
std::ostream& operator<<(std::ostream& os,
                         const std::vector<int8_t>& vectorToPrint)
{
    for (int i = 0; i < vectorToPrint.size(); ++i) {
        os << vectorToPrint[i];
    }
    return os;
}

std::ostream& operator<<(std::ostream& os,
                         const std::deque<int8_t>& dequeToPrint)
{
    for (int i = 0; i < dequeToPrint.size(); ++i) {
        os << static_cast<int>(dequeToPrint[dequeToPrint.size() - i - 1]);
    }
    return os;
}

inline bool isOperation(char ch)
{
    bool result = false;
    switch (ch) {
    case '+':
        result = true;
        break;
    case '-':
        result = true;
        break;
    case '*':
        result = true;
        break;
    default:
        result = false;
        break;
    }

    return result;
}

void computeSum(std::deque<int8_t>& firstNumber,
                std::deque<int8_t>& secondNumber, std::deque<int8_t>& result)
{
    using namespace std;

    int32_t carry = 0;
    int8_t sizeDifference;

    deque<int8_t>& aliasBiggerDeque = firstNumber.size() > secondNumber.size() ? firstNumber : secondNumber;
    deque<int8_t>& aliasSmallerDeque = secondNumber.size() < firstNumber.size() ? secondNumber : firstNumber;

    sizeDifference = aliasBiggerDeque.size() - aliasSmallerDeque.size();

    for (int i = 0; i < aliasSmallerDeque.size(); ++i) {
        int8_t currentValue = static_cast<int8_t>(carry + aliasBiggerDeque[i] + aliasSmallerDeque[i]);
        carry = currentValue / 10;
        result.push_back(currentValue % 10);
    }

    for (int i = static_cast<int>(aliasSmallerDeque.size());
         i < aliasBiggerDeque.size(); i++) {
        int8_t currentValue = static_cast<int8_t>(carry + aliasBiggerDeque[i]);
        carry = currentValue / 10;
        result.push_back(currentValue % 10);
    }
    if (0 != carry) {
        result.push_back(carry);
    }
}

void computeSumInPlace(std::deque<int8_t>& firstNumber,
                       std::deque<int8_t>& secondNumber)
{
    using namespace std;

    int32_t carry = 0;
    int8_t sizeDifference;

    deque<int8_t>& aliasBiggerDeque = firstNumber.size() > secondNumber.size() ? firstNumber : secondNumber;

    deque<int8_t>& aliasSmallerDeque = secondNumber.size() < firstNumber.size() ? secondNumber : firstNumber;

    sizeDifference = aliasBiggerDeque.size() - aliasSmallerDeque.size();

    for (int i = 0; i < aliasSmallerDeque.size(); ++i) {
        int8_t currentValue = static_cast<int8_t>(carry + aliasBiggerDeque[i] + aliasSmallerDeque[i]);
        carry = currentValue / 10;
        secondNumber[i] = currentValue % 10;
    }

    if (aliasBiggerDeque.size() > secondNumber.size()) {
        for (int i = static_cast<int>(aliasSmallerDeque.size());
             i < aliasBiggerDeque.size(); i++) {

            int8_t currentValue = static_cast<int8_t>(carry + aliasBiggerDeque[i]);
            carry = currentValue / 10;
            secondNumber.push_back(currentValue % 10);
        }
    } else {
        for (int i = static_cast<int>(aliasSmallerDeque.size());
             i < aliasBiggerDeque.size(); i++) {

            int8_t currentValue = static_cast<int8_t>(carry + aliasBiggerDeque[i]);
            carry = currentValue / 10;
            secondNumber[i] = currentValue % 10;
        }
    }

    if (0 != carry) {
        secondNumber.push_back(carry);
    }

    for (int32_t i = static_cast<int32_t>(secondNumber.size() - 1); i > 0; --i) {
        if (secondNumber[i] == 0) {
            secondNumber.pop_back();
        } else {
            break;
        }
    }
}

void printSum(std::deque<int8_t>& firstNumber,
              std::deque<int8_t>& secondNumber)
{
    using namespace std;

    deque<int8_t> result;

    computeSum(firstNumber, secondNumber, result);

    int32_t nrOfDashes = static_cast<int32_t>(max(result.size(), secondNumber.size() + 1));

    int32_t nrOfSpacesForFirst = nrOfDashes - static_cast<int32_t>(firstNumber.size());
    int32_t nrOfSpacesForSecond = nrOfDashes - static_cast<int32_t>(secondNumber.size() + 1);
    int32_t nrOfSpacesForResult = nrOfDashes - static_cast<int32_t>(result.size());

    std::cout << string(nrOfSpacesForFirst, ' ') << firstNumber << endl;
    std::cout << string(nrOfSpacesForSecond, ' ') << "+" << secondNumber << endl;
    std::cout << string(nrOfDashes, '-') << endl;
    std::cout << string(nrOfSpacesForResult, ' ') << result << endl;
}

inline bool printDifference(std::deque<int8_t>& firstNumber,
                            std::deque<int8_t>& secondNumber)
{
    using namespace std;

    int32_t borrow = 0;
    int8_t sizeDifference;
    deque<int8_t> result;

    deque<int8_t>& aliasBiggerDeque = firstNumber.size() > secondNumber.size() ? firstNumber : secondNumber;
    deque<int8_t>& aliasSmallerDeque = secondNumber.size() < firstNumber.size() ? secondNumber : firstNumber;
    sizeDifference = aliasBiggerDeque.size() - aliasSmallerDeque.size();

    for (int i = 0; i < aliasSmallerDeque.size(); ++i) {
        int8_t currentValue = static_cast<int8_t>(firstNumber[i] - secondNumber[i] + borrow);
        if (currentValue < 0) {
            currentValue += 10;
            borrow = -1;
        } else {
            borrow = 0;
        }
        result.push_back(currentValue);
    }

    for (int i = static_cast<int>(aliasSmallerDeque.size());
         i < aliasBiggerDeque.size(); i++) {
        int8_t currentValue = static_cast<int8_t>(borrow + aliasBiggerDeque[i]);
        if (currentValue < 0) {
            currentValue += 10;
            borrow = -1;
        } else {
            borrow = 0;
        }
        result.push_back(currentValue);
    }

    for (int i = static_cast<int>(result.size() - 1); i > 0 && result[i] == 0;
         i--) {
        result.pop_back();
    }

    int32_t nrOfDashes = static_cast<int32_t>(max(firstNumber.size(), secondNumber.size() + 1));
    int32_t nrOfSpacesForFirst = nrOfDashes - static_cast<int32_t>(firstNumber.size());
    int32_t nrOfSpacesForSecond = nrOfDashes - static_cast<int32_t>(secondNumber.size() + 1);
    int32_t nrOfSpacesForResult = nrOfDashes - static_cast<int32_t>(result.size());
    int32_t nrOfSpacesForDash = min(nrOfSpacesForSecond, nrOfSpacesForResult);

    std::cout << string(nrOfSpacesForFirst, ' ') << firstNumber << endl;
    std::cout << string(nrOfSpacesForSecond, ' ') << "-" << secondNumber << endl;
    std::cout << string(nrOfSpacesForDash, ' ') << string(nrOfDashes - nrOfSpacesForDash, '-') << endl;
    std::cout << string(nrOfSpacesForResult, ' ') << result << endl;

    return true;
}

void multiplyRow(std::deque<int8_t>& bigNumber, int8_t multiplicationFactor,
                 std::deque<int8_t>& result)
{
    using namespace std;

    if (0 == multiplicationFactor) {
        result.push_back(0);
        return;
    }

    int8_t carry = 0;

    for (int i = 0; i < bigNumber.size(); ++i) {
        result.push_back(multiplicationFactor * bigNumber[i] + carry);
        carry = result[i] / 10;
        result[i] %= 10;
    }

    if (0 != carry) {
        result.push_back(carry);
    }
}

inline void multiplyNumbers(std::deque<int8_t>& firstNumber,
                            std::deque<int8_t>& secondNumber,
                            std::deque<std::deque<int8_t> >& intermediarySums,
                            std::deque<int8_t>& multiplicationResult)
{
    using namespace std;

    intermediarySums.clear();
    multiplicationResult.clear();
    multiplicationResult.push_back(0);

    for (int i = 0; i < secondNumber.size(); ++i) {
        intermediarySums.push_back(deque<int8_t>());
        multiplyRow(firstNumber, secondNumber[i], intermediarySums[i]);

        intermediarySums[i].insert(intermediarySums[i].begin(), sizeof(int8_t) * i, static_cast<int8_t>(0));

        computeSumInPlace(intermediarySums[i], multiplicationResult);
        intermediarySums[i].erase(intermediarySums[i].begin(), intermediarySums[i].begin() + i);
    }
}

inline bool printMultiplication(std::deque<int8_t>& firstNumber,
                                std::deque<int8_t>& secondNumber)
{
    using namespace std;

    deque<deque<int8_t> > result;
    deque<int8_t> sumResult;
    sumResult.push_back(0);

    multiplyNumbers(firstNumber, secondNumber, result, sumResult);

    int32_t maxLineSize = static_cast<int32_t>(max(firstNumber.size(), secondNumber.size() + 1));
    int32_t firstDashSize = max(static_cast<int32_t>(secondNumber.size() + 1), static_cast<int32_t>(result[0].size()));
    int32_t nrOfSpacesForSecondDash = 0;
    int32_t nrOfSpacesForResult = 0;

    for (int i = 0; i < result.size(); ++i) {
        maxLineSize = max(maxLineSize, static_cast<int32_t>(result[i].size() + i));
    }

    maxLineSize = max(maxLineSize, static_cast<int32_t>(sumResult.size()));

    cout << string(maxLineSize - firstNumber.size(), ' ') << firstNumber << endl;
    cout << string(maxLineSize - secondNumber.size() - 1, ' ') << "*" << secondNumber << endl;
    if (secondNumber.size() > 1) {
        cout << string(maxLineSize - firstDashSize, ' ') << string(firstDashSize, '-') << endl;
    }

    if (secondNumber.size() > 1) {

        for (int i = 0; i < result.size(); ++i) {
            cout << string(maxLineSize - result[i].size() - i, ' ') << result[i] << endl;
            if (i == result.size() - 1)
                nrOfSpacesForSecondDash = static_cast<int32_t>(maxLineSize - result[i].size() - i);
        }
    }

    nrOfSpacesForResult = static_cast<int32_t>(maxLineSize - sumResult.size());
    nrOfSpacesForSecondDash = static_cast<int32_t>(min(nrOfSpacesForSecondDash, nrOfSpacesForResult));

    cout << string(nrOfSpacesForSecondDash, ' ') << string(maxLineSize - nrOfSpacesForSecondDash, '-') << endl;
    cout << string(nrOfSpacesForResult, ' ') << sumResult << endl;

    return true;
}

inline bool printOperation(std::vector<int8_t>& firstNumber,
                           std::vector<int8_t>& secondNumber, char& operation)
{
    return true;
}

inline bool decodeLine(std::string& inputLine, std::deque<int8_t>& firstNumber,
                       std::deque<int8_t>& secondNumber, char& operation)
{
    using namespace std;
    int index = 0;

    for (; index < inputLine.length(); ++index) {
        if (isOperation(inputLine[index])) {
            break;
        }
        firstNumber.push_front(inputLine[index] - '0');
    }

    // assign the operation, beware of conversions
    operation = inputLine[index];
    ++index;

    // read digits of the second number
    for (; index < inputLine.length(); ++index) {
        if (inputLine[index] == '\n' || inputLine[index] == ' ') {
            break;
        }

        secondNumber.push_front(inputLine[index] - '0');
    }

    return true;
}

inline void readInputLines(int nrOfOps, std::vector<std::string>& outResult)
{
    using namespace std;
    for (int i = 0; i < nrOfOps; ++i) {
        string tempString;
        getline(cin, tempString);
        outResult.push_back(tempString);
    }
}

inline void executeOperation(std::deque<int8_t>& firstNumber,
                             std::deque<int8_t>& secondNumber, char& operation)
{
    switch (operation) {
    case '+':
        printSum(firstNumber, secondNumber);
        break;
    case '-':
        printDifference(firstNumber, secondNumber);
        break;
    case '*':
        printMultiplication(firstNumber, secondNumber);
        break;

    default:
        exit(7);
        break;
    }
    std::cout << std::endl;
}

int main(int argc, const char* argv[])
{
    using namespace std;
    int16_t nrOfOps = 0;

    cin >> nrOfOps;
    cin.ignore();
    vector<string> inputLines;

    readInputLines(nrOfOps, inputLines);

    //cout << endl;

    for (int i = 0; i < inputLines.size(); ++i) {
        std::deque<int8_t> firstNumber;
        std::deque<int8_t> secondNumber;
        char operation;

        decodeLine(inputLines[i], firstNumber, secondNumber, operation);
        executeOperation(firstNumber, secondNumber, operation);
    }
    return 0;
}
