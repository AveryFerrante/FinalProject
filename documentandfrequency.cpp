#include "documentandfrequency.h"

DocumentAndFrequency::DocumentAndFrequency(int docNumb, int freq)
{
    documentNumber = docNumb;
    frequency = freq;
}

void DocumentAndFrequency::increaseFreq() { ++frequency; }
int DocumentAndFrequency::getDocNumb() { return documentNumber; }
int DocumentAndFrequency::getFreq() { return frequency; }
