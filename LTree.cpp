#include <bits/stdc++.h>


#define dbs(i) std::cout<<"lol"<<i<<"\n"


namespace ksb{
    int c = 0;
    int cc = 0;
    int dd = 0;
    template<typename T>
    class LTree
    {
        // _list is class to hold list of LTrees
        class _list
        {
        public:
            // _st is a subtree
            LTree<T> *_st;

            // __prnt is parent Ltree if any
            LTree<T> * __prnt;

            // next pointer(front) of the list
            _list *_ft;

            // prev pointer(front) of the list
            _list *_rr;

            // Simple Constructor
            _list(LTree<T> *st = new LTree<T>(),  LTree<T> *prnt=nullptr, _list *ft=nullptr, _list *rr=nullptr): _st(st), _ft(ft), _rr(rr), __prnt(prnt){};
            
        };

        // _dt is the Data
        T _dt;

        // _errordt is return when tried to index out of the bound
        T _errordt;

        // stores size of the Data Structure LTree
        size_t _sz;

        // list head
        _list *_head;

        // end point
        _list *_end;

        // parent list if any
        _list *_prnt;

        // Max allowed size (applicable only for subtrees)
        size_t _mxsz;


    public:


        using value_type        = T;
        using size_type         = size_t;
        using pointer           = value_type*;
        using const_pointer     = const value_type*;
        using reference         = value_type&;
        using const_reference   = const value_type&;

        // Constructor : 
        // each data is taken and distributed across the subtree;
        LTree(size_t n = 0, T dt = T()): _sz(n){
            size_t it = 1;
            _dt = dt;

            if(n > 0)
            {
                // initialising _end and _head
                --n;
                _list *tt = nullptr;
                _list *pr = nullptr;
                _prnt = nullptr;
                _end = new _list(new LTree<T>(0, dt), this);
                _end -> _st -> _prnt = _end;
                _head = _end;
                _mxsz = n+1;

                // distributing data across subtree of max-size 1
                if(n>0){
                    size_t ssz = std::min(it, n);
                    _head = new _list(new LTree<T>(ssz, dt), this);
                    _head -> _st -> _prnt = _head;
                    _head -> _st -> _mxsz = it;
                    _head -> _rr = pr;
                    _head -> _ft = _end;
                    _end -> _rr = _head;
                    pr = _head;
                    tt = _head -> _ft;
                    if(it >= n) n = 0;
                    else n = n - it;
                    it = it * 2;
                }

                // distributing data across subtree of max-size 2, 4, 8, 16, 32, .......
                while(n>0){
                    size_t ssz = std::min(it, n);
                    tt = new _list(new LTree<T>(ssz, dt), this);
                    tt -> _st -> _prnt = tt;
                    tt -> _st -> _mxsz = it;
                    tt -> _rr = pr;
                    tt -> _ft = pr -> _ft;
                    pr -> _ft -> _rr = tt;
                    pr -> _ft = tt;
                    pr = tt;
                    tt = tt -> _ft;
                    if(it >= n) n = 0;
                    else n = n - it;
                    it = it * 2;
                }
            }
        };

        class iterator : public std::iterator<std::random_access_iterator_tag, T, ptrdiff_t, T*, T&>
        {
            LTree<T> *_ptr;
        public:

            // Commented out as it is already in parent class

            using value_type        = T;
            using size_type         = size_t;
            using difference_type   = ptrdiff_t;
            using pointer           = value_type*;
            using const_pointer     = const value_type*;
            using reference         = value_type&;
            using const_reference   = const value_type&;
            iterator(LTree<T> *ptr=nullptr): _ptr(ptr){};
            iterator(const iterator &x): _ptr(x._ptr){};
            iterator(iterator &&x): _ptr(x._ptr){x._ptr = nullptr;};
            

            iterator& operator=(iterator&& x){
                // dbs(15);
                _ptr = x._ptr;
                x._ptr = nullptr;
                return *this;
            }

            iterator& operator=(const iterator& x){
                // dbs(14);
                _ptr = x._ptr;
                return *this;
            }



            iterator operator++(){
                // dbs(1);
                if(_ptr -> _head != _ptr -> _end){
                    _ptr = (_ptr -> _head->_st);
                    return *this;
                }
                else if(_ptr -> _prnt != nullptr){
                    _list *prnt = _ptr -> _prnt;
                    while(prnt!=nullptr && prnt -> _ft == prnt -> __prnt -> _end) {
                        _ptr = prnt -> __prnt -> _end -> _st;
                        prnt = prnt -> __prnt -> _prnt;
                    }
                    if(prnt != nullptr){
                        _ptr = (prnt -> _ft -> _st);
                    }
                    return *this;
                }
                else{
                    _ptr = _ptr -> _end -> _st;
                    return *this;
                }
                this -> _ptr = nullptr;
                return *this;
            }

