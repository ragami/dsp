
#include "FibonacciSequenceGenerator.h"
#include <cassert>
#include <climits>

FibonacciSequenceGenerator::FibonacciSequenceGenerator(const std::string& aID) noexcept :
    fID(aID), 
    fPrevious(0), 
    fCurrent(1) 
{}

//Get sequence ID
const std::string& FibonacciSequenceGenerator::id() const noexcept {
    return fID;
}

const long long& FibonacciSequenceGenerator::operator*() const noexcept {
    return fCurrent;
}

FibonacciSequenceGenerator::operator bool() const noexcept {
    return this->hasNext();
}

void FibonacciSequenceGenerator::reset() noexcept {
    fPrevious = 0;
    fCurrent = 1;
}

bool FibonacciSequenceGenerator::hasNext() const noexcept {
    // Check if the next Fibonacci number would cause overflow or not
    return fPrevious <= std::numeric_limits<long long>::max() - fCurrent;
}

void FibonacciSequenceGenerator::next() noexcept {
    assert(hasNext());

    // Calculate the next Fibonacci number
    long long lNext = fPrevious + fCurrent;

    fPrevious = fCurrent;
    fCurrent = lNext;
}