#ifndef AVLTREE_H
#define AVLTREE_H
#include <iostream>
#include <stdlib.h>
#include "word.h"
#include "IndexInterface.h"
#define FALSE 0
#define TRUE 1

struct AVLNode
{
    Word *data ;
    int balfact ;
    AVLNode *left ;
    AVLNode *right ;
} ;

class avltree : public IndexInterface
{
    private :
        AVLNode *root ;
    public :
        avltree( ) ;
        AVLNode* getRoot() ;
        static AVLNode* buildtree ( AVLNode *root, Word *data, int *h ) ;
        void display( AVLNode* root ) ;
        AVLNode* deldata ( AVLNode* root, Word *data, int *h ) ;
        static AVLNode* del ( AVLNode *node, AVLNode* root, int *h ) ;
        static AVLNode* balright ( AVLNode *root, int *h ) ;
        static AVLNode* balleft ( AVLNode* root, int *h ) ;
        void setroot ( AVLNode *avl ) ;
        ~avltree( ) ;
        static void deltree ( AVLNode *root ) ;

        virtual void addWordToIndex(Word *word, int *h);
        virtual bool alreadyContains(char*& word);
        virtual std::vector<int>& getDocumentsForWord(char* &word);
} ;

#endif // AVLTREE_H
