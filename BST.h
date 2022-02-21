#ifndef BST_H
#define BST_H

#include <iostream>

#include "BSTNode.h"

enum TraversalPlan {preorder, inorder, postorder};

template<class T>
class BST {
public: // DO NOT CHANGE THIS PART.
    BST();
    BST(const BST<T> &obj);

    ~BST();

    BSTNode<T> *getRoot() const;
    bool isEmpty() const;
    bool contains(BSTNode<T> *node) const;

    void insert(const T &data);

    void remove(const T &data);
    void removeAllNodes();

    BSTNode<T> *search(const T &data) const;
    BSTNode<T> *getSuccessor(BSTNode<T> *node, TraversalPlan tp) const;

    void print(TraversalPlan tp=inorder) const;

    BST<T> &operator=(const BST<T> &rhs);

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
    void print(BSTNode<T> *node, TraversalPlan tp) const;

    bool contains_helper(BSTNode<T> *r, BSTNode<T> *node) const;
    void insert_helper(BSTNode<T>* &r, const T &data);
    void remove_helper(BSTNode<T>* &r, const T &data);
    BSTNode<T> *search_helper(BSTNode<T> *r, const T &data) const;
    BSTNode<T> *findMin(BSTNode<T> *r);
    BSTNode<T>* copyTree(BSTNode<T>* &r, BSTNode<T>* node);
    BSTNode<T>* inorderSuccessor(BSTNode<T>* r, BSTNode<T>* node) const;
    BSTNode<T>* preorderSuccessor(BSTNode<T>* r, BSTNode<T>* node) const;
    BSTNode<T>* postorderSuccessor(BSTNode<T>* r, BSTNode<T>* node) const;

private: // DO NOT CHANGE THIS PART.
    BSTNode<T> *root;
};

#endif //BST_H

template<class T>
BST<T>::BST() {
    /* TODO */
    root = NULL;
}

template<class T>
BST<T>::BST(const BST<T> &obj) {
    /* TODO */
    root = NULL;
    *this = obj; 
}

template<class T>
BST<T>::~BST() {
    /* TODO */
    removeAllNodes();
    delete root;
}

template<class T>
BSTNode<T> *BST<T>::getRoot() const {
    /* TODO */
    return root;
}

template<class T>
bool BST<T>::isEmpty() const {
    /* TODO */
    return (root==NULL);
}

template<class T>
bool BST<T>::contains(BSTNode<T> *node) const {
    /* TODO */
    return contains_helper(root,node);
}

template<class T>
void BST<T>::insert(const T &data) {
    /* TODO */
    return insert_helper(root, data);  
}


template<class T>
void BST<T>::remove(const T &data) {
    /* TODO */
    return remove_helper(root, data);
}

template<class T>
void BST<T>::removeAllNodes() {
    /* TODO */
    while(root!=NULL)
    {
        remove(root->data);
    }
}

template<class T>
BSTNode<T> *BST<T>::search(const T &data) const {
    /* TODO */
    return search_helper(root, data);
}

template<class T>
BSTNode<T> *BST<T>::getSuccessor(BSTNode<T> *node, TraversalPlan tp) const {

    if (tp == inorder) {
        /* TODO */
        return inorderSuccessor(root,node);

    } else if (tp == preorder) {
        /* TODO */
        return preorderSuccessor(root,node);

    } else if (tp == postorder) {
        /* TODO */
        return postorderSuccessor(root,node);

    }
}

template<class T>
void BST<T>::print(TraversalPlan tp) const {

    if (tp == inorder) {
        // check if the tree is empty?
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_inorder{}" << std::endl;
            return;
        }

        // the tree is not empty.

        // recursively output the tree.
        std::cout << "BST_inorder{" << std::endl;
        print(root, inorder);
        std::cout << std::endl << "}" << std::endl;
    } else if (tp == preorder) {
        /* TODO */
        if (isEmpty()) {
            std::cout << "BST_preorder{}" << std::endl;
            return;
        }
        std::cout << "BST_preorder{" << std::endl;
        print(root, preorder);
        std::cout << std::endl << "}" << std::endl;
    } else if (tp == postorder) {
        /* TODO */
        if (isEmpty()) {
            std::cout << "BST_postorder{}" << std::endl;
            return;
        }
        std::cout << "BST_postorder{" << std::endl;
        print(root, postorder);
        std::cout << std::endl << "}" << std::endl;
    }
}

template<class T>
BST<T> &BST<T>::operator=(const BST<T> &rhs) {
    /* TODO */
    if(this != &rhs)
    {
        if(rhs.root == NULL)
        {
            this->root = NULL;
        }
        else{
            this->removeAllNodes();
            copyTree(root, rhs.root);   
        }
    }
    return *this;
}

template<class T>
void BST<T>::print(BSTNode<T> *node, TraversalPlan tp) const {

    // check if the node is NULL?
    if (node == NULL)
        return;

    if (tp == inorder) {
        // first, output left subtree and comma (if needed).
        print(node->left, inorder);
        if (node->left) {
            std::cout << "," << std::endl;
        }

        // then, output the node.
        std::cout << "\t" << node->data;

        // finally, output comma (if needed) and the right subtree.
        if (node->right) {
            std::cout << "," << std::endl;
        }
        print(node->right, inorder);
    } else if (tp == preorder) {
        /* TODO */
        std::cout << "\t" << node->data;
        
        if (node->left) {
            std::cout << "," << std::endl;
        }
        print(node->left, preorder);
        

        // finally, output comma (if needed) and the right subtree.
        if (node->right) {
            std::cout << "," << std::endl;
        }
        print(node->right, preorder);
    } else if (tp == postorder) {
        /* TODO */
        
        print(node->left, postorder);
        if (node->left) {
            std::cout << "," << std::endl;
        }

        // finally, output comma (if needed) and the right subtree.
        
        print(node->right, postorder);
        if (node->right) {
            std::cout << "," << std::endl;
        }
        std::cout << "\t" << node->data;
    }
}


    ///HELPER FUNCTIONS///
