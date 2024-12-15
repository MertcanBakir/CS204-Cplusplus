//
// Created by Mertcan Bakır on 8.04.2024.
//
#include <iostream>
#include <string>
using namespace std;

#ifndef CS204_HW4_DNASEQ_H
#define CS204_HW4_DNASEQ_H


enum Nucleotide {A, C, G, T};


class DNAseq{
public:

    DNAseq(); // default constructor

    DNAseq(const string& dna); // parametric constructor

    DNAseq(const DNAseq& other); // deep copy constructor

    ~DNAseq(); // Destructor

    DNAseq operator*(int number) const;  // Multiplication operator

    DNAseq& operator=(const DNAseq &other); // Equal operator

    DNAseq operator+(const DNAseq& other) const; // Addition operator

    DNAseq operator-(const DNAseq& other) const; // Subtraction operator

    DNAseq& operator+=(const DNAseq& other);// Compound assignment addition operator

    DNAseq operator!() const; // Reverse the nucleotides of dna

    int getLength() const; // Get the length of the sequence

    void setLength(int len); // Set the length of the sequence

    void setSequence(Nucleotide* nuc); // Set the sequence

    Nucleotide* getSequence() const; // Get the sequence


private:
    int length;

    Nucleotide* sequence;
};

DNAseq operator+(Nucleotide nucleotide, const DNAseq& dna); // Addition operator with Nucleotide

ostream& operator<<(ostream& os, const DNAseq& dna); // Output stream insertion operator

int operator%(const DNAseq& dna, Nucleotide nucleotide); // Nucleotide counter operator

bool operator<=(const DNAseq& dna, const DNAseq& other); // Subsequence checker operator


#endif //CS204_HW4_DNASEQ_H
