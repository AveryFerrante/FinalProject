#include "documentandfrequency.h"

DocumentAndFrequency::DocumentAndFrequency(int docNumb, int freq)
{
    documentNumber = docNumb;
    frequency = freq;
    finalFrequency = freq;
}

DocumentAndFrequency::DocumentAndFrequency()
{
    documentNumber = -1;
    frequency = -1;
}

void DocumentAndFrequency::increaseFreq() { finalFrequency = ++frequency; }
void DocumentAndFrequency::setFreq(int numb) { frequency = numb; }
void DocumentAndFrequency::addToFreq(int numb) { finalFrequency += numb; }
int DocumentAndFrequency::getFreq() { return frequency; }
int DocumentAndFrequency::getFinalFreq() { return finalFrequency; }
void DocumentAndFrequency::resetFreq() { finalFrequency = frequency; }

void DocumentAndFrequency::setDocNumb(int numb) { documentNumber = numb; }
int DocumentAndFrequency::getDocNumb() { return documentNumber; }





//****************************STATIC FUNCTIONS FOR OTHER ALGORITHMS TO USE***********************************************
bool DocumentAndFrequency::notCompare(DocumentAndFrequency *obj1, DocumentAndFrequency *obj2) { return(obj1->getDocNumb() < obj2->getDocNumb()); }

bool DocumentAndFrequency::descendingByFreq(DocumentAndFrequency *obj1, DocumentAndFrequency *obj2) { return(obj1->getFinalFreq() > obj2->getFinalFreq()); }

bool DocumentAndFrequency::ascendingByDocID(DocumentAndFrequency *obj1, DocumentAndFrequency *obj2) { return (obj1->getDocNumb() < obj2->getDocNumb()); }

bool DocumentAndFrequency::andCompare(DocumentAndFrequency *obj1, DocumentAndFrequency *obj2)
{
    if(obj1->getDocNumb() < obj2->getDocNumb())
    {
        obj1->addToFreq(obj2->getFreq()); // Have to keep a total tally of number of occurances of key words
        return true;
    }

    return false;
}
