#ifndef AVLTREE_H
#define AVLTREE_H
#include <iostream>
#include <stdlib.h>
#include "word.h"
#include "IndexInterface.h"
#include <fstream>
#define FALSE 0
#define TRUE 1

//AVLNode struct and destruct
struct AVLNode
{
    Word *data ;
    int balfact ;
    AVLNode *left ;
    AVLNode *right ;

    ~AVLNode()
    {
        delete left;
        delete right;
        delete data;
    }
} ;

//
class avltree : public IndexInterface
{
    private :
        AVLNode *root ;
    public :
        avltree( ) ;
        ~avltree( ) ;

        AVLNode* getRoot() ;
        static AVLNode* buildtree ( AVLNode *root, Word *data, bool *h ) ;
        void display( AVLNode* root ) ;
        AVLNode* deldata ( AVLNode* root, Word *data, int *h ) ;
        static AVLNode* del ( AVLNode *node, AVLNode* root, int *h ) ;
        static AVLNode* balright ( AVLNode *root, int *h ) ;
        static AVLNode* balleft ( AVLNode* root, int *h ) ;
        void setroot ( AVLNode *avl ) ;

        static void deltree ( AVLNode *root ) ;

        //Overridden functions from IndexInterface
        virtual void addWordToIndex(Word *word);

        virtual void writeOutIndex();
        void         inOrderTraverse(AVLNode *root, std::ofstream &outputFile); // This is called by write out index
        void         write(AVLNode *root, std::ofstream &outputFile);

        virtual void buildFromIndex();

        virtual bool alreadyContains(char*& word, int documentNumber);
        virtual std::vector<DocumentAndFrequency *>* getDocumentsForWord(char* &word);
} ;

#endif // AVLTREE_H
