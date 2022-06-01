// Marek Traczyński (261748)
// Lista 4 Zadanie 5
// Splay Binary Search Tree

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
    Node *parent;
    Node *left;
    Node *right;
};


/////////////////////////////////
//  Tree implementation class  //
/////////////////////////////////

class SplayTree {
    private:
    	Node *root;

        int height(Node *root) 
        {
            if (root == nullptr)
            {
                return 0;
            }
            else 
            {
                int left_height = height(root->left);
                int right_height = height(root->right);

                if (left_height >= right_height)
                {
                    return left_height + 1;
                }
                else
                {
                    return right_height + 1;
                }
            }
        }

        void delete_from_tree(Node *node, int value) 
        {
            Node *x = nullptr;
            Node *t, *s;
        
            while(node != nullptr)
            {
                if(node->value == value) 
                {
                    x = node;
                }

                if(node->value <= value) 
                {
                    node = node->right;
                } 
                else 
                {
                    node = node->left;
                }
            }

            if(x == nullptr) 
            {
                return;
            }

            split(x, s, t);

            if(s->left)
            {
                s->left->parent = nullptr;
            }

            root = join(s->left, t);
            delete s;

            s = nullptr;
        }

        void left_rotate(Node *node) 
        {
            Node *y = node->right;
            node->right = y->left;

            if(y->left != nullptr) 
            {
                y->left->parent = node;
            }

            y->parent = node->parent;
            
            if(node->parent == nullptr) 
            {
                this->root = y;
            } 
            else if(node == node->parent->left)
            {
                node->parent->left = y;
            } 
            else 
            {
                node->parent->right = y;
            }

            y->left = node;
            node->parent = y;
        }

        void right_rotate(Node *node) 
        {
            Node *y = node->left;
            node->left = y->right;

            if(y->right != nullptr) 
            {
                y->right->parent = node;
            }

            y->parent = node->parent;

            if(node->parent == nullptr) 
            {
                this->root = y;
            } 
            else if(node == node->parent->right) 
            {
                node->parent->right = y;
            } 
            else 
            {
                node->parent->left = y;
            }

            y->right = node;
            node->parent = y;
        }

        void splay(Node *node) 
        {
            while(node->parent) 
            {
                if(!node->parent->parent) 
                {
                    if(node == node->parent->left) 
                    {
                        right_rotate(node->parent);
                    } 
                    else 
                    {
                        left_rotate(node->parent);
                    }
                } 
                else if (node == node->parent->left && node->parent == node->parent->parent->left) 
                {
                    right_rotate(node->parent->parent);
                    right_rotate(node->parent);
                } 
                else if (node == node->parent->right && node->parent == node->parent->parent->right) 
                {
                    left_rotate(node->parent->parent);
                    left_rotate(node->parent);
                } 
                else if (node == node->parent->right && node->parent == node->parent->parent->left) 
                {
                    left_rotate(node->parent);
                    right_rotate(node->parent);
                } 
                else 
                {
                    right_rotate(node->parent);
                    left_rotate(node->parent);
                }
            }
        }

        Node *join(Node *s, Node *t)
        {
            if(s == nullptr) 
            {
                return t;
            }

            if(t == nullptr) 
            {
                return s;
            }

            Node *x = maximum(s);

            splay(x);
            
            x->right = t;
            t->parent = x;
            
            return x;
        }

        void split(Node *(&x), Node *(&s), Node *(&t)) 
        {
            splay(x);

            if (x->right) 
            {
                t = x->right;
                t->parent = nullptr;
            } 
            else 
            {
                t = nullptr;
            }

            s = x;
            s->right = nullptr;
            x = nullptr;
        }

