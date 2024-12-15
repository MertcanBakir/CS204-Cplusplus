//
// Mertcan Bakır 30879
//
#include "DNAseq.h"

using namespace std;

int DNAseq::getLength() const {
    return length; // Return the length of the DNA sequence
}

void DNAseq::setLength(int len) {
    length = len; // Set the length of the DNA sequence
}

void DNAseq::setSequence(Nucleotide* nuc) {
    delete[] sequence; // Delete the previous sequence

    sequence = nuc; // Set the sequence to the new sequence
}

Nucleotide* DNAseq::getSequence() const {
    return sequence; // Return a pointer to the sequence of nucleotides
}

DNAseq::DNAseq() {
    length = 0; // Start the length to 0
    sequence = nullptr; //Start the sequence nullptr
}

DNAseq::DNAseq(const string& dna) {
    length = dna.length(); // Get the length of the input DNA sequence

    if (length == 0) {// If the length is 0, set the sequence to nullptr
        sequence = nullptr;
    } else { // Means it is not 0
        sequence = new Nucleotide[length]; // Allocate memory for the sequence

        // Convert characters to nucleotides
        for (int i = 0; i < length; ++i) {
            if (dna[i] == 'A') {
                sequence[i] = A;
            } else if (dna[i] == 'C') {
                sequence[i] = C;
            } else if (dna[i] == 'G') {
                sequence[i] = G;
            } else if (dna[i] == 'T') {
                sequence[i] = T;
            }
        }
    }
}

DNAseq::DNAseq(const DNAseq &other) {
    length = other.length;
    if (length == 0) {// If the length is 0, set the sequence to nullptr
        sequence = nullptr;
    } else { // Means it is not 0
        sequence = new Nucleotide[length];
        for (int i = 0; i < length; ++i) {// Copy elements from the other sequence
            sequence[i] = other.sequence[i];
        }
    }
}

DNAseq::~DNAseq() {
    delete[] sequence; // Delete the sequence
    sequence = nullptr; // Set the sequence to nullptr
    length = 0; // Reset the length to 0
}


DNAseq DNAseq::operator*(int number) const {
    DNAseq result;

    result.length = length * number; // set the new length

    result.sequence = new Nucleotide[result.length]; // set the new resulting sequence

    int index = 0;
    for (int i = 0; i < number; ++i) { // repeat time
        for (int j = 0; j < length; ++j) { // goes to the every element
            result.sequence[index] = sequence[j];
            index++;
        }
    }

    return result;
}

DNAseq& DNAseq::operator=(const DNAseq &other) {
    if (this != &other) { // Check if they are not the same
        delete[] sequence; // Release previous memory space

        length = other.length;


        sequence = new Nucleotide[length]; // Create a new memory and copy
        for (int i = 0; i < length; ++i) {  // Copy the dna
            sequence[i] = other.sequence[i];
        }
    }

    return *this;
}


DNAseq DNAseq::operator+(const DNAseq& other) const {
    DNAseq result;

    if (other.sequence == nullptr) { // checks rhs is empty or not
        result.length = length;
        result.sequence = new Nucleotide[result.length];
        for (int i = 0; i < length; ++i) {
            result.sequence[i] = sequence[i];
        }
        return result;
    }
    else if (sequence == nullptr) { // checks lhs is empty or not
        result.length = other.length;
        result.sequence = new Nucleotide[result.length];
        for (int i = 0; i < result.length; ++i) {
            result.sequence[i] = other.sequence[i];
        }
        return result;
    }

    // Find the index of the first occurrence of the first nucleotide of rhs in lhs
    int index = -1;
    bool found = false;
    for (int i = 0; i < length && !found; ++i) {
        if (sequence[i] == other.sequence[0]) {
            index = i;
            found = true;
        }
    }

    // If the first nucleotide of rhs exists in lhs
    if (found) {
        result.length = length + other.length; // adjust the new length
        result.sequence = new Nucleotide[result.length]; // adjust the new sequence size

        // Copy lhs up to the first nucleotide of rhs
        for (int i = 0; i < index+1; ++i) {
            result.sequence[i] = sequence[i];
        }

        // Copy rhs
        for (int i = 0; i < other.length; ++i) {
            result.sequence[index + i + 1] = other.sequence[i];
        }

        // Copy the remaining part of lhs
        for (int i = index + 1; i < length; ++i) {
            result.sequence[i + other.length] = sequence[i];
        }
    }

    else { // Means the first nucleotide of rhs doesn't exist in lhs
        result.length = length + other.length;
        result.sequence = new Nucleotide[result.length];

        // Copy lhs
        for (int i = 0; i < length; ++i) {
            result.sequence[i] = sequence[i];
        }

        // Copy rhs
        for (int i = 0; i < other.length; ++i) {
            result.sequence[length + i] = other.sequence[i];
        }
    }

    return result;
}

