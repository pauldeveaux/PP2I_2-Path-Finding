#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "station_node_priority_queue.h"

# define DEBUG_MODE false
# define DEBUG_PRINT true
# define DEBUG_STATION_ID 1

// Create the root of the queue and return it
station_node_queue *create_queue(){
    station_node_queue *tmp = malloc(sizeof(station_node_queue));
    tmp->value = NULL;
    tmp->left = NULL;
    tmp->right = NULL;
    tmp->parent = NULL;
    return tmp;
}


// Create a station_node with the given parameters and return it. The parent is null by default and the battery_after_charge is 0
station_node* create_station_node(station_t *station, double cost, double heuristic){
    station_node *node = malloc(sizeof(station_node));
    node->station = station;
    node->cost = cost;
    node->heuristic = heuristic;
    node->battery_after_charge = 0;
    node->parent = NULL;
    return node;
}

// Returns the height of the tree
int tree_height(station_node_queue *root){
    if(root == NULL){
        return 0;
    }
    else if (root->left == NULL && root->right == NULL){
        return 1;
    }
    else{
        int left_height = tree_height(root->left);
        int right_height = tree_height(root->right);
        if(left_height > right_height){
            return left_height + 1;
        }
        else{
            return right_height + 1;
        }
    }
}

// Returns the balance of the tree
int get_balance(station_node_queue *root){
    if(root == NULL){
        return 0;
    }
    else{
        int tmp = abs(tree_height(root->left)) - abs(tree_height(root->right));
        return tmp;
    }
}

// Rotate the tree to the left
station_node_queue* left_rotate(station_node_queue *node){
    station_node_queue *x = node;
    station_node_queue *y = node->right;
    y->parent = x->parent;
    if(x->parent == NULL){}
    else if(x->parent->left == x){
        x->parent->left = y;
    } 
    else{
         x->parent->right = y;
    }

    if(y->left == NULL){
        y->left = x;
        x->right = NULL;
    }
    else{
        x->right = y->left;
        y->left->parent = x;
        y->left = x;
    }
    x->parent = y;
    return y;
}   

// Rotate the tree to the right
station_node_queue* right_rotate(station_node_queue *node){
    station_node_queue *x = node;
    station_node_queue *y = node->left;
    y->parent = x->parent;
    if(x->parent == NULL){}
    else if(x->parent->left == x){
        x->parent->left = y;
    }
    else{
        x->parent->right = y;
    }
       
    if(y->right == NULL){
        y->right = x;
        x->left = NULL;
        x->parent = y;
    }
    else{
        x->left = y->right;
        y->right->parent = x;
        y->right = x;
    }  
    x->parent = y;
    return y;
}

station_node_queue * rotate_tree(station_node_queue *root){
    int balance = get_balance(root);
    int balance_right = get_balance(root->right);
    int balance_left = get_balance(root->left);

    // Simple left rotation
    if(balance == -2 && balance_right == -1)
        return left_rotate(root);
    // Simple right rotation
    else if(balance == 2 && balance_left == 1)
        return right_rotate(root);
    // Double right left rotation
    else if(balance == -2 && balance_right == 1){
        right_rotate(root->right);
        return left_rotate(root);
    }
    // double left right rotation
    else if(balance == 2 && balance_left == -1){
        left_rotate(root->left);
        return right_rotate(root);
    }
    return root;
}

// Remove a node from the queue and return the root
station_node_queue *remove_from_queue(station_node_queue *root, station_node *value){
    if(root == NULL || root->value == NULL){
        return NULL;
    }
    else if((root)->value->station->id == value->station->id){
        // If we are on the good node
        if(root->left != NULL && root->right != NULL){
            // If both nodes are not null

            // We need to find the rightest node of the left tree, exchange it with the node to delete, and delete the node
            station_node_queue *tmp = root->left;
            while(tmp->right != NULL){
                tmp = tmp->right;
            }
            station_node *tmp_value = root->value;

            root->value = tmp->value;
            tmp->value = tmp_value;    

            remove_from_queue(root->left, tmp_value);
            return root;
        }
        else if(root->right != NULL){
            // If the right node is not null
            if(root->parent == NULL){
                root->right->parent = NULL;
                station_node_queue *tmp = root->right;
                free(root);
                return tmp;
            }
            else if(root->parent->left == root){
                root->parent->left = root->right;
            }
            else{
                root->parent->right = root->right;
            }

            root->right->parent = root->parent;
            free(root);
            return NULL;
        }
        else if (root->left != NULL){
            // If the left node is not null
            if(root->parent == NULL){
                root->left->parent = NULL;
                station_node_queue *tmp = root->left;
                free(root);
                return tmp;
            }
            else if(root->parent->left == root){
                root->parent->left = root->left;
            }
            else{
                root->parent->right = root->left;
            }

            root->left->parent = root->parent;
            free(root);
            return NULL;
        }
        else{
            // If both nodes are null
            if(root->parent == NULL){
                free(root);
                return NULL;
            }
            if(root->parent->left == root){
                root->parent->left = NULL;
            }
            else{
                root->parent->right = NULL;
            }
            free(root);
            return NULL;
        }
    }
    else if(value->heuristic <= root->value->heuristic){
        // If the value is smaller than the root, we go left
        remove_from_queue(root->left, value);
    }
    else{
        // If the value is bigger than the root, we go right
        remove_from_queue(root->right, value);
    }
    
    // We test the balance of the tree and rotate it if needed
    return rotate_tree(root);
}