        void print_tree(Node *root, int depth, char prefix, char *left_trace, char *right_trace, std::ostream &stream) 
        {
            if(root == NULL)
            {
                return;
            }
            if(root->right != NULL)
            {
                print_tree(root->right, depth + 1, '/', left_trace, right_trace, stream);
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

            if(root->left != NULL)
            {
                left_trace[depth] = '|';
                print_tree(root->left, depth + 1, '\\', left_trace, right_trace, stream);
            }
        }
 
    public:
        SplayTree() 
        {
            root = nullptr;
        }

        Node *maximum(Node *node) 
        {
            while(node->right != nullptr) 
            {
                node = node->right;
            }
            
            return node;
        }

        void insert_node(int value) 
        {
            Node *node = new Node;
            node->value = value;
            node->parent = nullptr;
            node->left = nullptr;
            node->right = nullptr;

            Node *y = nullptr;
            Node *x = this->root;

            while(x != nullptr) 
            {
                y = x;
                
                if(node->value < x->value) 
                {
                    x = x->left;
                } 
                else 
                {
                    x = x->right;
                }
            }

            node->parent = y;

            if(y == nullptr) 
            {
                root = node;
            } 
            else if(node->value < y->value) 
            {
                y->left = node;
            } 
            else 
            {
                y->right = node;
            }

            splay(node);
        }

        Node *getRoot()
        {
            return this->root;
        }

        int tree_height()
        {
            return height(this->root);
        }
        
        void delete_node(int value) {
            delete_from_tree(this->root, value);
        }

        void tree_display(char *left_trace, char *right_trace, std::ostream &stream)
        {
            if(root != nullptr)
            {
                print_tree(this->root, INITIAL_DEPTH, '-', left_trace, right_trace, stream);
            }
        }

};


void tree_test(int tree_size, GeneratorMode mode, std::ostream &logs_stream);
void log_header(GeneratorMode mode, std::ostream &stream);


int main()
{
    std::ofstream tree_logs;
    int tree_size;

    cout << "\nPlease enter tree size: ";
    cin >> tree_size;


    tree_logs.open("../logs/zad5_logs.txt");

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
    SplayTree splay_tree;
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
            splay_tree.insert_node(node_value);
        }
        else if(mode == RANDOM)
        {
            node_value = mersenne_generator(0, UPPER_LIMIT(tree_size));
            splay_tree.insert_node(node_value);
        }
        

        cout << "\n=================================";
        cout << "\nInserting node with value: " << node_value << "\n\n";
        splay_tree.tree_display(left_trace, right_trace, cout);
        
        logs_stream << "\n=================================";
        logs_stream << "\nInserting node with value: " << node_value << "\n\n";
        splay_tree.tree_display(left_trace, right_trace, logs_stream);
    }


    cout << "\n=================================";
    cout << "\n\n  >> Height of the tree: " << std::setw(DISPLAY_PADDING) << splay_tree.tree_height() << " <<\n";
    cout << "\n\n      >------------------<";
    cout << "\n      >> Deleting nodes <<";
    cout << "\n      >------------------<\n";

    logs_stream << "\n=================================";
    logs_stream << "\n\n  >> Height of the tree: " << std::setw(DISPLAY_PADDING) << splay_tree.tree_height() << " <<\n";
    logs_stream << "\n\n      >------------------<";
    logs_stream << "\n      >> Deleting nodes <<";
    logs_stream << "\n      >------------------<\n";


    for(int i = 0; i < tree_size; i++)
    {   
        int random_value = mersenne_generator(0, UPPER_LIMIT(tree_size));
        splay_tree.delete_node(random_value);


        cout << "\n=================================";
        cout << "\nDeleting node with value: " << random_value << "\n\n";
        splay_tree.tree_display(left_trace, right_trace, cout);
        
        logs_stream << "\n=================================";
        logs_stream << "\nDeleting node with value: " << random_value << "\n\n";
        splay_tree.tree_display(left_trace, right_trace, logs_stream);
    }


    cout << "\n=================================\n";
    logs_stream << "\n=================================\n";


    delete left_trace;
    delete right_trace;
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