template<class T>
bool BST<T>::contains_helper(BSTNode<T> *r, BSTNode<T> *node) const {
    /* TODO */
    if(r==NULL)
    {
        return false;
    }
    else{
        if(r == node)
        {
            return true;
        }
        else{
            return contains_helper(r->right,node)||contains_helper(r->left,node);
        }
    }
}

template<class T>
void BST<T>::insert_helper(BSTNode<T>* &r, const T &data) {
    /* TODO */
    if(r==NULL)
    {
        r = new BSTNode<T>(data,NULL,NULL);
    }
    else{
        if(data < r->data)
            return insert_helper(r->left, data);
        else if(data > r->data)
            return insert_helper(r->right, data);
        else
            return;
    }
}

template<class T>
void BST<T>::remove_helper(BSTNode<T>* &r, const T &data) {
    /* TODO */
    if(r)
    {
        if(r->data == data)
        {
            if(r->left!=NULL && r->right!=NULL)
            {
                r->data = findMin(r->right)->data;
                remove_helper(r->right, r->data);
            }
            else{
                BSTNode<T>* tmp = r;
                r = (r->right!=NULL) ? r->right : r->left;
                tmp->right = NULL;
                tmp->left = NULL;
                delete tmp;
            }
        }
        else if(data < r->data)
            return remove_helper(r->left, data);
        else if(data > r->data)
            return remove_helper(r->right, data);
    }
}

template<class T>
BSTNode<T> *BST<T>::findMin(BSTNode<T> *r) {
    /* TODO */
    if(!r)
    {
        return NULL;
    }
    else if(r->left==NULL)
    {
        return r;
    }
    else{
        return findMin(r->left);
    }
}

template<class T>
BSTNode<T> *BST<T>::search_helper(BSTNode<T> *r, const T &data) const{
    if(r==NULL)
    {
        return NULL;
    }
    else{
        if(r->data == data)
        {
            return r;
        }
        else if (data > r->data)
        {
            return search_helper(r->right,data);
        }
        else if (data < r->data)
        {
            return search_helper(r->left,data);
        }
    }
    return NULL;
}

template<class T>
BSTNode<T>* BST<T>::copyTree(BSTNode<T>* &r, BSTNode<T>* node)
{
    if (node == NULL)
    {
        r = NULL;
        return NULL;
    }

    BSTNode<T>* newNode = new BSTNode<T>(node->data,NULL,NULL);

    copyTree(newNode->left, node->left);
    copyTree(newNode->right, node->right); 

    r = newNode;
    return r;
}
template<class T>
BSTNode<T>* BST<T>::inorderSuccessor(BSTNode<T>* r, BSTNode<T>* node) const{
    BSTNode<T>* res = NULL;
    if(node->right==NULL)
    {
        BSTNode<T>* tmp = r;
        T data1 = node->data;
        while(tmp->data != data1)
        {
            if(data1 > tmp->data)
            {
                tmp=tmp->right;
            }
            else
            {
                res = tmp;
                tmp = tmp->left;
            }
        }
    }
    else
    {
        res=node->right;
        while(res->left!=NULL)
        {
            res = res->left;
        }
    }
    return res;
}

template<class T>
BSTNode<T>* BST<T>::preorderSuccessor(BSTNode<T>* r, BSTNode<T>* node) const{
        BSTNode<T>* res = NULL;

        if(node->left!=NULL)
            res = node->left;
        else if(node->left==NULL&&node->right==NULL) //Check whether the node is leaf or not
        {
            BSTNode<T>* tmp = r;
            res = r;
            T data1 = node->data;
            while(tmp->data != data1)
            {
                if(tmp->right!=NULL && tmp->left!=NULL)
                {
                    if(data1 < res->data)
                    {
                        res=tmp->right;
                    }
                }
                if (data1 < tmp->data)
                {
                    tmp = tmp->left;
                }
                else
                {
                    tmp=tmp->right;
                }
                if(res==r)
                {
                    res=NULL;
                }
            }
        }
        else
        {
            res = node->right;
        }
        return res;
}

template<class T>
BSTNode<T>* BST<T>::postorderSuccessor(BSTNode<T>* r, BSTNode<T>* node) const{
    BSTNode<T>* res = NULL;
    if(node==r)
    {
        res = NULL;
    }
    else
    {
        BSTNode<T>* tmp = r;
        T data1 = node->data;
        
        while(data1!=tmp->data)
        {
            if(data1<tmp->data)
            {
                res=tmp;
                tmp=tmp->left;
            }
            else
            {
                res=tmp;
                tmp=tmp->right;
            }
        }
        if(res->right!=NULL && res->right->data!=node->data)
        {
            BSTNode<T>* curr = res->right;
            while(curr->left!=NULL || curr->right!=NULL)
            {
                if(curr->left==NULL)
                {
                    curr = curr->right;
                }
                else
                {
                    curr = curr->left;
                }
            }
            res = curr;
        }
    }
    return res;
}