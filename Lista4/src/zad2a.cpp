// Marek Traczyński (261748)
// Lista 4 Zadanie 2a
// Ascending Binary Search Tree

#include <iostream>
#include <ostream>
#include <fstream>
#include <iomanip>
#include <chrono>
#include "../utils/generator.h"

#define UPPER_LIMIT(x) (2 * x - 1)
#define GENERATED_NUMBERS_BASE 10000
#define ITERATIONS_MULTIPLIER 10
#define SIMULATION_REPETITIONS 10
#define HEIGHT_ARRAY_SIZE 199
#define HEIGHT_SHIFT 1000

using std::cout;
using std::cin;
typedef steady_clock Clock;

struct InsData {
    long comparisons;
    long reads;
    int height[HEIGHT_ARRAY_SIZE];
};

struct DelData {
    long comparisons;
    long reads;
    int height[HEIGHT_ARRAY_SIZE];
};

struct Node {
    int value;
    Node *left;
    Node *right;
};

InsData simulation_data_ins[SIMULATION_REPETITIONS];
DelData simulation_data_del[SIMULATION_REPETITIONS];


Node *new_node(int value);
Node *insert_node(Node *root, int value, int k);
Node *minimum_node(Node *root, int k);
Node *delete_node(Node *root, int value, int k);
int tree_height(Node *root);
void tree_free(Node *root);
void tree_simulation(int tree_size);


int main()
{
    cout << "\n   +----------------------------+";
    cout << "\n   | Tree with ascending values |";
    cout << "\n   +----------------------------+\n\n";

    auto start = Clock::now();

    tree_simulation(GENERATED_NUMBERS_BASE);

    auto finish = Clock::now();


    duration<double> time_elapsed = finish - start;
    double duration = time_elapsed.count();

    cout << "\n   +-------------------------+";
    cout << "\n   | Simulation time elapsed |";
    cout << "\n   |   for " << std::setw(2) <<  SIMULATION_REPETITIONS << " repetitions:   |";
    cout << "\n   |                         |" << std::fixed << std::setprecision(4);
    cout << "\n   |    > " << duration << " s <     |";
    cout << "\n   +-------------------------+\n\n";
 
 
    return 0;    
}


//////////////////
//  Simulation  //
//////////////////

