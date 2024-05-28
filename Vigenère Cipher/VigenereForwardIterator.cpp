
#include "VigenereForwardIterator.h"
#include <cctype> 

// Constructor
VigenereForwardIterator::VigenereForwardIterator(
    const std::string& aKeyword,
    const std::string& aSource,
    EVigenereMode aMode) noexcept
    : fMode(aMode), fKeys(aKeyword, aSource), fSource(aSource), fIndex(0), fCurrentChar('\0') {
    initializeTable(); // Initialize the mapping table
    if (!fSource.empty()) {
        if (fMode == EVigenereMode::Encode) {
            encodeCurrentChar();
        }
        else if (fMode == EVigenereMode::Decode) {
            decodeCurrentChar();
        }
    }
}

// Encode the current character
void VigenereForwardIterator::encodeCurrentChar() noexcept {
    char lCurrentChar = fSource[fIndex];

    if (std::isalpha(lCurrentChar)) {
        char lKeyChar = *fKeys++;
        size_t lRow = std::toupper(lKeyChar) - 'A';
        size_t lColumn = std::toupper(lCurrentChar) - 'A';
        fCurrentChar = fMappingTable[lRow][lColumn];
        if (std::islower(lCurrentChar)) {
            fCurrentChar = std::tolower(fCurrentChar);
        }
    }
    else {
        fCurrentChar = lCurrentChar; // Non-alphabetic character, no encoding
    }
}

// Decode the current character
void VigenereForwardIterator::decodeCurrentChar() noexcept {
    char lCurrentChar = fSource[fIndex];

    if (std::isalpha(lCurrentChar)) {
        char lKeyChar = *fKeys++;
        size_t lRow = std::toupper(lKeyChar) - 'A';
        // Find the column corresponding to the current character
        for (size_t i = 0; i < CHARACTERS; ++i) {
            if (fMappingTable[lRow][i] == std::toupper(lCurrentChar)) {
                fCurrentChar = 'A' + i; // Decoded character
                if (std::islower(lCurrentChar)) {
                    fCurrentChar = std::tolower(fCurrentChar);
                }
            }
        }
    }
    else {
        fCurrentChar = lCurrentChar; // Non-alphabetic character, no decoding
    }
}

// Operator
char VigenereForwardIterator::operator*() const noexcept {
    return fCurrentChar; // Return the current character
}

// Prefix operator
VigenereForwardIterator& VigenereForwardIterator::operator++() noexcept {
    ++fIndex; // Move to the next character
    if (fIndex < fSource.size()) {
        if (fMode == EVigenereMode::Encode) {
            encodeCurrentChar(); // Encode the next character
        }
        else if (fMode == EVigenereMode::Decode) {
            decodeCurrentChar(); // Decode the next character
        }
    }
    return *this;
}

// Postfix operator
VigenereForwardIterator VigenereForwardIterator::operator++(int) noexcept {
    VigenereForwardIterator lTemp = *this; // Create a copy of the current iterator
    ++(*this); // Call operator
    return lTemp; 
}

// Equality operator
bool VigenereForwardIterator::operator==(const VigenereForwardIterator& aOther) const noexcept {
    return (fSource == aOther.fSource) && (fIndex == aOther.fIndex);
}

// Inequality operator
bool VigenereForwardIterator::operator!=(const VigenereForwardIterator& aOther) const noexcept {
    return !(*this == aOther);
}

// Method begin()
VigenereForwardIterator VigenereForwardIterator::begin() const noexcept {
    VigenereForwardIterator lIterator = *this; 
    lIterator.fIndex = 0; // Start from the beginning

    return lIterator;
}

// Method end()
VigenereForwardIterator VigenereForwardIterator::end() const noexcept {
    VigenereForwardIterator lIterator = *this; 
    lIterator.fIndex = fSource.size(); // Position after the last character
    return lIterator;
}