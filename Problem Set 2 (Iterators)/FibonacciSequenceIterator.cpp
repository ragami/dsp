
#include "FibonacciSequenceIterator.h"

//Constructor
FibonacciSequenceIterator::FibonacciSequenceIterator(const FibonacciSequenceGenerator& aSequenceObject, long long aStart) noexcept : fSequenceObject(aSequenceObject), fIndex(aStart) {
	fSequenceObject.reset();
	for (int i = 0; i <= aStart; i++)
		fSequenceObject.next();
}

const long long& FibonacciSequenceIterator::operator*() const noexcept
{
	return *fSequenceObject;
}

FibonacciSequenceIterator& FibonacciSequenceIterator::operator++() noexcept
{
	if (fSequenceObject.hasNext()) {
		fSequenceObject.next();
		fIndex++;
	}
	else {
		fIndex = std::numeric_limits<long long>::max();
	}

	return *this;
}

//Postfix increment
FibonacciSequenceIterator FibonacciSequenceIterator::operator++(int) noexcept
{
	FibonacciSequenceIterator lTemp = *this;
	++(*this);
	return lTemp;
}

//Iterator comparison
bool FibonacciSequenceIterator::operator==(const FibonacciSequenceIterator& aOther) const noexcept
{
	return (fIndex == aOther.fIndex)
		&& fSequenceObject.id() == aOther.fSequenceObject.id();
}

bool FibonacciSequenceIterator::operator!=(const FibonacciSequenceIterator& aOther) const noexcept
{
	return !(*this == aOther);
}

FibonacciSequenceIterator FibonacciSequenceIterator::begin() const noexcept
{
	FibonacciSequenceIterator lResult = *this;
	lResult.fIndex = 0;
	lResult.fSequenceObject.reset();
	return lResult;
}

FibonacciSequenceIterator FibonacciSequenceIterator::end() const noexcept
{
	FibonacciSequenceIterator lResult = *this;
	lResult.fIndex = std::numeric_limits<long long>::max();
	return lResult;
}