//Source code posted by Ranjith on electrofriends.com
//http://electrofriends.com/source-codes/software-programs/cpp-programs/cpp-data-structure/c-program-to-implement-avl-tree-its-operations/


#ifndef AVLTREE_H
#define AVLTREE_H
#include <iostream>
//#include<constream>
#include "IndexInterface.h"
#define FALSE 0
#define TRUE 1


template<typename T>
class avltree: public IndexInterface
{
    private:
        //Struct for an AVLNode
        struct AVLNode
        {
            //The data held by the node
            T data ;

            //The "balance factor"... essentially the different in height of left and right trees. Can be -1, 0, or 1
            int balfact ;

            //Pointers to the left and right nodes/children/trees
            AVLNode *left ;
            AVLNode *right ;
        } ;


    private :
        AVLNode *root ;

    public :


        //Constructor. Creates an AVLTree with no nodes
        avltree( )
        {
            root = NULL ;
        }

        AVLNode*  insert ( T data, int *h )
        {
            root = buildtree ( root, data, h ) ;
            return root ;
        }

        /**The insert function is dependent on this function, so it returns pointer to the new root of the tree.
         * The root  of the tree may be different every time a new node is inserted. This is where rebalancing occurs,
         * and is appropriately recursive
        **/
        static AVLNode* buildtree ( AVLNode *root, T data, int *h )
        {
            AVLNode *node1, *node2 ;

            //If the tree is empty, a new node is created. Its data is initalized and pointers are declared null
            //Balance factor is assigned 0
            //****This is also the recursive base case
            if ( root == NULL )
            {
                root = new AVLNode ;
                root -> data = data ;

                //In the empty tree case, there would be no subtrees, so balance would be 0.
                root -> left = NULL ;
                root -> right = NULL ;
                root -> balfact = 0 ;

                *h = TRUE ;
                return ( root ) ;
            }

            /**In the case where the data to be inserted is less than the data in the root of the tree,
             * the function is called recursively on the left subtree
             **/
            if ( data < root -> data )
            {
                //Recursive call to the left subtree. Same data and h values.
                root -> left = buildtree ( root -> left, data, h ) ;

                // If left subtree is higher
                if ( *h )
                {
                    switch ( root -> balfact )
                    {
                        case 1 :
                            node1 = root -> left ;
                            if ( node1 -> balfact == 1 )
                            {
                                std::cout << "\nRight rotation." ;
                                root -> left = node1 -> right ;
                                node1 -> right = root ;
                                root -> balfact = 0 ;
                                root = node1 ;
                            }
                            else
                            {
                                std::cout << "\nDouble rotation, left then right." ;
                                node2 = node1 -> right ;
                                node1 -> right = node2 -> left ;
                                node2 -> left = node1 ;
                                root -> left = node2 -> right ;
                                node2 -> right = root ;
                                if ( node2 -> balfact == 1 )
                                    root -> balfact = -1 ;
                                else
                                    root -> balfact = 0 ;
                                if ( node2 -> balfact == -1 )
                                    node1 -> balfact = 1 ;
                                else
                                    node1 -> balfact = 0 ;
                                root = node2 ;
                            }
                            root -> balfact = 0 ;
                            *h = FALSE ;
                            break ;

                        case 0 :
                            root -> balfact = 1 ;
                            break ;
                        case -1 :
                            root -> balfact = 0 ;
                            *h = FALSE ;
                    }
                }
            }

            if ( data > root -> data )
            {
                root -> right = buildtree ( root -> right, data, h ) ;

                if ( *h )
                {
                    switch ( root -> balfact )
                    {
                        case 1 :
                            root -> balfact = 0 ;
                            *h = FALSE ;
                            break ;
                        case 0 :
                            root -> balfact = -1 ;
                            break ;
                        case -1 :
                            node1 = root -> right ;
                            if ( node1 -> balfact == -1 )
                            {
                                std::cout << "\nLeft rotation." ;
                                root -> right = node1 -> left ;
                                node1 -> left = root ;
                                root -> balfact = 0 ;
                                root = node1 ;
                            }
                            else
                            {
                                std::cout << "\nDouble rotation, right then left." ;
                                node2 = node1 -> left ;
                                node1 -> left = node2 -> right ;
                                node2 -> right = node1 ;
                                root -> right = node2 -> left ;
                                node2 -> left = root ;
                                if ( node2 -> balfact == -1 )
                                    root -> balfact = 1 ;
                                else
                                    root -> balfact = 0 ;
                                if ( node2 -> balfact == 1 )
                                    node1 -> balfact = -1 ;
                                else
                                    node1 -> balfact = 0 ;
                                root = node2 ;
                            }
                            root -> balfact = 0 ;
                            *h = FALSE ;
                    }
                }
            }
            return ( root ) ;
        }

