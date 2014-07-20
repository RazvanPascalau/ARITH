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
std::ostream& operator<<(std::ostream& os, const std::vector<int8_t>& vectorToPrint)
{
    for (int i = 0; i < vectorToPrint.size() ; ++i) {
        os << vectorToPrint[i];
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const std::deque<int8_t>& dequeToPrint)
{
    for (int i = 0; i < dequeToPrint.size() ; ++i) {
        os << static_cast<int>(dequeToPrint[dequeToPrint.size()-i-1]);
    }
    return os;
}

inline bool isOperation (char ch)
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

void printSum(std::deque<int8_t>&firstNumber, std::deque<int8_t>&secondNumber){
    using namespace std;

    int32_t carry = 0;
    int8_t sizeDifference;
    deque<int8_t> result;
    
    deque<int8_t>& aliasBiggerDeque = firstNumber.size() > secondNumber.size() ? firstNumber : secondNumber;
    deque<int8_t>& aliasSmallerDeque = secondNumber.size() < firstNumber.size() ? secondNumber : firstNumber;
    sizeDifference = aliasBiggerDeque.size() - aliasSmallerDeque.size();
    
    for (int i = 0; i < aliasSmallerDeque.size(); ++i) {
        int8_t currentValue = static_cast<int8_t>(carry + aliasBiggerDeque[i] + aliasSmallerDeque[i]);
        carry = currentValue / 10;
        result.push_back(currentValue%10);
    }
    
    for (int i = static_cast<int>(aliasSmallerDeque.size()); i < aliasBiggerDeque.size() ; i++) {
        int8_t currentValue = static_cast<int8_t>(carry + aliasBiggerDeque[i]);
        carry = currentValue / 10;
        result.push_back(currentValue%10);
    }
    if (0 != carry) {
        result.push_back(carry);
    }
    
    int32_t nrOfDashes = static_cast<int32_t>( max(result.size(), secondNumber.size() + 1));
    
    int32_t nrOfSpacesForFirst = static_cast<int32_t>(max(static_cast<int32_t>(result.size() - firstNumber.size()),
                                                          static_cast<int32_t>( secondNumber.size()+ 1 - firstNumber.size())));
    int32_t nrOfSpacesForSecond = max(static_cast<int32_t>(result.size() - secondNumber.size()-1), 0);
    
    int32_t nrOfSpacesForResult = nrOfDashes - static_cast<int32_t>(result.size() );
    
    std::cout << string(nrOfSpacesForFirst, ' ') << firstNumber << endl;
    std::cout << string(nrOfSpacesForSecond, ' ')<< "+" << secondNumber << endl;
    std::cout << string(nrOfDashes, '-') << endl;
    std::cout << string(nrOfSpacesForResult, ' ') <<result << endl << endl;
}

inline bool printDifference(std::deque<int8_t>&firstNumber, std::deque<int8_t>&secondNumber){
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
    
    for (int i = static_cast<int>(aliasSmallerDeque.size()); i < aliasBiggerDeque.size() ; i++) {
        int8_t currentValue = static_cast<int8_t>(borrow + aliasBiggerDeque[i]);
        if (currentValue < 0) {
            currentValue += 10;
            borrow = -1;
        } else {
            borrow = 0;
        }
        result.push_back(currentValue);
    }
    
    for (int i = static_cast<int>(result.size() - 1); i > 0 && result[i] == 0 ; i--) {
        result.pop_back();
    }
   
    
    
    int32_t nrOfSpacesForFirst = firstNumber.size() == secondNumber.size() ? 1 : 0;
    int32_t nrOfSpacesForSecond = max(static_cast<int32_t>(firstNumber.size() - secondNumber.size()-1), 0);
    int32_t nrOfDashes = static_cast<int32_t>(firstNumber.size());
    
    std::cout << string(nrOfSpacesForFirst, ' ') << firstNumber << endl;
    std::cout << string(nrOfSpacesForSecond, ' ')<< "-" << secondNumber << endl;
    std::cout << string(nrOfDashes, '-') << endl;
    std::cout << result << endl << endl;
    
    return true;
}


inline bool printMultiplication(std::vector<int8_t>&firstNumber, std::vector<int8_t>&secondNumber){
    
    return true;
}

inline bool printOperation(std::vector<int8_t>&firstNumber, std::vector<int8_t>&secondNumber, char& operation){

    return true;
}

inline bool readLine(std::deque<int8_t>&firstNumber, std::deque<int8_t>&secondNumber, char& operation)
{
    using namespace std;
    char ch = 0;
    
    //read digits of the first number
    while ( std::cin>>ch) {
        if (isOperation(ch ) == true ) {
            break;
        }
        firstNumber.push_front(ch - '0');
    }
    
    //assign the operation, beware of conversions
    operation = ch;
    
    
    //read digits of the second number
    while ( std::cin>>noskipws>>ch && ch!= '\n' && ch != ' ') {
        secondNumber.push_front(ch - '0');
    }
    
    return true;
}

int main(int argc, const char * argv[])
{
    using namespace std;
    int16_t nrOfOps = 0;
    
    deque<int8_t> firstNumber;
    deque<int8_t> secondNumber;
    
    
    char operation = 0;
    
    cin >> nrOfOps;
    
    for (int16_t  i = 0; i < nrOfOps; ++i) {
        readLine(firstNumber, secondNumber, operation);
        
        printSum(firstNumber,secondNumber);
        printDifference(firstNumber, secondNumber);
        firstNumber.clear();
        secondNumber.clear();
        operation = 0;
    }
    
    
    return 0;
}