// Remove the minimum node from the queue and return it. Be carefull to free the value after use
station_node *unqueue(station_node_queue **root){
    station_node_queue *node = *root;
    while(node->left != NULL){
        node = node->left;
    }
    station_node *value = node->value;
    *root = remove_from_queue(*root, node->value);
    return value;
}


// Find the root of the tree and return it
station_node_queue* find_root(station_node_queue *node){
    if(node->parent != NULL){
        return find_root(node->parent);
    }
    else{
        return node;
    }
}

station_node *get_from_queue(station_node_queue *root, station_t *station){
    if(root == NULL || root->value == NULL){
        return NULL;
    }
    else if(root->value->station->id == station->id){
        return root->value;
    }
    else{
        station_node *tmp = get_from_queue(root->left, station);
        if(tmp == NULL){
            tmp = get_from_queue(root->right, station);
        }
        return tmp;
    }
}

// Insert in an avl tree
station_node_queue* insert(station_node_queue *root, station_node *node){
    if(root == NULL || root->value == NULL){
        if(root != NULL && root->value == NULL)
            free(root);
        root = create_queue();
        root->value = node;
        root->parent = NULL;
        root->left = NULL;
        root->right = NULL;
        return root;
    }
    else if(node->heuristic <= root->value->heuristic){
        if(root->left == NULL){
            root->left = create_queue();
            root->left->value = node;
            root->left->parent = root;
            root->left->left = NULL;
            root->left->right = NULL;
            return root;
        }
        else{
            insert(root->left, node);
        }
    }
    else {
        if(root->right == NULL){
            root->right = create_queue();
            root->right->value = node;
            root->right->parent = root;
            root->right->left = NULL;
            root->right->right = NULL;
            return root;
        }
        else{
            insert(root->right, node);
        }
    }

    return rotate_tree(root);
}

// Add a node to the queue
void add_to_queue(station_node_queue **root, station_node *value){
    station_node *tmp = get_from_queue(*root, value->station);
    if(tmp != NULL){
        *root = remove_from_queue(*root, tmp);
        //free(tmp);
    }

    *root = insert(*root, value);
}

// Free the queue memory
void free_queue(station_node_queue **root){
    if(*root == NULL){
        return;
    }
    station_node_queue * left = (*root)->left;
    station_node_queue * right = (*root)->right;
    //station_node_queue * parent = (*root)->parent;   

    free((*root)->value);
    free((*root));

    if(left != NULL){
        free_queue(&left);
    }
    if(right != NULL){
        free_queue(&right);
    }

    # if DEBUG_MODE
    //assert(parent == NULL);
    assert(left == NULL);
    assert(right == NULL);
    assert((*root) == NULL);
    # endif

}

// Check if a station is in the queue
bool is_in_queue(station_node_queue *root, station_t *station){
    if(root == NULL || root->value == NULL){
        return false;
    }
    else if(root->value->station->id == station->id){
        return true;
    }
    else{
        return is_in_queue(root->left, station) || is_in_queue(root->right, station);
    }

}


// Check if a station is in the queue with a lower cost
bool is_in_queue_with_lower_cost(station_node_queue *root, station_node *station){
    if(root == NULL || root->value == NULL){
        return false;
    }
    else if(root->value->station->id == station->station->id){
        if(root->value->cost <= station->cost){
            return true;
        }
    }
    else{
        if(is_in_queue_with_lower_cost(root->left, station))
            return true;
        else return is_in_queue_with_lower_cost(root->right, station);
    }
    return false;
}

// Check if the queue is empty
bool queue_is_empty(station_node_queue *root){
    return root == NULL || root->value == NULL;
}

int size_queue(station_node_queue *root){
    if(root == NULL || root->value == NULL){
        return 0;
    }
    else{
        return 1 + size_queue(root->left) + size_queue(root->right);
    }
}

// Print the queue
void print_queue(station_node_queue *root){
    if(root != NULL && root->value != NULL){
        print_queue(root->left);
        printf("%d : %f\n", root->value->station->id, root->value->heuristic);
        print_queue(root->right);
    }
}


void print_queue_prefixe(station_node_queue *root){
     if(root != NULL && root->value != NULL){
        printf("%d(", root->value->station->id);
        print_queue_prefixe(root->left);
        printf(", ");
        print_queue_prefixe(root->right);
        printf(")");
    }
    else{
        printf(" ");
    }
}