            iterator operator++(int){
                // dbs(2);
                auto tmp = *this;
                ++*this;
                return tmp;
            }

            iterator operator--(){
                // dbs(3<<" "<<(_ptr->_dt)<<" "<<(_ptr -> _prnt == nullptr));
                if(_ptr -> _prnt == nullptr){ 
                    // dbs(22222);
                    _ptr -> printData();
                    // dbs(22222);
                    _ptr = nullptr;
                    return *this;
                }
                else{
                    _list *prnt = _ptr -> _prnt;
                    if(prnt -> _rr == nullptr){
                        _ptr = prnt -> __prnt;
                        return *this;
                    }
                    else{
                        prnt = prnt -> _rr;
                        while(prnt -> _st -> _end -> _rr != nullptr){
                            prnt = prnt -> _st -> _end -> _rr;
                        }
                        _ptr = prnt -> _st;
                        return *this;
                    }
                }
                _ptr = nullptr;
                return *this;
            }
            iterator operator--(int){
                auto tmp = *this;
                --*this;
                return tmp;
            }

            iterator operator+(unsigned int inc){
                // dbs(4);
                ++c;
                if(inc == 0) return *this;
                if(inc == 1) {
                    auto tmp = *this;
                    ++tmp;
                    return tmp;
                }
                if(_ptr -> _sz > inc){
                    auto tt = _ptr -> _head;
                    unsigned int itr = 0;
                    while(tt!=nullptr)
                    {
                        if(inc <= tt -> _st -> _sz){
                            return tt -> _st -> begin() + (inc - 1);
                        }
                        //std::cout<<"  inc = "<<inc<<"  sz = "<< tt -> _st -> _sz<<" \n";
                        //// dbs(inc);
                        inc = inc - tt -> _st -> _sz;
                        tt = tt -> _ft;
                        
                        ++itr;
                    }
                    // // dbs(3);std::cout<<"blah\n";
                    // // dbs(inc);
                    return iterator(nullptr);
                }
                inc = inc - (_ptr -> _sz - 1);
                if(_ptr -> _prnt != nullptr){
                    if(_ptr -> _prnt -> _ft != _ptr -> _prnt -> __prnt -> _end){
                        return _ptr -> _prnt -> _ft -> _st -> begin() + (inc-1); 
                    }
                    _ptr = _ptr -> _prnt -> __prnt;
                    return _ptr -> begin() + (_ptr -> _sz + inc-1);
                }

                if(inc == 1)
                    return _ptr -> end();
                return iterator(nullptr);
            }


            iterator operator-(unsigned int dec){
                // dbs(5);
                if(dec == 0) return *this;
                if(dec == 1) {
                    auto tmp = *this;
                    --tmp;
                    return tmp;
                }
                if(_ptr->_prnt != nullptr){
                    if(_ptr->_prnt -> _rr !=nullptr){
                        _list *tt = _ptr->_prnt -> _rr;
                        if(dec <= tt -> _st ->_sz){
                            dec = tt -> _st ->_sz - dec;

                            return tt -> _st -> begin() + dec;
                        }
                        dec = dec -  tt -> _st ->_sz;

                        return tt -> _st -> begin() - dec;
                    }
                    return _ptr->_prnt->__prnt->begin() - (dec - 1);
                }
                return iterator(nullptr);
            }


            
            ptrdiff_t operator-(const iterator &x){
                // dbs(6);
                if(x._ptr == _ptr) return 0;
                LTree<T> *tmp = _ptr;
                ptrdiff_t n = 0;
                while(tmp -> _prnt != nullptr)
                {
                    _list *tt = tmp -> _prnt -> _rr; 
                    while(tt != nullptr){
                        n = n + tt -> _st -> _sz;
                        tt = tt -> _rr;
                    }
                    tmp = tmp -> _prnt -> __prnt;
                    ++n;
                }
                tmp = x._ptr;
                while(tmp -> _prnt != nullptr)
                {
                    _list *tt = tmp -> _prnt -> _rr; 
                    while(tt != nullptr){
                        n = n - tt -> _st -> _sz;
                        tt = tt -> _rr;
                    }
                    tmp = tmp -> _prnt -> __prnt;
                    --n;
                }
                return n;
            }

            bool operator<(const iterator &x){
                // dbs(7);
                if(x._ptr == nullptr || _ptr == nullptr) return false;
                if(x._ptr -> _prnt == nullptr) return false;
                return this->operator-(x) < 0;
            }