void tree_simulation(int n)
{
    std::ofstream ins_file, del_file, ins_height_file, del_height_file;
    int k;

    ins_file.open("../csvdata/zad2asc/BSTCRInsertAscendingData.csv");
    del_file.open("../csvdata/zad2asc/BSTCRDeleteAscendingData.csv");
    ins_height_file.open("../csvdata/zad2asc/BSTHInsertRAscendingata.csv");
    del_height_file.open("../csvdata/zad2asc/BSTHDeleteRAscendingata.csv");

    ins_file << "n; comparisons";
    del_file << "n; comparisons";
    for(k = 0; k < SIMULATION_REPETITIONS; k++)
    {
        ins_file << "; ";
        del_file << "; ";
    }
    ins_file << "reads;\n";
    del_file << "reads;\n";

    ins_height_file << "n; height;\n";
    del_height_file << "reps; height;\n";


    for(int i = 1; i <= ITERATIONS_MULTIPLIER; i++)
    {
        int tree_size = n * i;

        cout << "     >> Tree size: " << std::setw(6) << tree_size << " <<\n\n";

        ins_file << n * i << "; ";
        del_file << n * i << "; ";

        
        for(k = 0; k < SIMULATION_REPETITIONS; k++)
        {
            Node *root = nullptr;
            simulation_data_ins[k] = {0, 0, 0};
            simulation_data_del[k] = {0, 0, 0};
            int index = 0;

            cout << "    > Repetition " << std::setw(2) << k + 1 << " out of " << std::setw(2) << SIMULATION_REPETITIONS << " <\n\n";

            for(int j = 1; j <= tree_size; j++)
            {   
                int node_value = j;
                root = insert_node(root, node_value, k);

                if(tree_size == GENERATED_NUMBERS_BASE * ITERATIONS_MULTIPLIER)
                {
                    if(j <= HEIGHT_SHIFT && j % 10 == 0)
                    {
                        simulation_data_ins[k].height[index] = tree_height(root);
                        index++;
                    }
                    else if(j % 1000 == 0)
                    {
                        simulation_data_ins[k].height[index] = tree_height(root);
                        index++;
                    }
                }
            } 

            
            index = 0;
            
            for(int j = tree_size; j > 0; j--)
            {   
                int random_value = mersenne_generator(0, UPPER_LIMIT(tree_size));
                root = delete_node(root, random_value, k);

                if(tree_size == GENERATED_NUMBERS_BASE * ITERATIONS_MULTIPLIER)
                {
                    if(j != tree_size && j % 500 == 0)
                    {
                        simulation_data_del[k].height[index] = tree_height(root);
                        index++;
                    }
                }
            }

            tree_free(root);
        }

        for(k = 0; k < SIMULATION_REPETITIONS; k++)
        {
            ins_file << simulation_data_ins[k].comparisons << "; ";
            del_file << simulation_data_del[k].comparisons << "; "; 
        }

        for(k = 0; k < SIMULATION_REPETITIONS; k++)
        {
            ins_file << simulation_data_ins[k].reads << "; ";
            del_file << simulation_data_del[k].reads << "; ";
        }
        
        if(i == 10)
        {
            for(int j = 1; j <= HEIGHT_ARRAY_SIZE; j++)
            {

                if(j <= 100)                
                {
                    ins_height_file << j * 10 << "; ";
                }
                else
                {
                    ins_height_file << ((j % 100) + 1) * 1000  << "; ";
                }

                del_height_file << j * 500  << "; ";


                for(k = 0; k < SIMULATION_REPETITIONS; k++)
                {    
                    ins_height_file << simulation_data_ins[k].height[j - 1] << "; ";
                    del_height_file << simulation_data_del[k].height[j - 1] << "; ";
                }

                ins_height_file << "\n";
                del_height_file << "\n";
            }
        }

        ins_file << "\n";
        del_file << "\n";

    }

    ins_file.close();
    del_file.close();
    ins_height_file.close();
    del_height_file.close();

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

Node *insert_node(Node *root, int value, int k)
{
    if(root == nullptr)
    {
        return new_node(value);
    }

    simulation_data_ins[k].comparisons++;
    if(value <= root->value)
    {
    simulation_data_ins[k].reads++;
        root->left = insert_node(root->left, value, k);
    }
    else
    {
    simulation_data_ins[k].reads++;
        root->right = insert_node(root->right, value, k);
    }

    return root;
}

Node *minimum_node(Node *root, int k)
{
    Node *temp = root;

    while(temp != nullptr && temp->left != nullptr)
    {
        simulation_data_del[k].reads++;
        temp = temp->left;
    }

    return temp;
}

Node *delete_node(Node *root, int value, int k)
{
    if(root == nullptr)
    {
        return root;
    }

    simulation_data_del[k].comparisons++;
    if(value < root->value)
    {
        simulation_data_del[k].reads++;
        root->left = delete_node(root->left, value, k);
    }
    else if(value > root->value)
    {
        simulation_data_del[k].reads++;
        root->right = delete_node(root->right, value, k);
    }
    else
    {
        simulation_data_del[k].reads++;
        if(root->left == nullptr)
        {
            Node *temp = root->right;
            delete root;

            return temp;
        }
        else if(root->right == nullptr)
        {
            Node *temp = root->left;
            delete root;

            return temp;
        }

        simulation_data_del[k].reads += 2;
        Node *temp = minimum_node(root->right, k);
        root->value = temp->value;
        root->right = delete_node(root->right, temp->value, k);
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
