#ifndef SJTU_MAP_HPP
#define SJTU_MAP_HPP
#include <iostream>
// only for std::less<T>
#include <functional>
#include <cstddef>
#include "utility.hpp"
#include "exceptions.hpp"
#include <cstdio>

namespace sjtu {

enum RBTColor{RED, BLACK};

template<
	class Key,
	class T,
	class Compare = std::less<Key>
> class map {
public:
    typedef pair<const Key, T> value_type;

    struct RBTNode{
        value_type data;    // 关键字(键值)
        RBTColor color;    // 颜色
        RBTNode *parent; // 父结点
        RBTNode *left;    // 左孩子
        RBTNode *right;    // 右孩子

        RBTNode(value_type value, RBTColor c = RED, RBTNode *p = NULL, RBTNode *l = NULL, RBTNode *r = NULL):
            data(value),color(c),parent(p),left(l),right(r) {}
    };

    RBTNode *mRoot;  //根节点
    size_t len;    //长度

	class const_iterator;
	class iterator {
	    friend class map;
	private:
		RBTNode* current;
		//RBTNode* root;
		map* address;
	public:
		iterator(RBTNode *c = NULL,map* a = NULL) {
			current = c;
			//root = r;
			address = a;
		}
		iterator(const iterator &other) {
			current = other.current;
			//root = other.root;
			address = other.address;
		}

		iterator operator++(int) {
		    if(current == NULL) throw invalid_iterator();
		    iterator tmp(current,address);
            current = successor(current);
            return tmp;
		}

		iterator & operator++() {
		    if(current == NULL) throw invalid_iterator();
		    current = successor(current);
		    return *this;
		}

		iterator operator--(int) {
		    iterator tmp(current,address);
		    if(address!=NULL&&current==NULL)
            {
                RBTNode *t = address->mRoot;
                if(t==NULL) throw invalid_iterator();
                while(t->right!=NULL) t= t->right;
                current = t;
                return tmp;
            }
		    current = predecessor(current);
		    if(current==NULL) throw invalid_iterator();
		    return tmp;
		}

		iterator & operator--() {
		    if(address!=NULL&&current==NULL)
            {
                RBTNode *t = address->mRoot;
                if(t==NULL) throw invalid_iterator();
                while(t->right!=NULL) t= t->right;
                current = t;
                return *this;
            }
		    current = predecessor(current);
		    if(current==NULL) throw invalid_iterator();
		    return *this;
		}

		value_type & operator*() const {
		    return current->data;
		}

		RBTNode* maximum(RBTNode* tree)
        {
            if (tree == NULL)
                return NULL;

            while(tree->right != NULL)
                tree = tree->right;
            return tree;
        }

        RBTNode* minimum(RBTNode* tree)
        {
            if (tree == NULL)
                return NULL;

            while(tree->left != NULL)
                tree = tree->left;
            return tree;
        }

        RBTNode* successor(RBTNode *x)
        {
            if (x->right != NULL)
                return minimum(x->right);

            RBTNode* y = x->parent;
            while ((y!=NULL) && (x==y->right))
            {
                x = y;
                y = y->parent;
            }
            return y;
        }

        RBTNode* predecessor(RBTNode *x)
        {
            if (x->left != NULL)
                return maximum(x->left);

            RBTNode* y = x->parent;
            while ((y!=NULL) && (x==y->left))
            {
                x = y;
                y = y->parent;
            }
            return y;
        }
		bool operator==(const iterator &rhs) const {return current==rhs.current&&address==rhs.address;}
		bool operator==(const const_iterator &rhs) const {return current==rhs.current&&address==rhs.address;}

		bool operator!=(const iterator &rhs) const {return current!=rhs.current||address!=rhs.address;}
		bool operator!=(const const_iterator &rhs) const {return current!=rhs.current||address!=rhs.address;}
		value_type* operator->() const noexcept {if(current!=NULL) return &(current->data);else throw invalid_iterator();}
	};

	class const_iterator {
		friend class map;
		private:
			RBTNode* current;
            //RBTNode* root;
            const map* address;
		public:
			const_iterator(RBTNode *c = NULL,const map* a = NULL){
				current = c;
				//root = r;
				address = a;
			}
			const_iterator(const const_iterator &other) {
				current = other.current;
				//root = other.root;
				address = other.address;
			}
			const_iterator(const iterator &other) {
				current = other.current;
				//root = other.root;
				address = other.address;
			}

            const_iterator operator++(int) {
                if(current == NULL) throw invalid_iterator();
                const_iterator tmp(current,address);
                current = successor(current);
                return tmp;
            }

            const_iterator & operator++() {
                if(current == NULL) throw invalid_iterator();
                current = successor(current);
                return *this;
            }

            const_iterator operator--(int) {
                const_iterator tmp(current,address);
                if(address!=NULL&&current==NULL)
                {
                    RBTNode *t = address->mRoot;
                    if(t==NULL) throw invalid_iterator();
                    while(t->right!=NULL) t= t->right;
                    current = t;
                    return tmp;
                }
                current = predecessor(current);
                if(current==NULL) throw invalid_iterator();
                return tmp;
            }

            const_iterator & operator--() {
                if(address!=NULL&&current==NULL)
                {
                    RBTNode *t = address->mRoot;
                    if(t==NULL) throw invalid_iterator();
                    while(t->right!=NULL) t= t->right;
                    current = t;
                    return *this;
                }
                current = predecessor(current);
                if(current==NULL) throw invalid_iterator();
                return *this;
            }

            value_type & operator*() const {
                return current->data;
            }

            RBTNode* maximum(RBTNode* tree)
            {
                if (tree == NULL)
                    return NULL;

                while(tree->right != NULL)
                    tree = tree->right;
                return tree;
            }

            RBTNode* minimum(RBTNode* tree)
            {
                if (tree == NULL)
                    return NULL;

                while(tree->left != NULL)
                    tree = tree->left;
                return tree;
            }

            RBTNode* successor(RBTNode *x)
            {
                if (x->right != NULL)
                    return minimum(x->right);

                RBTNode* y = x->parent;
                while ((y!=NULL) && (x==y->right))
                {
                    x = y;
                    y = y->parent;
                }
                return y;
            }

            RBTNode* predecessor(RBTNode *x)
            {
                if (x->left != NULL)
                    return maximum(x->left);

                RBTNode* y = x->parent;
                while ((y!=NULL) && (x==y->left))
                {
                    x = y;
                    y = y->parent;
                }
                return y;
            }
            bool operator==(const iterator &rhs) const {return current==rhs.current&&address==rhs.address;}
            bool operator==(const const_iterator &rhs) const {return current==rhs.current&&address==rhs.address;}

            bool operator!=(const iterator &rhs) const {return current!=rhs.current||address!=rhs.address;}
            bool operator!=(const const_iterator &rhs) const {return current!=rhs.current||address!=rhs.address;}
            value_type* operator->() const noexcept {if(current!=NULL) return &(current->data);else throw invalid_iterator();}
	};

	map()
	{
	    mRoot = NULL;
	    len = 0;
	}

	RBTNode* makeTree(RBTNode *root)
	{
	    if(root==NULL) return NULL;
	    RBTNode *t = new RBTNode(root->data,root->color);
	    if(root->left!=NULL) {t->left = makeTree(root->left);t->left->parent = t;}
	    if(root->right!=NULL) {t->right = makeTree(root->right);t->right->parent = t;}
	    return t;
	}

	map(const map &other) {
        len = other.len;
        mRoot = makeTree(other.mRoot);
	}

	map & operator=(const map &other) {
        if(this==&other) return *this;

        len = other.len;
        Destroy(mRoot);
        mRoot = makeTree(other.mRoot);
        return *this;
	}

    void Destroy(RBTNode *&root)
    {
        //RBTNode* t = root;
        if(root==NULL) return;
        Destroy(root->left);
        Destroy(root->right);
        delete root;
        root=NULL;
    }

	~map() {Destroy(mRoot);}

	RBTNode* search(const Key &key) const
	{
        RBTNode* t = mRoot;
        Compare cmp;
        while(t!=NULL&&(cmp(key,t->data.first)||cmp(t->data.first,key)))
        {
            if(cmp(t->data.first,key))
                t = t->right;
            else
                t = t->left;
        }
        return t;
	}

	T & at(const Key &key)
    {
        RBTNode *t = search(key);
        if(t==NULL) throw index_out_of_bound();

        return t->data.second;
    }
	const T & at(const Key &key) const
	{
	    RBTNode *t = search(key);
        if(t==NULL) throw index_out_of_bound();

        return t->data.second;
	}

	T & operator[](const Key &key) {
	    RBTNode *t = search(key);
	    if(t!=NULL) return t->data.second;
	    pair<iterator, bool> p = insert(pair<Key, T>(key, T()));
        return p.first.current->data.second;
	}

	const T & operator[](const Key &key) const
	{
	    RBTNode *t = search(key);
        if(t==NULL) throw index_out_of_bound();

        return t->data.second;
	}

	iterator begin() {
	    RBTNode *t = mRoot;
	    if(t==NULL) return iterator(t,this);
	    while(t->left!=NULL) t = t->left;
	    return iterator(t,this);
    }
	const_iterator cbegin() const {
	    RBTNode *t = mRoot;
	    if(t==NULL) return const_iterator(t,this);
	    while(t->left!=NULL) t = t->left;
	    return const_iterator(t,this);
    }

	iterator end() {return iterator(NULL,this);}
	const_iterator cend() const {return const_iterator(NULL,this);}

	bool empty() const { return len==0;}

	size_t size() const {return len;}

	void clear() {Destroy(mRoot);len=0;}

	pair<iterator, bool> insert(const value_type &value) {
        RBTNode* t = search(value.first);
        if(t!=NULL) return pair<iterator,bool>(iterator(t,this),false);
        RBTNode *tmp = new RBTNode(value);
        RBTinsert(mRoot,tmp);
        ++len;
        return pair<iterator,bool>(iterator(tmp,this),true);
	}

	void erase(iterator pos) {
	    if(pos.current==NULL||pos.address!=this) throw invalid_iterator();
	    RBTremove(mRoot,pos.current);
	    --len;
	}

	size_t count(const Key &key) const
	{
	    RBTNode *t = search(key);
        if(t==NULL) return 0;
        return 1;
	}

	iterator find(const Key &key) {
	    RBTNode *t = search(key);
	    return iterator(t,this);
	}
	const_iterator find(const Key &key) const {
	    RBTNode *t = search(key);
	    return const_iterator(t,this);
	}

	RBTNode* rb_parent(RBTNode *r){return r->parent;}
    RBTColor rb_color(RBTNode *r){return r->color;}

    bool rb_is_red(RBTNode *r){return r->color==RED;}
    bool rb_is_black(RBTNode *r){return r->color==BLACK;}

    void rb_set_black(RBTNode *r){r->color=BLACK;}
    void rb_set_red(RBTNode *r){r->color=RED;}

    void rb_set_parent(RBTNode *r,RBTNode *p){r->parent=p;}
    void rb_set_color(RBTNode *r,RBTColor c){r->color=c;}


    RBTNode* maximum(RBTNode* tree)
    {
        if (tree == NULL)
            return NULL;

        while(tree->right != NULL)
            tree = tree->right;
        return tree;
    }

    RBTNode* minimum(RBTNode* tree)
    {
        if (tree == NULL)
            return NULL;

        while(tree->left != NULL)
            tree = tree->left;
        return tree;
    }

    RBTNode* successor(RBTNode *x)
    {
        if (x->right != NULL)
            return minimum(x->right);

        RBTNode* y = x->parent;
        while ((y!=NULL) && (x==y->right))
        {
            x = y;
            y = y->parent;
        }
        return y;
    }

    RBTNode* predecessor(RBTNode *x)
    {
        if (x->left != NULL)
            return maximum(x->left);

        RBTNode* y = x->parent;
        while ((y!=NULL) && (x==y->left))
        {
            x = y;
            y = y->parent;
        }
        return y;
    }

    void leftRotate(RBTNode* &root,RBTNode* x)
    {
        RBTNode *y = x->right;
        x->right = y->left;
        if (y->left != NULL)
            y->left->parent = x;

        y->parent = x->parent;

        if (x->parent == NULL)
        {
            root = y;
        }
        else
        {
            if (x->parent->left == x)
                x->parent->left = y;
            else
                x->parent->right = y;
        }

        y->left = x;

        x->parent = y;
    }

    void rightRotate(RBTNode* &root, RBTNode* y)
    {

        RBTNode *x = y->left;
        y->left = x->right;
        if (x->right != NULL)
            x->right->parent = y;

        x->parent = y->parent;

        if (y->parent == NULL)
        {
            root = x;
        }
        else
        {
            if (y == y->parent->right)
                y->parent->right = x;
            else
                y->parent->left = x;
        }

        x->right = y;

        y->parent = x;
    }

    void insertFixUp(RBTNode* &root, RBTNode* node)
    {
        RBTNode *parent, *gparent;

        while ((parent = rb_parent(node)) && rb_is_red(parent))
        {
            gparent = rb_parent(parent);

            if (parent == gparent->left)
            {
                {
                    RBTNode *uncle = gparent->right;
                    if (uncle && rb_is_red(uncle))
                    {
                        rb_set_black(uncle);
                        rb_set_black(parent);
                        rb_set_red(gparent);
                        node = gparent;
                        continue;
                    }
                }

                if (parent->right == node)
                {
                    RBTNode *tmp;
                    leftRotate(root, parent);
                    tmp = parent;
                    parent = node;
                    node = tmp;
                }

                rb_set_black(parent);
                rb_set_red(gparent);
                rightRotate(root, gparent);
            }
            else
            {
                {
                    RBTNode *uncle = gparent->left;
                    if (uncle && rb_is_red(uncle))
                    {
                        rb_set_black(uncle);
                        rb_set_black(parent);
                        rb_set_red(gparent);
                        node = gparent;
                        continue;
                    }
                }

                if (parent->left == node)
                {
                    RBTNode *tmp;
                    rightRotate(root, parent);
                    tmp = parent;
                    parent = node;
                    node = tmp;
                }

                rb_set_black(parent);
                rb_set_red(gparent);
                leftRotate(root, gparent);
            }
        }

        rb_set_black(root);
    }

    void RBTinsert(RBTNode* &root, RBTNode* &node)
    {
        RBTNode *y = NULL;
        RBTNode *x = root;

        Compare cmp;
        while (x != NULL)
        {
            y = x;
            if (cmp(node->data.first,x->data.first))
                x = x->left;
            else
                x = x->right;
        }

        node->parent = y;
        if (y!=NULL)
        {
            if (cmp(node->data.first,y->data.first))
                y->left = node;
            else
                y->right = node;
        }
        else
            root = node;

        node->color = RED;

        insertFixUp(root, node);
    }

    void removeFixUp(RBTNode* &root, RBTNode *node, RBTNode *parent)
    {
        RBTNode *other;

        while ((!node || rb_is_black(node)) && node != root)
        {
            if (parent->left == node)
            {
                other = parent->right;
                if (rb_is_red(other))
                {
                    rb_set_black(other);
                    rb_set_red(parent);
                    leftRotate(root, parent);
                    other = parent->right;
                }
                if ((!other->left || rb_is_black(other->left)) &&
                    (!other->right || rb_is_black(other->right)))
                {
                    rb_set_red(other);
                    node = parent;
                    parent = rb_parent(node);
                }
                else
                {
                    if (!other->right || rb_is_black(other->right))
                    {
                        rb_set_black(other->left);
                        rb_set_red(other);
                        rightRotate(root, other);
                        other = parent->right;
                    }
                    rb_set_color(other, rb_color(parent));
                    rb_set_black(parent);
                    rb_set_black(other->right);
                    leftRotate(root, parent);
                    node = root;
                    break;
                }
            }
            else
            {
                other = parent->left;
                if (rb_is_red(other))
                {
                    rb_set_black(other);
                    rb_set_red(parent);
                    rightRotate(root, parent);
                    other = parent->left;
                }
                if ((!other->left || rb_is_black(other->left)) &&
                    (!other->right || rb_is_black(other->right)))
                {
                    rb_set_red(other);
                    node = parent;
                    parent = rb_parent(node);
                }
                else
                {
                    if (!other->left || rb_is_black(other->left))
                    {
                        rb_set_black(other->right);
                        rb_set_red(other);
                        leftRotate(root, other);
                        other = parent->left;
                    }
                    rb_set_color(other, rb_color(parent));
                    rb_set_black(parent);
                    rb_set_black(other->left);
                    rightRotate(root, parent);
                    node = root;
                    break;
                }
            }
        }
        if (node)
            rb_set_black(node);
    }

    void RBTremove(RBTNode* &root, RBTNode *node)
    {
        RBTNode *child, *parent;
        RBTColor color;

        if ( (node->left!=NULL) && (node->right!=NULL) )
        {
            RBTNode *rp = node;

            rp = rp->right;
            while (rp->left != NULL)
                rp = rp->left;

            if (rb_parent(node))
            {
                if (rb_parent(node)->left == node)
                    rb_parent(node)->left = rp;
                else
                    rb_parent(node)->right = rp;
            }
            else
                root = rp;

            child = rp->right;
            parent = rb_parent(rp);
            color = rb_color(rp);

            if (parent == node)
            {
                parent = rp;
            }
            else
            {
                if (child)
                    rb_set_parent(child, parent);
                parent->left = child;

                rp->right = node->right;
                rb_set_parent(node->right, rp);
            }

            rp->parent = node->parent;
            rp->color = node->color;
            rp->left = node->left;
            node->left->parent = rp;

            if (color == BLACK)
                removeFixUp(root, child, parent);

            delete node;
            return ;
        }

        if (node->left !=NULL)
            child = node->left;
        else
            child = node->right;

        parent = node->parent;
        color = node->color;

        if (child)
            child->parent = parent;

        if (parent)
        {
            if (parent->left == node)
                parent->left = child;
            else
                parent->right = child;
        }
        else
            root = child;

        if (color == BLACK)
            removeFixUp(root, child, parent);
        delete node;
    }
};

}

#endif
