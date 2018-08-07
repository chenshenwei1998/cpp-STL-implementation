#ifndef SJTU_DEQUE_HPP
#define SJTU_DEQUE_HPP

#include "exceptions.hpp"

#include <cstddef>
#include <cstdio>
namespace sjtu {

template<class T>
class deque {
    //Á´±í½Úµã
    struct node{
        T *data;
        node *next;
        node *pre;
        node(const T &x,node *P = NULL,node *N=NULL)
        {data = new T(x) ; pre = P ; next = N;}
        node():data(NULL),next(NULL),pre(NULL){}
        ~node(){if(data) delete data;}
    };

    node *head;
    node *tail;
public:
	class const_iterator;
	class iterator {
	    friend class deque;
	private:
		node *current;
		node *h;
		node *t;

	public:
        iterator(node *p = NULL,node *x = NULL,node *y = NULL){current = p;h = x;t = y;}
        iterator(const iterator &rhs){current = rhs.current;h = rhs.h;t = rhs.t;}
        iterator &operator=(const iterator &rhs)
        {
            current = rhs.current;h = rhs.h;t = rhs.t;
            return *this;
        }

		iterator operator+(const int &n) const {
		    if(current==NULL) throw invalid_iterator();
			iterator tmp(current,h,t);
			if(n>=0){
                for(int i = 0 ; i < n ; ++i)
                {
                    if(tmp.current!=t)
                        tmp.current = tmp.current->next;
                    else throw invalid_iterator();
                }
			}
			else{
                for(int i = 0 ; i < -n ; ++i)
                {
                    if(tmp.current->pre!=h)
                        tmp.current = tmp.current->pre;
                    else throw invalid_iterator();
                }
			}
            return tmp;
		}

		iterator operator-(const int &n) const {
		    if(current==NULL) throw invalid_iterator();
			iterator tmp(current,h,t);
			if(n>=0){
                for(int i = 0 ; i < n ; ++i)
                {
                    if(tmp.current->pre!=h)
                        tmp.current = tmp.current->pre;
                    else throw invalid_iterator();
                }
			}
			else{
                for(int i = 0 ; i < -n ; ++i)
                {
                    if(tmp.current!=t)
                        tmp.current = tmp.current->next;
                    else throw invalid_iterator();
                }
			}
            return tmp;
		}

		// return th distance between two iterator,
		int operator-(const iterator &rhs) const {
			if(h!=rhs.h) throw invalid_iterator();

			node *p1 = h;
			node *p2 = h;
			int i1 = 0;
			int i2 = 0;
			while(p1!=current){++i1;p1 = p1->next;}
			while(p2!=rhs.current){++i2;p2 = p2->next;}
			return i1-i2;
		}
		iterator &operator+=(const int &n) {
			if(current==NULL) throw invalid_iterator();
			if(n>=0){
                for(int i = 0 ; i < n ; ++i)
                {
                    if(current!=t)
                        current = current->next;
                    else throw invalid_iterator();
                }
			}
			else{
                for(int i = 0 ; i < -n ; ++i)
                {
                    if(current->pre!=h)
                        current = current->pre;
                    else throw invalid_iterator();
                }
			}
            return *this;
		}
		iterator &operator-=(const int &n) {
			if(current==NULL) throw invalid_iterator();
			if(n>=0){
                for(int i = 0 ; i < n ; ++i)
                {
                    if(current->pre!=h)
                        current = current->pre;
                    else throw invalid_iterator();
                }
			}
			else{
                for(int i = 0 ; i < -n ; ++i)
                {
                    if(current!=t)
                        current = current->next;
                    else throw invalid_iterator();
                }
			}
            return *this;
		}

		iterator operator++(int) {
		    iterator tmp(current,h,t);
		    if(current!=t) current = current->next;
		    else throw invalid_iterator();
		    return tmp;
		}

		iterator& operator++() {
            if(current!=t) current = current->next;
            else throw invalid_iterator();
            return *this;
		}

		iterator operator--(int) {
		    iterator tmp(current,h,t);
		    if(current->pre!=h) current = current->pre;
		    else throw invalid_iterator();
		    return tmp;
		}

		iterator& operator--() {
		    if(current->pre!=h) current = current->pre;
		    else throw invalid_iterator();
		    return *this;
		}

		T& operator*() const {if(current == t) throw invalid_iterator(); return *(current->data);}

		T* operator->() const noexcept {return current->data;}

		bool operator==(const iterator &rhs) const {return current==rhs.current;}
		bool operator==(const const_iterator &rhs) const {return current==rhs.current;}

