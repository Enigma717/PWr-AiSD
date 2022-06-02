// Marek Traczyński (261748)
// Lista 4 Zadanie 3
// Red-Black Binary Search Tree

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

enum Color : bool {
    BLACK = false,
    RED = true
};

struct Node {
    int value;
    bool color;
    Node *parent;
    Node *left;
    Node *right;
};


/////////////////////////////////
//  Tree implementation class  //
/////////////////////////////////

class RBTree {
    private:
        Node *root;
        Node *nil_node;

        int height(Node *root) 
        {
            if(root == nullptr)
            {
                return 0;
            }
            else 
            {
                int left_height = height(root->left);
                int right_height = height(root->right);

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

        void insert_fix(Node *node)
        {
            Node *uncle;
    
            while(node->parent->color == RED)
            {
                if(node->parent == node->parent->parent->right)
                {
                    uncle = node->parent->parent->left;
        
                    if(uncle->color == RED)
                    {
                        uncle->color = BLACK;
                        node->parent->color = BLACK;
                        node->parent->parent->color = RED;
                        node = node->parent->parent;
                    }
                    else
                    {
                        if(node == node->parent->left)
                        {
                            node = node->parent;
                            right_rotate(node);
                        }
        
                        node->parent->color = BLACK;
                        node->parent->parent->color = RED;
                        left_rotate(node->parent->parent);
                    }
                }
                else
                {
                    uncle = node->parent->parent->right;

                    if(uncle->color == RED)
                    {
                        uncle->color = BLACK;
                        node->parent->color = BLACK;
                        node->parent->parent->color = RED;
                        node = node->parent->parent;
                    }
                    else
                    {
                        if(node == node->parent->right)
                        {
                            node = node->parent;
                            left_rotate(node);
                        }
        
                        node->parent->color = BLACK;
                        node->parent->parent->color = RED;
                        right_rotate(node->parent->parent);
                    }
                }
                
                if(node == root)
                {
                    break;
                }
            }
    
            root->color = BLACK;
        }

        void delete_from_tree(Node *node, int value) 
        {
            Node *z = nil_node;
            Node *x, *y;

            while (node != nil_node) 
            {
                if(node->value == value) 
                {
                    z = node;
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
    
            if(z == nil_node) 
            {
                return;
            }

            y = z;

            int y_original_color = y->color;
            
            if(z->left == nil_node) 
            {
                x = z->right;
                
                tree_transplant(z, z->right);
            } 
            else if(z->right == nil_node) 
            {
                x = z->left;

                tree_transplant(z, z->left);
            } 
            else 
            {
                y = minimum(z->right);
                y_original_color = y->color;
                x = y->right;
            
                if(y->parent == z) 
                {
                    x->parent = y;
                } 
                else 
                {
                    tree_transplant(y, y->right);

                    y->right = z->right;
                    y->right->parent = y;
                }

                tree_transplant(z, y);
                
                y->left = z->left;
                y->left->parent = y;
                y->color = z->color;

            }

            delete z;

            if(y_original_color == 0) 
            {
                delete_fix(x);
            }
        }

        void delete_fix(Node *node) 
        {
            Node *s;

            while (node != root && node->color == BLACK) 
            {
                if (node == node->parent->left) 
                {
                    s = node->parent->right;

                    if (s->color == RED) 
                    {
                        s->color = BLACK;
                        node->parent->color = RED;
                        
                        left_rotate(node->parent);
                        s = node->parent->right;
                    }

                if (s->left->color == BLACK && s->right->color == BLACK) 
                {
                    s->color = RED;
                    node = node->parent;
                } 
                else 
                {
                    if (s->right->color == BLACK) 
                    {
                        s->left->color = BLACK;
                        s->color = RED;
                    
                        right_rotate(s);
                        s = node->parent->right;
                    }

                    s->color = node->parent->color;
                    node->parent->color = BLACK;
                    s->right->color = BLACK;
                    
                    left_rotate(node->parent);
                    node = root;
                }
                } 
                else 
                {
                    s = node->parent->left;

                    if (s->color == RED) 
                    {
                        s->color = BLACK;
                        node->parent->color = RED;
                        
                        right_rotate(node->parent);
                        s = node->parent->left;
                    }

                    if (s->right->color == BLACK && s->right->color == BLACK) 
                    {
                        s->color = RED;
                        node = node->parent;
                    } 
                    else 
                    {
                        if (s->left->color == BLACK) 
                        {
                            s->right->color = BLACK;
                            s->color = RED;
                            
                            left_rotate(s);
                            s = node->parent->left;
                        }

                        s->color = node->parent->color;
                        node->parent->color = BLACK;
                        s->left->color = BLACK;
                        
                        right_rotate(node->parent);
                        node = root;
                    }
                }
            }

            node->color = BLACK;
        }        

        void left_rotate(Node *node)
        {
            Node *y = node->right;
            node->right = y->left;
            
            if(y->left != nil_node)
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
            
            if(y->left != nil_node)
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

        void tree_transplant(Node *u, Node *v) 
        {
            if(u->parent == nullptr) 
            {
                root = v;
            } 
            else if(u == u->parent->left) 
            {
                u->parent->left = v;
            } 
            else 
            {
                u->parent->right = v;
            }
            
            v->parent = u->parent;
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

            if(root != nil_node)
            {
                if(&stream == &cout)
                {
                    if(root->color == RED)
                    {
                        stream << "\u001b[31m[" << root->value << ":R]\u001b[0m\n";
                    }
                    else
                    {
                        stream << "\u001b[30;1m[" << root->value << ":B]\u001b[0m\n";
                    }
                }
                else
                {
                    stream << "[" << root->value << (root->color ? ":R]\n" : ":B]\n");
                }
            }
            else
            {
                stream << "[NIL]\n";
            }
            
            right_trace[depth] = ' ';

            if(root->left != NULL)
            {
                left_trace[depth] = '|';
                print_tree(root->left, depth + 1, '\\', left_trace, right_trace, stream);
            }
        }

    public:
        RBTree()
        {
            nil_node = new Node;
            nil_node->color = BLACK;
            nil_node->left = nullptr;
            nil_node->right = nullptr;
            root = nil_node;
        }

        Node *minimum(Node *node) 
        {
            while(node->left != nil_node) 
            {
                node = node->left;
            }

            return node;
        }

        void insert_node(int value)
        {
            Node *node = new Node;
            node->value = value;
            node->color = RED;
            node->parent = nullptr;
            node->left = nil_node;
            node->right = nil_node;

            Node *y = nullptr;
            Node *x = this->root;

            while(x != nil_node)
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

            if(node->parent == nullptr)
            {
                node->color = BLACK;
                return;
            }

            if(node->parent->parent == nullptr)
            {
                return;
            }

            insert_fix(node);
        }

        Node *get_root()
        {
            return this->root;
        }

        int tree_height()
        {
            return height(this->root);
        }
        
        void delete_node(int value) 
        {
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


    tree_logs.open("../logs/zad3_logs.txt");

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
    RBTree rb_tree;
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


    for(int i = 1; i <= tree_size; i++)
    {   
        int node_value;
        
        if(mode == ASCENDING)
        {
            node_value = i;
            rb_tree.insert_node(node_value);
        }
        else if(mode == RANDOM)
        {
            node_value = mersenne_generator(0, UPPER_LIMIT(tree_size));
            rb_tree.insert_node(node_value);
        }

        cout << "\n=================================";
        cout << "\nInserting node with value: " << node_value << "\n\n";
        rb_tree.tree_display(left_trace, right_trace, cout);
        
        logs_stream << "\n=================================";
        logs_stream << "\nInserting node with value: " << node_value << "\n\n";
        rb_tree.tree_display(left_trace, right_trace, logs_stream);
    }


    cout << "\n=================================";
    cout << "\n\n  >> Height of the tree: " << std::setw(DISPLAY_PADDING) << rb_tree.tree_height() - 1 << " <<\n";
    cout << "\n\n      >------------------<";
    cout << "\n      >> Deleting nodes <<";
    cout << "\n      >------------------<\n";

    logs_stream << "\n=================================";
    logs_stream << "\n\n  >> Height of the tree: " << std::setw(DISPLAY_PADDING) << rb_tree.tree_height() - 1 << " <<\n";
    logs_stream << "\n\n      >------------------<";
    logs_stream << "\n      >> Deleting nodes <<";
    logs_stream << "\n      >------------------<\n";


    for(int i = 0; i < tree_size; i++)
    {   
        int random_value = mersenne_generator(0, UPPER_LIMIT(tree_size));
        rb_tree.delete_node(random_value);


        cout << "\n=================================";
        cout << "\nDeleting node with value: " << random_value << "\n\n";
        rb_tree.tree_display(left_trace, right_trace, cout);
        
        logs_stream << "\n=================================";
        logs_stream << "\nDeleting node with value: " << random_value << "\n\n";
        rb_tree.tree_display(left_trace, right_trace, logs_stream);
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
