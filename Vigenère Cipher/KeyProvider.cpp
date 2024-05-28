
#include "KeyProvider.h"
#include <cassert>
#include <cctype>

std::string KeyProvider::preprocessString(const std::string& aString) noexcept {
    std::string lResult;
    for (char lCharacter : aString) {
        if (std::isalpha(lCharacter)) {
            lResult += std::toupper(lCharacter);
        }
    }
    return lResult;
}

KeyProvider::KeyProvider(const std::string& aKeyword, const std::string& aSource) noexcept
    : fIndex(0) {
    // Compute the keyword sequence for the input text
    std::string lProcessedSource = preprocessString(aSource); // Preprocess aSource
    size_t lMessageLength = lProcessedSource.size(); // Use the size of the processed source

    // Compute fKeys by repeating the keyword for the length of the message
    std::string lKeywordUpper = preprocessString(aKeyword); // Convert keyword to uppercase
    size_t lKeywordLength = lKeywordUpper.size();
    fKeys.reserve(lMessageLength);
    for (size_t i = 0; i < lMessageLength; ++i) {
        fKeys.push_back(lKeywordUpper[i % lKeywordLength]); // Repeat keyword
    }

    assert(fKeys.size() == lMessageLength); // Ensure fKeys size matches message length
}

char KeyProvider::operator*() const noexcept {
    return fKeys[fIndex];
}

KeyProvider& KeyProvider::operator++() noexcept {
    ++fIndex;
    return *this;
}

KeyProvider KeyProvider::operator++(int) noexcept {
    KeyProvider lTemp = *this;
    ++(*this);
    return lTemp;
}

bool KeyProvider::operator==(const KeyProvider& aOther) const noexcept {
    return (fKeys == aOther.fKeys) && (fIndex == aOther.fIndex);
}

bool KeyProvider::operator!=(const KeyProvider& aOther) const noexcept {
    return !(*this == aOther);
}

KeyProvider KeyProvider::begin() const noexcept {
    return KeyProvider(*this); // Start from the beginning
}

KeyProvider KeyProvider::end() const noexcept {
    KeyProvider lEndIterator(*this);
    lEndIterator.fIndex = fKeys.size(); // Position after the last character
    return lEndIterator;
}