DNAseq DNAseq::operator-(const DNAseq& other) const {
    DNAseq result;
    int start = -7;
    bool found = false;

    int rhsLength = other.length; // Length of the right-hand side (rhs) sequence
    int lhsLength = length; // Length of the left-hand side (lhs) sequence

    if (rhsLength == 0) { // If the length of rhs is 0, directly return lhs
        return *this;
    }

    if(rhsLength == lhsLength){ // checks that their length are same or not
        int counter = 0;
        for(int i = 0; i < rhsLength; i++){ // checks that lhs and rhs are same or not
            if(this->sequence[i] == other.sequence[i]){
                counter++;
            }
        }
        if(counter == rhsLength){ // checks it is all same or not
            result.length = 0;
            result.sequence = nullptr;
            return result;
        }
    }

    int newLength = lhsLength - rhsLength; // Calculate the new length after subtraction

    if (newLength <= 0) { // If the new length is smaller or equal to 0, return lhs
        return *this;
    }

    // Find the position where the rhs DNA sequence first occurs in the lhs DNA sequence
    int i = 0;
    while (i <= lhsLength - rhsLength && !found) {
        bool match = true;
        int j = 0;
        while (j < rhsLength && match) {
            if (sequence[i + j] != other.sequence[j]) { // Check if the sequences match
                match = false;
            }
            j++;
        }
        if (match) { // If a match is found, update positions
            start = i;
            found = true;
        }
        i++;
    }

    // If there is no match, directly return lhs
    if (start == -7) {
        return *this;
    }

    // If there is a match, create a new object by subtracting the rhs from lhs
    result.length = newLength; // set the new length
    result.sequence = new Nucleotide[newLength]; // set the new sequence

    int j = 0;
    for (int i = 0; i < start; i++, j++) {
        result.sequence[j] = sequence[i]; // Copy elements before the matching sequence
    }

    for (int i = start + rhsLength; i < lhsLength; i++, j++) {
        result.sequence[j] = sequence[i]; // Copy elements after the matching sequence
    }

    return result;
}


DNAseq& DNAseq::operator+=(const DNAseq &other) {
    *this = *this + other; // do the summation with + operator
    return *this;
}

DNAseq DNAseq::operator!() const {
    DNAseq result;
    result.length = length;
    result.sequence = new Nucleotide[result.length];

    for (int i = 0; i < length; i++) {
        if (sequence[i] == A) {
            result.sequence[i] = T;
        } else if (sequence[i] == C) {
            result.sequence[i] = G;
        } else if (sequence[i] == G) {
            result.sequence[i] = C;
        } else if (sequence[i] == T) {
            result.sequence[i] = A;
        }
    }
    return result;
}


DNAseq operator+(Nucleotide nucleotide, const DNAseq& dna) {
    int newLength = dna.getLength() + 1; // arrange the new length

    Nucleotide* newSequence = new Nucleotide[newLength]; // create a new sequence with a new size

    newSequence[0] = nucleotide;  // Set the first element to the nucleotide

    // Copy the original sequence into the new sequence
    for (int i = 0; i < dna.getLength(); ++i) {
        newSequence[i + 1] = dna.getSequence()[i];
    }

    DNAseq result;
    result.setLength(newLength); // adjust the new length


    delete[] result.getSequence(); // Delete the previous sequence memory

    result.setSequence(newSequence); // adjust the new sequence

    return result;
}


ostream& operator<<(ostream& os, const DNAseq& dna) {
    int length = dna.getLength(); // Get the length of the DNA sequence
    Nucleotide* sequence = dna.getSequence(); // Get the sequence of nucleotides

    for (int i = 0; i < length; i++) { // print the all elements with a corresponding character
        if (sequence[i] == A) {
            os << 'A';
        } else if (sequence[i] == C) {
            os << 'C';
        } else if (sequence[i] == G) {
            os << 'G';
        } else if (sequence[i] == T) {
            os << 'T';
        }
    }

    return os;
}

int operator%(const DNAseq& dna, Nucleotide nucleotide){
    int length = dna.getLength(); // Get the length of the DNA sequence
    Nucleotide* sequence = dna.getSequence(); // Get the sequence of nucleotides
    int counter = 0;

    for(int i = 0; i < length; i++){
        if( nucleotide == sequence[i]){
            counter ++;
        }
    }

    return counter;
}

bool operator<=(const DNAseq& dna, const DNAseq& other){
     int dnalen = dna.getLength();
     Nucleotide* dnaseq = dna.getSequence();
     Nucleotide* otherseq = other.getSequence();
     int otherlen = other.getLength();

    if (otherseq == nullptr) { // If the other sequence is null return false
        return false;
    }
    if (dnalen > otherlen) { // If the length of this sequence is greater than the other return false
        return false;
    }
    if (dnalen == otherlen) { // If the lengths are equal compare each nucleotide
        for (int c = 0; c < dnalen; c++) { // Goes to the every element
            if (dnaseq[c] != otherseq[c]) { // checks is it same or not
                return false;
            }
        }
        return true;
    }
    // It means they are not null and their length is not same

    for (int a = 0; a <= otherlen - dnalen; a++) { // Goes to the all possible starting positions
        bool found = true;
        for (int b = 0; b < dnalen; b++) { // Goes to each nucleotide
            if (dnaseq[b] != otherseq[a + b]) { // Checks if sequence is found in the other sequence
                found = false;
            }
        }
        if (found) { // If the sequence is found in the other sequence
            return true;
        }
    }
    return false;
}