            bool operator<=(const iterator &x){
                // dbs(8);
                if(x._ptr == nullptr || _ptr == nullptr) return false;
                if(_ptr -> _prnt == nullptr) return true;
                return this -> operator<(x) || this -> operator==(x);
            }

            bool operator>(const iterator &x){
                // dbs(9);
                if(x._ptr == nullptr || _ptr == nullptr) return false;
                if(_ptr -> _prnt == nullptr) return false;
                return !this->operator<=(x);

            }

            bool operator>=(const iterator &x){
                // dbs(10);
                if(x._ptr == nullptr || _ptr == nullptr) return false;
                if(x._ptr -> _prnt == nullptr) return true;
                return this -> operator>(x) || this -> operator==(x);
            }

            T &operator*(){
                // dbs(13 <<" "<<(_ptr->_dt));
                return _ptr->_dt;
            }

            bool operator==(const iterator &x){
                // dbs(11 << (_ptr -> _dt) <<" "<< (x._ptr -> _dt)<<" "<< (x._ptr == _ptr));
                if(x._ptr == nullptr || _ptr == nullptr) return false;
                return x._ptr == _ptr;
            }

            bool operator!=(const iterator &x){
                // dbs(12);
                return !this->operator==(x);
            }

            LTree<T> *_current_ltree(){
                return _ptr;
            }
        };


        iterator begin(){
            return iterator(this);
        }
        iterator end(){
            return iterator(_end->_st);
        }


        T &operator[](unsigned int idx){
            if(idx == 0)
                return _dt;
            _list *tt = _head;
            _list *tp = tt;
            --idx;
            int itr = 0;
            while(tt != _end){
                if(idx < tt -> _st -> _sz){
                    return tt -> _st -> operator[](idx);
                }
                idx = idx - tt -> _st -> _sz;
                ++itr;
                tt = tt -> _ft;
            }
            
            return _errordt;
        }

        T back(){
            return *(end() - 1);
        }


        void pop(){

        }

        void insert(const iterator &x, const T &k){
            LTree<T> *tmp = x.__current_ltree();
            _list *tt = new _list(new LTree<T>(1, tmp->_dt), tmp);
            tmp->_dt = k;
            tt -> _ft = tmp -> _head;
            tmp -> _head = tt;
            LTree<T> *tmp2 = tmp;
            while(tmp2 -> _prnt != nullptr){
                ++tmp2 -> _sz;
                tmp2 = tmp2 -> _prnt -> __prnt;
            }
            ++tmp2 -> _sz;
            if(tmp -> _prnt != nullptr){
                if(tmp -> _prnt -> __prnt -> _prnt == nullptr && tmp -> _prnt -> _ft == tmp -> _prnt -> __prnt -> _end){
                    LTree<T> * lt = tmp -> _prnt -> __prnt; 
                    if(tmp -> _sz == tmp -> _mxsz){
                        stabilize(lt);
                    }
                    else if(tmp -> _sz > tmp -> _mxsz){
                        T dt = tmp -> back();
                        tmp -> pop();
                        lt -> push_back(dt);        
                    }
                }
                else
                {
                    T dt = tmp -> back();
                    tmp -> pop();
                    if(tmp -> _prnt -> _ft != tmp -> _end){
                        insert(tmp -> _prnt -> _ft -> _st, dt);
                    }
                    else{
                        ++x;
                        insert(x, dt);   
                    }
                }
            }
            tt = _head -> _ft;
            while(tt != tmp -> _end && tt -> _ft != tmp -> _end){
                if(tt -> _st -> _sz == tt -> _ft -> _st -> _sz){
                    _list *mrg = tt -> _st -> _end -> _rr;
                    tt -> _ft -> _rr = mrg;
                    if(tt -> _st -> _sz == 1){
                        tt -> _st -> _head = tt -> _ft;
                        tt -> _ft = tt -> _ft -> _ft;
                        tt -> _st -> _head -> _ft = tt -> _st -> _end;
                        tt -> _ft -> _rr = tt;
                    }
                    else{
                        _list *tp = tt -> _ft -> _ft;
                        tt -> _ft -> _ft = mrg -> _ft;
                        mrg -> _ft = tt -> _ft;
                        tp -> _rr = tt;
                        tt -> _ft = tp;
                    }
                }
            }
        }




        void printData(){
            //for(int i = 0 ; i < c; ++i) std::cout<<" ";
            std::cout<<_dt<<" ";
            _list * tt = _head;
            while(tt != tt -> __prnt -> _end){
                tt->_st->printData();
                tt = tt->_ft;
            }
        }

        size_t size(){
            return _sz;
        }
    };
}