		bool operator!=(const iterator &rhs) const {return current!=rhs.current;}
		bool operator!=(const const_iterator &rhs) const {return current!=rhs.current;}
	};
	class const_iterator {
		friend class deque;
		private:
			node *current;
            node *h;
            node *t;

		public:
			const_iterator(node *p = NULL,node *x = NULL,node *y = NULL) {
				current = p;h = x;t = y;
			}
			const_iterator(const const_iterator &other) {
				current = other.current;h = other.h;t = other.t;
			}
			const_iterator(const iterator &other) {
				current = other.current;h = other.h;t = other.t;
			}
			const_iterator &operator=(const const_iterator &rhs)
            {
                current = rhs.current;h = rhs.h;t = rhs.t;
                return *this;
            }
            const_iterator operator+(const int &n) const {
                if(current==NULL) throw invalid_iterator();
                const_iterator tmp(current,h,t);
                if(n>=0){
                    for(int i = 0 ; i < n ; ++i)
                    {
                        if(tmp.current!=t)
                            tmp.current = tmp.current->next;
                        else throw invalid_iterator();
                    }
                }
                else{
                    for(int i = 0 ; i < -n ; ++i)
                    {
                        if(tmp.current->pre!=h)
                            tmp.current = tmp.current->pre;
                        else throw invalid_iterator();
                    }
                }
                return tmp;
            }

            const_iterator operator-(const int &n) const {
                if(current==NULL) throw invalid_iterator();
                const_iterator tmp(current,h,t);
                if(n>=0){
                    for(int i = 0 ; i < n ; ++i)
                    {
                        if(tmp.current->pre!=h)
                            tmp.current = tmp.current->pre;
                        else throw invalid_iterator();
                    }
                }
                else{
                    for(int i = 0 ; i < -n ; ++i)
                    {
                        if(tmp.current!=t)
                            tmp.current = tmp.current->next;
                        else throw invalid_iterator();
                    }
                }
                return tmp;
            }

            // return th distance between two iterator,
            int operator-(const const_iterator &rhs) const {
                if(h!=rhs.h) throw invalid_iterator();
                node *p1 = h;
                node *p2 = h;
                int i1 = 0;
                int i2 = 0;
                while(p1!=current){++i1;p1 = p1->next;}
                while(p2!=rhs.current){++i2;p2 = p2->next;}
                return i1-i2;
            }
            const_iterator &operator+=(const int &n) {
                if(current==NULL) throw invalid_iterator();
                if(n>=0){
                    for(int i = 0 ; i < n ; ++i)
                    {
                        if(current!=t)
                            current = current->next;
                        else throw invalid_iterator();
                    }
                }
                else{
                    for(int i = 0 ; i < -n ; ++i)
                    {
                        if(current->pre!=h)
                            current = current->pre;
                        else throw invalid_iterator();
                    }
                }
                return *this;
            }
            const_iterator &operator-=(const int &n) {
                if(current==NULL) throw invalid_iterator();
                if(n>=0){
                    for(int i = 0 ; i < n ; ++i)
                    {
                        if(current->pre!=h)
                            current = current->pre;
                        else throw invalid_iterator();
                    }
                }
                else{
                    for(int i = 0 ; i < -n ; ++i)
                    {
                        if(current!=t)
                            current = current->next;
                        else throw invalid_iterator();
                    }
                }
                return *this;
            }

            const_iterator operator++(int) {
                const_iterator tmp(current,h,t);
                if(current!=t) current = current->next;
                else throw invalid_iterator();
                return tmp;
            }

            const_iterator& operator++() {
                if(current!=t) current = current->next;
                else throw invalid_iterator();
                return *this;
            }

            const_iterator operator--(int) {
                const_iterator tmp(current,h,t);
                if(current->pre!=h) current = current->pre;
                else throw invalid_iterator();
                return tmp;
            }

            const_iterator& operator--() {
                if(current->pre!=h) current = current->pre;
                else throw invalid_iterator();
                return *this;
            }

            T& operator*() const {if(current == t) throw invalid_iterator();return *(current->data);}

            T* operator->() const noexcept {return current->data;}

            bool operator==(const const_iterator &rhs) const {return current==rhs.current;}
            bool operator==(const iterator &rhs) const {return current==rhs.current;}

            bool operator!=(const iterator &rhs) const {return current!=rhs.current;}
            bool operator!=(const const_iterator &rhs) const {return current!=rhs.current;}
	};

	deque() {
	    head = new node;
	    tail = new node;
	    head->next = tail;
	    tail->pre = head;
	}

	deque(const deque &other) {
	    head = new node;
        node *p,*q;
        p = q = head;
        node *curr = other.head->next;
        while(curr->next!=NULL)
        {
            p = new node(*(curr->data));
            p->pre = q;
            q->next = p;
            q = p;
            curr = curr->next;
        }
        tail = new node;
        tail->pre = p;
        p->next = tail;
	}