        void display( AVLNode *root ){
            if ( root != NULL )
            {
                display ( root -> left ) ;
                std::cout << root -> data << "\t" ;
                display ( root -> right ) ;
            }
        }
        AVLNode* deldata ( AVLNode* root, T data, int *h ) {

            AVLNode *node ;
            if ( root -> data == 13 )
                std::cout << root -> data ;
            if ( root == NULL )
            {
                std::cout << "\nNo such data." ;
                return ( root ) ;
            }
            else
            {
                if ( data < root -> data )
                {
                    root -> left = deldata ( root -> left, data, h ) ;
                    if ( *h )
                        root = balright ( root, h ) ;
                }
                else
                {
                    if ( data > root -> data )
                    {
                        root -> right = deldata ( root -> right, data, h ) ;
                        if ( *h )
                            root = balleft ( root, h ) ;
                    }
                    else
                    {
                        node = root ;
                        if ( node -> right == NULL )
                        {
                            root = node -> left ;
                            *h = TRUE ;
                            delete ( node ) ;
                        }
                        else
                        {
                            if ( node -> left == NULL )
                            {
                                root = node -> right ;
                                *h = TRUE ;
                                delete ( node ) ;
                            }
                            else
                            {
                                node -> right = del ( node -> right, node, h ) ;
                                if ( *h )
                                    root = balleft ( root, h ) ;
                            }
                        }
                    }
                }
            }
            return ( root ) ;

        }

        static AVLNode* del ( AVLNode* succ, AVLNode* node, int *h )
        {
            AVLNode *temp = succ ;

            if ( succ -> left != NULL )
            {
                succ -> left = del ( succ -> left, node, h ) ;
                if ( *h )
                    succ = balright ( succ, h ) ;
            }
            else
            {
                temp = succ ;
                node -> data = succ -> data ;
                succ = succ -> right ;
                delete ( temp ) ;
                *h = TRUE ;
            }
            return ( succ ) ;
        }
        static AVLNode* balright ( AVLNode *root, int *h )
        {
            AVLNode *temp1, *temp2 ;
            switch ( root -> balfact )
            {
                case 1 :
                    root -> balfact = 0 ;
                    break ;
                case 0 :
                    root -> balfact = -1 ;
                    *h  = FALSE ;
                    break ;
                case -1 :
                    temp1 = root -> right ;
                    if ( temp1 -> balfact <= 0 )
                    {
                        std::cout << "\nLeft rotation." ;
                        root -> right = temp1 -> left ;
                        temp1 -> left = root ;
                        if ( temp1 -> balfact == 0 )
                        {
                            root -> balfact = -1 ;
                            temp1 -> balfact = 1 ;
                            *h = FALSE ;
                        }
                        else
                        {
                            root -> balfact = temp1 -> balfact = 0 ;
                        }
                        root = temp1 ;
                    }
                    else
                    {
                        std::cout << "\nDouble rotation, right then left." ;
                        temp2 = temp1 -> left ;
                        temp1 -> left = temp2 -> right ;
                        temp2 -> right = temp1 ;
                        root -> right = temp2 -> left ;
                        temp2 -> left = root ;
                        if ( temp2 -> balfact == -1 )
                            root -> balfact = 1 ;
                        else
                            root -> balfact = 0 ;
                        if ( temp2 -> balfact == 1 )
                            temp1 -> balfact = -1 ;
                        else
                            temp1 -> balfact = 0 ;
                        root = temp2 ;
                        temp2 -> balfact = 0 ;
                    }
            }
            return ( root ) ;
        }
        static AVLNode* balleft ( AVLNode* root, int *h )
        {
            AVLNode *temp1, *temp2 ;
            switch ( root -> balfact )
            {
                case -1 :
                    root -> balfact = 0 ;
                    break ;

                case 0 :
                    root -> balfact = 1 ;
                    *h = FALSE ;
                    break ;

                case 1 :
                    temp1 = root -> left ;
                    if ( temp1 -> balfact >= 0 )
                    {
                        std::cout << "\nRight rotation." ;
                        root -> left = temp1 -> right ;
                        temp1 -> right = root ;

                        if ( temp1 -> balfact == 0 )
                        {
                            root -> balfact = 1 ;
                            temp1 -> balfact = -1 ;
                            *h = FALSE ;
                        }
                        else
                        {
                            root -> balfact = temp1 -> balfact = 0 ;
                        }
                        root = temp1 ;
                    }
                    else
                    {
                        std::cout << "\nDouble rotation, left then right." ;
                        temp2 = temp1 -> right ;
                        temp1 -> right = temp2 -> left ;
                        temp2 -> left = temp1 ;
                        root -> left = temp2 -> right ;
                        temp2 -> right = root ;
                        if ( temp2 -> balfact == 1 )
                            root -> balfact = -1 ;
                        else
                            root -> balfact = 0 ;
                        if ( temp2-> balfact == -1 )
                            temp1 -> balfact = 1 ;
                        else
                            temp1 -> balfact = 0 ;
                        root = temp2 ;
                        temp2 -> balfact = 0 ;
                    }
            }
            return ( root ) ;
        }

        void setroot ( AVLNode *avl )
        {
            root = avl ;
        }
        ~avltree( )
        {
            deltree ( root ) ;
        }

        static void deltree ( AVLNode *root ) {
            if ( root != NULL )
            {
                deltree ( root -> left ) ;
                deltree ( root -> right ) ;
            }
            delete ( root ) ;
        }

        std::vector<Document> getDocumentsForWord(Word word)
        {
            //AVLNode* temp = this->root;
            //if(temp)
        }

        void addWordToIndex(Word word)
        {

        }

} ;

#endif // AVLTREE_H
