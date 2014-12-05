#include "avltree.h"

using namespace std;

avltree :: avltree( )
{
    root = NULL ;
}

void avltree :: addWordToIndex(Word *data)
{
    bool h = true;
    root = buildtree ( root, data, &h ) ;
    setroot( root );
}
AVLNode* avltree :: buildtree ( AVLNode *root, Word *data, bool *h )
{
    AVLNode *node1, *node2 ;

    if ( root == NULL )
    {
        root = new AVLNode ;
        root -> data = data ;
        root -> left = NULL ;
        root -> right = NULL ;
        root -> balfact = 0 ;
        *h = TRUE ;
        return ( root ) ;
    }
    if ( *data < *root -> data )
    {
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
                        //cout << "\nRight rotation." ;
                        root -> left = node1 -> right ;
                        node1 -> right = root ;
                        root -> balfact = 0 ;
                        root = node1 ;
                    }
                    else
                    {
                        //cout << "\nDouble rotation, left then right." ;
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

    if ( *data >  *root->data )
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
                        //cout << "\nLeft rotation." ;
                        root -> right = node1 -> left ;
                        node1 -> left = root ;
                        root -> balfact = 0 ;
                        root = node1 ;
                    }
                    else
                    {
                        //cout << "\nDouble rotation, right then left." ;
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

AVLNode* avltree :: getRoot() { return root; }

void avltree :: display (AVLNode* root)
{
    if ( root != NULL )
    {
        display ( root -> left ) ;
        cout << root -> data->getWord() << "\t" ;
        display ( root -> right ) ;
    }
}
//AVLNode* avltree :: deldata ( AVLNode *root, Word *data, int *h )
//{
//    AVLNode *node ;
//    if ( root == NULL )
//    {
//        return ( root ) ;
//    }
//    else
//    {
//        if ( data < root -> data )
//        {
//            root -> left = deldata ( root -> left, data, h ) ;
//            if ( *h )
//                root = balright ( root, h ) ;
//        }
//        else
//        {
//            if ( data > root -> data )
//            {
//                root -> right = deldata ( root -> right, data, h ) ;
//                if ( *h )
//                    root = balleft ( root, h ) ;
//            }
//            else
//            {
//                node = root ;
//                if ( node -> right == NULL )
//                {
//                    root = node -> left ;
//                    *h = TRUE ;
//                    delete ( node ) ;
//                }
//                else
//                {
//                    if ( node -> left == NULL )
//                    {
//                        root = node -> right ;
//                        *h = TRUE ;
//                        delete ( node ) ;
//                    }
//                    else
//                    {
//                        node -> right = del ( node -> right, node, h ) ;
//                        if ( *h )
//                            root = balleft ( root, h ) ;
//                    }
//                }
//            }
//        }
//    }
//    return ( root ) ;
//}
//AVLNode* avltree :: del ( AVLNode *succ, AVLNode *node, int *h )
//{
//    AVLNode *temp = succ ;

//    if ( succ -> left != NULL )
//    {
//        succ -> left = del ( succ -> left, node, h ) ;
//        if ( *h )
//            succ = balright ( succ, h ) ;
//    }
//    else
//    {
//        temp = succ ;
//        node -> data = succ -> data ;
//        succ = succ -> right ;
//        delete ( temp ) ;
//        *h = TRUE ;
//    }
//    return ( succ ) ;
//}
AVLNode* avltree :: balright ( AVLNode *root, int *h )
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
                //cout << "\nLeft rotation." ;
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
                //cout << "\nDouble rotation, right then left." ;
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
AVLNode* avltree :: balleft ( AVLNode *root, int *h )
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
               // cout << "\nRight rotation." ;
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
                //cout << "\nDouble rotation, left then right." ;
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
void avltree :: setroot ( AVLNode *avl )
{
    root = avl ;
}

avltree :: ~avltree( )
{
    cout << "Deleting AVLTree" << endl;
    deltree ( root ) ;
    cout << "Deleted AVLTree" << endl;
}


void avltree :: deltree ( AVLNode *root )
{
    if ( root != NULL )
    {
        deltree ( root -> left ) ;
        deltree ( root -> right ) ;
        delete root ;
    }
}

void avltree::buildFromIndex()
{
    ifstream inputFile(WORD_INDEX_FILE_PATH);
    try
    {
        int tempFreq = 0;
        int tempIndex = 0;
        string size = "fill"; // This is a string so I can check to see if it is on a blank line (end of the document)
        string word;
        while(!inputFile.eof() && (inputFile >> size != "")) // This also loads the length of the word
        {
            inputFile >> word;
            Word *temp = new Word(word, atoi(size.c_str()));

            inputFile >> tempIndex; // File index first
            while(tempIndex != -1)
            {
                inputFile >> tempFreq; // Frequency
                temp->addInfo(tempIndex, tempFreq);
                inputFile >> tempIndex; // File Index (or terminator -1)
            }

            this->addWordToIndex(temp);
        }
    }
    catch(...)
    {
        inputFile.close();
        throw ERROR_BUILDING_INDEX;
    }

    inputFile.close();
}

void avltree::writeOutIndex()
{
    ofstream outputFile(WORD_INDEX_FILE_PATH);
    inOrderTraverse(this->getRoot(), outputFile);
    outputFile.close();
}

void avltree::inOrderTraverse(AVLNode *root, ofstream &outputFile)
{
    if(root == NULL)
        return;

    inOrderTraverse(root->left, outputFile); // Traverse down the left side
    write(root, outputFile);
    inOrderTraverse(root->right, outputFile); // Traverse right side
}

void avltree::write(AVLNode *root, ofstream &outputFile) { root->data->writeOutIndex(outputFile); }

std::vector<DocumentAndFrequency *> *avltree::getDocumentsForWord(char *&word)
{
    AVLNode* temp = root;
    while(temp != NULL)
    {
        if(strcmp(temp->data->getWord(), word) == 0)
        {
            temp->data->sortRelevancy();
            return temp->data->getInformation();
        }
        else if(strcmp(temp->data->getWord(), word) < 0)
            temp = temp->right;
        else
            temp = temp->left;
    }

    return NULL; // Word does not exist
}

bool avltree::alreadyContains(char*& word, int documentNumber){
    AVLNode* temp = this->root;
    while(temp != NULL)
    {
        if(strcmp(temp->data->getWord(), word) == 0)
        {
            assert(temp->data != NULL);

            temp->data->updateFreqAndDoc(documentNumber);
            return true;
        }
        else if(strcmp(temp->data->getWord(), word) < 0) // Word is larger than temp
            temp = temp->right;
        else
            temp = temp->left;
    }

    return false;
}
