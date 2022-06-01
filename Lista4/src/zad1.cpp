// Marek Traczyński (261748)
// Lista 4 Zadanie 1
// Binary Search Tree

#include <iostream>
#include <ostream>
#include <fstream>
#include <iomanip>
#include "../utils/generator.h"

#define UPPER_LIMIT(x) (2 * x - 1)
#define DISPLAY_PADDING 2
#define INITIAL_DEPTH 0

using std::cout;
using std::cin;


enum GeneratorMode {
    ASCENDING,
    RANDOM
};

struct Node {
    int value;
    Node *left;
    Node *right;
};


Node *new_node(int value);
Node *insert_node(Node *root, int value);
Node *minimum_node(Node *root);
Node *delete_node(Node *root, int value);
Node *search_node(int value);
int tree_height(Node *root);
void tree_free(Node *root);
void tree_print(Node *curr, int depth, char prefix, char *left_trace, char *right_trace, std::ostream &stream);
void tree_test(int tree_size, GeneratorMode mode, std::ostream &logs_stream);
void log_header(GeneratorMode mode, std::ostream &stream);


int main()
{
    std::ofstream tree_logs;
    int tree_size;

    cout << "\nPlease enter tree size: ";
    cin >> tree_size;


    tree_logs.open("../logs/zad1_logs.txt");

    log_header(ASCENDING, tree_logs);
    tree_test(tree_size, ASCENDING, tree_logs);

    log_header(RANDOM, tree_logs);
    tree_test(tree_size, RANDOM, tree_logs);

    tree_logs.close();

 
    return 0;    
}


////////////////////////
//  Testing function  //
////////////////////////

void tree_test(int tree_size, GeneratorMode mode, std::ostream &logs_stream)
{
    Node *root = nullptr;
    char *left_trace = new char[tree_size];
    char *right_trace = new char[tree_size];


    for(int i = 0; i < tree_size; i++)
    {
        left_trace[i] = ' ';
        right_trace[i] = ' ';
    }


    cout << "\n      >-------------------<";
    cout << "\n      >> Inserting nodes <<";
    cout << "\n      >-------------------<\n";
    
    logs_stream << "\n      >-------------------<";
    logs_stream << "\n      >> Inserting nodes <<";
    logs_stream << "\n      >-------------------<\n";


    for(int i = 0; i < tree_size; i++)
    {   
        int node_value;
        
        if(mode == ASCENDING)
        {
            node_value = i + 1;
            root = insert_node(root, node_value);
        }
        else if(mode == RANDOM)
        {
            node_value = mersenne_generator(0, UPPER_LIMIT(tree_size));
            root = insert_node(root, node_value);
        }
        

        cout << "\n=================================";
        cout << "\nInserting node with value: " << node_value << "\n\n";
        tree_print(root, 0, '-', left_trace, right_trace, cout);
        
        logs_stream << "\n=================================";
        logs_stream << "\nInserting node with value: " << node_value << "\n\n";
        tree_print(root, 0, '-', left_trace, right_trace, logs_stream);
    }


    cout << "\n=================================";
    cout << "\n\n  >> Height of the tree: " << std::setw(DISPLAY_PADDING) << tree_height(root) << " <<\n";
    cout << "\n\n      >------------------<";
    cout << "\n      >> Deleting nodes <<";
    cout << "\n      >------------------<\n";

    logs_stream << "\n=================================";
    logs_stream << "\n\n  >> Height of the tree: " << std::setw(DISPLAY_PADDING) << tree_height(root) << " <<\n";
    logs_stream << "\n\n      >------------------<";
    logs_stream << "\n      >> Deleting nodes <<";
    logs_stream << "\n      >------------------<\n";


    for(int i = 0; i < tree_size; i++)
    {   
        int random_value = mersenne_generator(0, UPPER_LIMIT(tree_size));
        root = delete_node(root, random_value);


        cout << "\n=================================";
        cout << "\nDeleting node with value: " << random_value << "\n\n";
        tree_print(root, INITIAL_DEPTH, ' ', left_trace, right_trace, cout);
        
        logs_stream << "\n=================================";
        logs_stream << "\nDeleting node with value: " << random_value << "\n\n";
        tree_print(root, INITIAL_DEPTH, ' ', left_trace, right_trace, logs_stream);
    }


    cout << "\n=================================\n";
    logs_stream << "\n=================================\n";


    delete left_trace;
    delete right_trace;
    tree_free(root);
}