	~deque(){
	    node *p = head;
	    node *q;
        while(p)
        {
            q = p;
            p = p->next;
            delete q;
        }
        head = NULL;
	}

	deque &operator=(const deque &other) {
	    if(this==&other) return *this;
        node *p;
        while(head!=NULL)
        {
            p = head;
            head = head->next;
            delete p;
        }

        node *q = new node;
        head = p = q;
        node *curr = other.head->next;
        while(curr->next!=NULL)
        {
            p = new node(*(curr->data));
            p->pre = q;
            q->next = p;
            q = p;
            curr = curr->next;
        }
        tail = new node;
        tail->pre = p;
        p->next = tail;
        return *this;
	}

	T & at(const size_t &pos) {
	    if(pos<0) throw index_out_of_bound();

        node *p = head->next;
        size_t i;
        for(i = pos ; i>0 ; --i)
        {
            if(p->next==tail) throw index_out_of_bound();
            p = p->next;
        }
        return *(p->data);
	}

	const T & at(const size_t &pos) const {
	    if(pos<0) throw index_out_of_bound();

        node *p = head->next;
        size_t i;
        for(i = pos ; i>0 ; --i)
        {
            if(p->next==tail) throw index_out_of_bound();
            p = p->next;
        }
        return *(p->data);
	}

	T & operator[](const size_t &pos) {
	    if(pos<0) throw index_out_of_bound();

        node *p = head->next;
        size_t i;
        for(i = pos ; i>0 ; --i)
        {
            if(p->next==tail) throw index_out_of_bound();
            p = p->next;
        }
        return *(p->data);
	}

	const T & operator[](const size_t &pos) const {
	    if(pos<0) throw index_out_of_bound();

        node *p = head->next;
        size_t i;
        for(i = pos ; i>0 ; --i)
        {
            if(p->next==tail) throw index_out_of_bound();
            p = p->next;
        }
        return *(p->data);
	}


	const T & front() const {if(head->next==tail) throw container_is_empty(); return *(head->next->data);}

	const T & back() const {if(head->next==tail) throw container_is_empty(); return *(tail->pre->data);}

	iterator begin() {return iterator(head->next,head,tail);}
	const_iterator cbegin() const {return const_iterator(head->next,head,tail);}

	iterator end() {return iterator(tail,head,tail);}
	const_iterator cend() const {return const_iterator(tail,head,tail);}

	bool empty() const {if(head->next==tail) return true; else return false;}

	size_t size() const {
	    size_t i = 0;
	    node *p = head;
	    while(p->next!=tail)
        {
            p = p->next;
            ++i;
        }
	    return i;
	}

	void clear() {
	    node *p;
        while(head!=NULL)
        {
            p = head;
            head = head->next;
            delete p;
        }
        head = new node;
        tail = new node;
        head->next = tail;
        tail->pre = head;
	}

	iterator insert(iterator pos, const T &value) {
	    if(head!=pos.h) throw invalid_iterator();

	    node *p = new node(value);
	    pos.current->pre->next = p;
	    p->pre = pos.current->pre;
	    p->next = pos.current;
	    pos.current->pre = p;
	    return iterator(p,head,tail);
	}
	/**
	 * removes specified element at pos.
	 * removes the element at pos.
	 * returns an iterator pointing to the following element, if pos pointing to the last element, end() will be returned.
	 * throw if the container is empty, the iterator is invalid or it points to a wrong place.
	 */
	iterator erase(iterator pos) {
        if(head->next==tail) throw invalid_iterator();
        if(pos.h!=head) throw invalid_iterator();
        if(pos.current==tail) throw invalid_iterator();

        node *tmp = pos.current->next;
        tmp->pre = pos.current->pre;
        pos.current->pre->next = tmp;
        delete pos.current;
        return iterator(tmp,head,tail);
	}

	void push_back(const T &value) {
	    node *p = new node(value);
        p->next = tail;
        p->pre = tail->pre;
        p->pre->next = p;
        tail->pre = p;
	}

	void pop_back() {
	    if(head->next==tail) throw container_is_empty();

        node *p = tail->pre;
        tail->pre = tail->pre->pre;
        tail->pre->next = tail;
        delete p;
	}

	void push_front(const T &value) {
	    node *p = new node(value);
        head->next->pre = p;
        p->next = head->next;
        p->pre = head;
        head->next = p;
	}

	void pop_front() {
	    if(head->next==tail) throw container_is_empty();

        node *p = head->next;
        head->next = head->next->next;
        head->next->pre = head;
        delete p;
	}
};

}

#endif
