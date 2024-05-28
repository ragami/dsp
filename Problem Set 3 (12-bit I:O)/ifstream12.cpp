
#include "ifstream12.h"
#include <iostream>
#include <cstddef> // for std::byte
#include <cassert>

// Constructor
ifstream12::ifstream12(const char* aFileName, size_t aBufferSize)
    : fBufferSize(aBufferSize),
    fByteCount(0),
    fByteIndex(0),
    fBitIndex(-1),
    fBuffer(nullptr) {
    // Allocate the input buffer
    fBuffer = new std::byte[fBufferSize];
    memset(fBuffer, 0, fBufferSize);

    // Open the file if a filename is provided
    if (aFileName) {
        open(aFileName);
    }
}

// Destructor
ifstream12::~ifstream12() {
    close();
    delete[] fBuffer;
}

// Open a file for input
void ifstream12::open(const char* aFileName) {
    if (fIStream.is_open()) {
        fIStream.close(); // Close any currently open file
    }
    fIStream.open(aFileName, std::ios::binary); // Open in binary mode
    reset(); // Initialize/reset buffer indices
}

// Close the file stream
void ifstream12::close() {
    if (fIStream.is_open()) {
        fIStream.close(); // Close the file stream
    }
    reset(); // Reset buffer and indices
}

// Check if the file is open
bool ifstream12::isOpen() const {
    return fIStream.is_open();
}

// Check if the file stream is in a good state
bool ifstream12::good() const {
    return fIStream.good();
}

// Check if the end of file is reached
bool ifstream12::eof() const {
    return (fByteCount == 0) && fIStream.eof();
}

// Reset the buffer indices and bit index
void ifstream12::reset() {
    fByteCount = 0;
    fByteIndex = 0;
    fBitIndex = -1;
}

// Fetch data from the input file stream into the buffer
void ifstream12::fetch_data() {
    // Read data into the buffer if the stream is good
    if (fIStream.good()) {
        fIStream.read(reinterpret_cast<char*>(fBuffer), fBufferSize);
        fByteCount = fIStream.gcount(); // Get the number of bytes read

        // Reset indices for bit reading
        fByteIndex = 0;
        fBitIndex = 7;
    }
    else {
        fByteCount = 0; // No data available
    }
}

// Read the next individual bit from the buffer
std::optional<size_t> ifstream12::readBit() {
    // Check if new data is needed
    if (fByteCount == 0) {
        fetch_data();
        if (fByteCount == 0) {
            return std::nullopt;
        }
    }

    // Extract the bit using the current index
    std::byte lNextBit = fBuffer[fByteIndex] & (std::byte{ 1 } << fBitIndex);
    size_t lResult = (std::to_integer<size_t>(lNextBit) >> fBitIndex);

    // Move to the next bit
    --fBitIndex;

    // Handle byte transition if necessary
    if (fBitIndex < 0) {
        fBitIndex = 7;
        ++fByteIndex;

        // Ensure we do not exceed the buffer bounds
        if (fByteIndex >= fBufferSize || fByteIndex >= fByteCount) {
            fetch_data();
        }
    }
    return lResult;
}

// Extract a 12-bit value using the read12Bits algorithm
ifstream12& ifstream12::operator>>(size_t& aValue) {
    aValue = 0;
    for (int i = 0; i < 12; ++i) {
        std::optional<size_t> lNextBit = readBit();

        if (!lNextBit)
            break;
        else if (lNextBit == 1)
        {
            aValue |= (static_cast<size_t>(1) << i);
        }
    }
    return *this;
}