void log_header(GeneratorMode mode, std::ostream &stream)
{
    if(mode == ASCENDING)
    {
        cout << "\n\n  +----------------------------+";
        cout << "\n  | Tree with ascending values |";
        cout << "\n  +----------------------------+\n\n";
        
        stream << "\n\n  +----------------------------+";
        stream << "\n  | Tree with ascending values |";
        stream << "\n  +----------------------------+\n\n";
    }
    else if(mode == RANDOM)
    {
        cout << "\n\n   +-------------------------+";
        cout << "\n   | Tree with random values |";
        cout << "\n   +-------------------------+\n\n";
     
        stream << "\n\n   +-------------------------+";
        stream << "\n   | Tree with random values |";
        stream << "\n   +-------------------------+\n\n";
    }
}


/////////////////////////////////////
//  Tree implementation functions  //
/////////////////////////////////////

Node *new_node(int value)
{
    Node *temp = new Node;

    temp->value = value;
    temp->left = nullptr;
    temp->right = nullptr;

    return temp;
}

Node *insert_node(Node *root, int value)
{
    if(root == nullptr)
    {
        return new_node(value);
    }

    if(value <= root->value)
    {
        root->left = insert_node(root->left, value);
    }
    else
    {
        root->right = insert_node(root->right, value);
    }

    return root;
}

Node *minimum_node(Node *root)
{
    Node *temp = root;

    while(temp != nullptr && temp->left != nullptr)
    {
        temp = temp->left;
    }

    return temp;
}

Node *delete_node(Node *root, int value)
{
    if(root == nullptr)
    {
        return root;
    }

    if(value < root->value)
    {
        root->left = delete_node(root->left, value);
    }
    else if(value > root->value)
    {
        root->right = delete_node(root->right, value);
    }
    else
    {
        if(root->left == nullptr)
        {
            Node *temp = root->right;
            free(root);

            return temp;
        }
        else if(root->right == nullptr)
        {
            Node *temp = root->left;
            delete root;

            return temp;
        }

        Node *temp = minimum_node(root->right);
        root->value = temp->value;
        root->right = delete_node(root->right, temp->value);
    }

    return root;
}

int tree_height(Node *root) 
{
    if(root == nullptr)
    {
        return 0;
    }
    else 
    {
        int left_height = tree_height(root->left);
        int right_height = tree_height(root->right);

        if(left_height >= right_height)
        {
            return left_height + 1;
        }
        else
        {
            return right_height + 1;
        }
    }
}

void tree_free(Node *root)
{
    Node *temp = root;

    if(temp == nullptr)
    {
        return;
    }

    tree_free(temp->left);
    tree_free(temp->right);
    
    if(temp->left == nullptr && temp->right == nullptr) 
    {
        delete temp;

        return;
    }
}


void tree_print(Node *root, int depth, char prefix, char *left_trace, char *right_trace, std::ostream &stream)
{
    if(root == nullptr)
    {
        return;
    }
    if(root->right != nullptr)
    {
        tree_print(root->right, depth + 1, '/', left_trace, right_trace, stream);
    }

    if(prefix == '/')
    {
        right_trace[depth - 1] = '|';
    }
    if(prefix == '\\') 
    {
        left_trace[depth - 1] = ' ';
    }
    if(depth > INITIAL_DEPTH) 
    {
        stream << "  ";
    }

    for(int i = 0; i < depth - 1; i++)
    {
        if(right_trace[i] == '|' || left_trace[i] == '|' ) 
        {
            stream << "| ";
        } 
        else
        {
            stream << "  ";
        }
    }    

    if(depth > 0) 
    {
        stream << prefix << "---";
    }

    stream << "[" << root->value << "]\n";
    
    right_trace[depth] = ' ';

    if(root->left != nullptr)
    {
        left_trace[depth] = '|';
        tree_print(root->left, depth + 1, '\\', left_trace, right_trace, stream);
    }
}
