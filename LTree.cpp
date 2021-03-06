#include <bits/stdc++.h>


#define dbs(i) std::cout<<"lol"<<i<<"\n"


namespace ksb{
    // int c = 0;
    // int cc = 0;
    // int dd = 0;
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
            _list(LTree<T> *st = nullptr,  LTree<T> *prnt=nullptr, _list *ft=nullptr, _list *rr=nullptr): _st(st), _ft(ft), _rr(rr), __prnt(prnt){};
            
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
            _end = new _list(nullptr, this);
            _head = _end;
            _prnt = nullptr;
            _mxsz = n+1;
            if(n > 0)
            {
                // initialising _end and _head
                --n;
                _list *tt = nullptr;
                _list *pr = nullptr;
                
                _end = new _list(new LTree<T>(0, dt), this);
                _end -> _st -> _prnt = _end;
                _head = _end;
                

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
                    pr -> _st -> _end -> _st = tt -> _st;
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

        

        LTree(const LTree<T>& x){
            size_t n = x._sz;
            T dt = T();
            _sz = n;
            size_t it = 1;
            _dt = dt;
            _head = _end = nullptr;
            _prnt = nullptr;
            _mxsz = n+1;
            if(n > 0)
            {
                // initialising _end and _head
                --n;
                _list *tt = nullptr;
                _list *pr = nullptr;
                
                _end = new _list(new LTree<T>(0, dt), this);
                _end -> _st -> _prnt = _end;
                _head = _end;
                

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
                    pr -> _st -> _end -> _st = tt -> _st;
                    pr -> _ft -> _rr = tt;
                    pr -> _ft = tt;
                    pr = tt;
                    tt = tt -> _ft;
                    if(it >= n) n = 0;
                    else n = n - it;
                    it = it * 2;
                }
            }
            iterator a = begin();
            iterator b = x.begin();
            while(b != x.end()){
                *a = *b;
                ++a;
                ++b;
            }
        }

        LTree(LTree<T> &&x){
            _sz = x._sz;
            _head = x._head;
            _end = x._end;
            _mxsz = x._mxsz;
            _prnt = x._prnt;
            _dt = x._dt;
            x._sz = 0;
            x._dt = T();
            x._head = x._end = nullptr;
            x._mxsz = 1;

        }

        template<typename I, typename = std::_RequireInputIter<I>>
        LTree(I __first, I __last){
            size_t n = 0;
            T dt = T();
            _sz = n;
            _dt = dt;
            _head = _end = nullptr;
            _prnt = nullptr;
            while(__first != __last){
                push_back(*__first);
                ++__first;
            }
        }

        LTree(std::initializer_list<T> init){
            size_t n = 0;
            T dt = T();
            _sz = n;
            _dt = dt;
            _head = _end = nullptr;
            _prnt = nullptr;
            typename std::initializer_list<T>::iterator __first = init.begin();
            typename std::initializer_list<T>::iterator __last = init.end();
            while(__first != __last){
                push_back((*__first));
                ++__first;
            }
        }

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
                // dbs(" = "<< (_ptr->_dt)<<" "<<( x._ptr -> _dt));
                _ptr = x._ptr;
                x._ptr = nullptr;
                return *this;
            }

            iterator& operator=(const iterator& x){
                // dbs(" = "<< (_ptr->_dt)<<" "<<( x._ptr -> _dt));
                _ptr = x._ptr;
                return *this;
            }



            iterator operator++(){
                // dbs(" ++ "<< (_ptr->_dt)<<" ");
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
                // dbs(" ++1 "<< (_ptr->_dt));
                auto tmp = *this;
                ++*this;
                return tmp;
            }

            iterator operator--(){
                // dbs(" -- "<< (_ptr->_dt)<<" ");
                if(_ptr -> _prnt == nullptr){ 
                    // // dbs(22222);
                    //_ptr -> printData();
                    // // dbs(22222);
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
                // dbs(" +x "<< (_ptr->_dt)<<" "<<( inc));
                // ++c;
                if(inc == 0) return *this;
                if(inc == 1) {
                    iterator tmp = *this;
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
                        //// // dbs(inc);
                        inc = inc - tt -> _st -> _sz;
                        tt = tt -> _ft;
                        
                        ++itr;
                    }
                    // // // dbs(3);std::cout<<"blah\n";
                    // // // dbs(inc);
                    return iterator(nullptr);
                }
                LTree<T> *tmp = _ptr;
                inc = inc - (tmp -> _sz - 1);
                if(tmp -> _prnt != nullptr){
                    if(tmp -> _prnt -> _ft != tmp -> _prnt -> __prnt -> _end){
                        return tmp -> _prnt -> _ft -> _st -> begin() + (inc-1); 
                    }
                    tmp = tmp -> _prnt -> __prnt;
                    return tmp -> begin() + (tmp -> _sz + inc-1);
                }

                if(inc == 1)
                    return tmp-> end();
                return iterator(nullptr);
            }


            iterator operator-(unsigned int dec){
                // dbs(" -x "<< (_ptr->_dt)<<" "<<( dec));
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
                // dbs(" - "<< (_ptr->_dt)<<" "<<( x._ptr -> _dt)<<" "<<n);
                return n;
            }

            bool operator<(const iterator &x){
                // dbs(" < "<< (_ptr->_dt)<<" "<<( x._ptr -> _dt));
                if(x._ptr == nullptr || _ptr == nullptr) return false;
                if(x._ptr -> _prnt == nullptr) return false;
                return this->operator-(x) < 0;
            }

            bool operator<=(const iterator &x){
                // dbs(" <= "<< (_ptr->_dt)<<" "<<( x._ptr -> _dt));
                if(x._ptr == nullptr || _ptr == nullptr) return false;
                if(_ptr -> _prnt == nullptr) return true;
                return this -> operator<(x) || this -> operator==(x);
            }

            bool operator>(const iterator &x){
                // dbs(" > "<< (_ptr->_dt)<<" "<<( x._ptr -> _dt));
                if(x._ptr == nullptr || _ptr == nullptr) return false;
                if(_ptr -> _prnt == nullptr) return false;
                return !this->operator<=(x);

            }

            bool operator>=(const iterator &x){
                // dbs(" >= "<< (_ptr->_dt)<<" "<<( x._ptr -> _dt));
                if(x._ptr == nullptr || _ptr == nullptr) return false;
                if(x._ptr -> _prnt == nullptr) return true;
                return this -> operator>(x) || this -> operator==(x);
            }

            T &operator*(){
                // dbs(" * "<< (_ptr->_dt)<<" ");
                return _ptr->_dt;
            }

            bool operator==(const iterator &x){
                // dbs(" == "<< (_ptr->_dt)<<" "<<( x._ptr -> _dt));
                if(x._ptr == nullptr && _ptr == nullptr) return true;
                if(x._ptr == nullptr || _ptr == nullptr) return false;
                return x._ptr == _ptr;
            }

            bool operator!=(const iterator &x){
                // dbs(" != "<< (_ptr->_dt)<<" "<<( x._ptr -> _dt));
                return !this->operator==(x);
            }
            friend class LTree<T>;

        };


        iterator begin(){
            return iterator(this);
        }
        iterator end(){
            if(_end == nullptr) return iterator(nullptr);
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

        T front(){
            return *(begin());
        }

        
        void push_back(const T& k){
            _list *tt = _head;
            //dbs(0);
            ++_sz;
            if(_head == _end){
                //dbs(1);
                if(_prnt == nullptr){
                    //dbs(2);
                    if(_head == nullptr){

                        _sz = 1;
                        _dt = k;
                        _end = new _list(new LTree<T>(0, T()), this);
                        _end -> _st -> _prnt = _end;
                        _head = _end;
                        return;
                    }
                }
                size_t ssz = 1;
                _head = new _list(new LTree<T>(ssz, k), this);
                _head -> _st -> _prnt = _head;
                _head -> _st -> _mxsz = ssz;
                _head -> _rr = nullptr;
                _head -> _ft = _end;
                _end -> _rr = _head;
                return;
            }
            tt = _head;
            tt = _end -> _rr;
            if(tt->_st->_sz < tt -> _st -> _mxsz){
                tt -> _st -> push_back(k);
                return;
            }
            size_t ssz = 1;
            //dbs(" before "<<(tt -> _st -> _dt)<<"  "<<(tt -> _ft == _end) );
            
            _list *tmp= new _list(new LTree<T>(ssz, k), this);
            tmp -> _st -> _prnt = tmp;
            tmp -> _ft = tt -> _ft;
            tmp -> _rr = tt;
            tt -> _ft = tmp;
            tmp -> _ft -> _rr = tmp;
            //dbs(0);
            tmp -> _st -> _mxsz = (tt -> _st -> _mxsz) * 2;
            //dbs(0);
        }

        void pop(){
            // dbs(" popopop ");
            // --_sz;
            _list *tt = _head;
            if(_head == _end){
                if(_prnt == nullptr){
                    delete _head;
                    _head = _end = new _list(nullptr, this);
                    _dt = 0;
                    _sz = 0;
                    return;
                }
                LTree<T> *tmp = _prnt -> __prnt;
                if(tmp -> _head == _prnt){
                    // dbs(" pop "<<(tmp -> _head  ->_st->_dt)<<" "<<(tmp -> _dt));
                    delete tmp -> _head  -> _st;
                    delete tmp -> _head;
                    tmp -> _head = tmp -> _end;
                    tmp -> _head -> _ft = tmp -> _head -> _rr = nullptr; 
                    while(tmp->_prnt!=nullptr){
                        --(tmp->_sz);
                        tmp = tmp -> _prnt -> __prnt;
                    }
                    --(tmp->_sz);

                    //--(tmp -> _sz);
                    return;
                }
                tt = _prnt;
                // dbs(" pop "<<(tt->_st->_dt));
                delete tt -> _st;
                tt -> _ft -> _rr = tt -> _rr;
                tt -> _rr -> _ft = tt -> _ft;
                delete tt;
                while(tmp->_prnt!=nullptr){
                    --(tmp->_sz);
                    tmp = tmp -> _prnt -> __prnt;
                }
                --(tmp->_sz);
                return;
            }
            tt = _end -> _rr;
            
            // dbs(" pop "<<(tt->_st->_dt));
            tt -> _st -> pop();
        }


        void insert(unsigned int pos, const T &k){
            // dbs(0);
            if(pos == 0)
            {
                if(_prnt != nullptr){
                    T ele = k;
                    LTree<T> *tmp;
                    if(_sz == 1 && _prnt -> __prnt -> _prnt != nullptr){  
                        tmp = _prnt -> __prnt;  
                    }
                    else{
                        ele = _dt;
                        _dt = k;
                        tmp = this;
                    }
                    _list *newd = new _list(new LTree<T>(1, ele), tmp);
                    newd -> _st -> _prnt = newd;
                    // dbs(1);
                    newd -> _ft = tmp -> _head;
                    tmp -> _head-> _rr = newd;
                    tmp -> _head = newd;
                    LTree<T> *tmp2 = tmp;
                    while(tmp->_prnt!=nullptr){
                        ++(tmp->_sz);
                        tmp = tmp -> _prnt -> __prnt;
                    }
                    ++(tmp->_sz);
                    tmp = tmp2;
                    // dbs(2);
                    while (tmp -> _prnt -> _ft == tmp -> _prnt -> __prnt -> _end && tmp -> _prnt -> __prnt -> _prnt != nullptr) 
                        tmp = tmp -> _prnt -> __prnt;
                    if(tmp -> _prnt -> _ft == tmp -> _prnt -> __prnt -> _end && tmp -> _prnt -> __prnt -> _prnt == nullptr){
                        if(tmp -> _sz == tmp -> _mxsz ){
                            // dbs(" okay okay");
                            //tmp -> _prnt -> __prnt -> stabilize();
                            
                        }
                        else{
                            // dbs(" not okay");
                            ele = tmp ->  back();
                            tmp->pop();
                            //tmp -> _prnt -> __prnt -> stabilize();
                            tmp -> _prnt -> __prnt -> push_back(ele);
                        }
                        if(tmp2 -> _sz > 1){
                            newd = tmp2 -> _head;
                            while(newd -> _ft != tmp2 -> _end && newd -> _ft -> _ft != tmp2 -> _end){
                                size_t sz1 = newd -> _st -> _sz;
                                size_t sz2 = newd -> _ft -> _st -> _sz;
                                size_t sz3 = newd -> _ft -> _ft -> _st -> _sz;
                                if(sz1 == sz2 && sz2 == sz3){
                                    // dbs(" "<<(newd->_st->_dt)<<" "<<(newd->_ft->_st->_dt)<<" "<<(newd->_ft->_ft->_st->_dt));
                                    if(sz2 == 1){
                                        // dbs(" Fucked ");
                                        newd -> _ft -> _st -> _head = newd -> _ft -> _ft;
                                        newd -> _ft -> _ft = newd -> _ft -> _ft -> _ft;
                                        newd -> _ft -> _st -> _head -> _ft = newd -> _ft -> _st -> _end;
                                        newd -> _ft -> _st -> _end -> _rr = newd -> _ft -> _st -> _head;
                                        newd -> _ft -> _st -> _head -> _rr = nullptr;
                                        newd -> _ft -> _st -> _head -> __prnt = newd -> _ft -> _st;
                                        newd -> _ft -> _st -> _head -> _st -> _prnt = newd -> _ft -> _st -> _head;
                                        newd -> _ft -> _ft -> _rr = newd -> _ft ;
                                        newd -> _ft -> _st -> _sz = 2;
                                        newd -> _ft -> _st ->  _mxsz = 2;
                                        
                                    }
                                    else{
                                        _list *tmp3 = newd -> _ft -> _ft;
                                        newd -> _ft -> _ft = newd -> _ft -> _ft -> _ft;
                                        newd -> _ft -> _ft -> _rr = tmp3 -> _rr;
                                        newd -> _ft -> _st -> _end -> _rr -> _ft = tmp3;
                                        tmp3 -> _rr = newd -> _ft -> _st -> _end -> _rr;
                                        tmp3 -> _ft = newd -> _ft -> _st -> _end;
                                        tmp3 -> __prnt = newd -> _ft -> _st;
                                        newd -> _ft -> _st -> _end -> _rr = tmp3;
                                        newd -> _ft -> _st -> _sz = newd -> _ft -> _st -> _sz + tmp3 -> _st -> _sz;
                                        newd -> _ft -> _st -> _mxsz = newd -> _ft -> _st -> _mxsz*2;
                                    }
                                }
                                newd = newd -> _ft;
                            }
                        }
                        return;  
                    }
                    // dbs(3);
                    ele = tmp2 ->  back();
                    // dbs(" ele "<<ele<<" ");
                    tmp2 -> pop();
                    
                    tmp -> _prnt -> _ft -> _st -> insert(0, ele);
                    if(tmp2 -> _sz > 1){
                        newd = tmp2 -> _head;
                        while(newd -> _ft != tmp2 -> _end && newd -> _ft -> _ft != tmp2 -> _end){
                            size_t sz1 = newd -> _st -> _sz;
                            size_t sz2 = newd -> _ft -> _st -> _sz;
                            size_t sz3 = newd -> _ft -> _ft -> _st -> _sz;
                            if(sz1 == sz2 && sz2 == sz3){
                                // dbs(" "<<(newd->_st->_dt)<<" "<<(newd->_ft->_st->_dt)<<" "<<(newd->_ft->_ft->_st->_dt));
                                if(sz2 == 1){
                                    // dbs(" Fucked ");
                                    newd -> _ft -> _st -> _head = newd -> _ft -> _ft;
                                    newd -> _ft -> _ft = newd -> _ft -> _ft -> _ft;
                                    newd -> _ft -> _st -> _head -> _ft = newd -> _ft -> _st -> _end;
                                    newd -> _ft -> _st -> _end -> _rr = newd -> _ft -> _st -> _head;
                                    newd -> _ft -> _st -> _head -> _rr = nullptr;
                                    newd -> _ft -> _st -> _head -> __prnt = newd -> _ft -> _st;
                                    newd -> _ft -> _st -> _head -> _st -> _prnt = newd -> _ft -> _st -> _head;
                                    newd -> _ft -> _ft -> _rr = newd -> _ft ;
                                    newd -> _ft -> _st -> _sz = 2;
                                    newd -> _ft -> _st ->  _mxsz = 2;
                                    
                                }
                                else{
                                    _list *tmp3 = newd -> _ft -> _ft;
                                    newd -> _ft -> _ft = newd -> _ft -> _ft -> _ft;
                                    newd -> _ft -> _ft -> _rr = tmp3 -> _rr;
                                    newd -> _ft -> _st -> _end -> _rr -> _ft = tmp3;
                                    tmp3 -> _rr = newd -> _ft -> _st -> _end -> _rr;
                                    tmp3 -> _ft = newd -> _ft -> _st -> _end;
                                    tmp3 -> __prnt = newd -> _ft -> _st;
                                    newd -> _ft -> _st -> _end -> _rr = tmp3;
                                    newd -> _ft -> _st -> _sz = newd -> _ft -> _st -> _sz + tmp3 -> _st -> _sz;
                                    newd -> _ft -> _st -> _mxsz = newd -> _ft -> _st -> _mxsz*2;
                                }
                            }
                            newd = newd -> _ft;
                        }
                    }
                }
                else{
                    if(_sz == 0) push_back(k);
                    else{
                        T ele = _dt;
                        _dt = k;
                        insert(1, ele);
                    }
                }
                return;
            }
            _list *tt = _head;
            _list *tp = tt;
            --pos;
            int itr = 0;
            while(tt != _end){
                if(pos < tt -> _st -> _sz){
                    return tt -> _st -> insert(pos, k);
                }
                pos = pos - tt -> _st -> _sz;
                ++itr;
                tt = tt -> _ft;
            }
            push_back(k);
        }

        void insert(iterator pos, const T& k){
            pos._ptr->insert(0,k);
        }


        ///////////////////////////////////////////// TEMPORARY IMPLEMENTATION /////////////////////////////////////////////

        void sort(){
            std::vector<T> v(_sz);
            iterator itr = begin();
            for(T &t :v){
                t = *itr;
                ++itr;
            }
            std::sort(v.begin(), v.end());
            itr = begin();
            for(T &t :v){
                *itr = t;
                ++itr;
            }
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


        ///////////////////////////////////////////// TEMPORARY IMPLEMENTATION /////////////////////////////////////////////

        void reverse(){
            std::list<T> l;
            iterator itr = begin();
            iterator e = end();
            while(itr != e){
                l.push_back(*itr);
                ++itr;
            }
            l.reverse();
            itr = begin();
            typename std::list<T>::iterator itr2 = l.begin();
            typename std::list<T>::iterator e2 = l.end();
            while(itr2 != e2){
                *itr = *itr2;
                ++itr;
                ++itr2;
            }
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        // void printData(){
        //     ++c;
        //     for(int i = 0 ; i < c; ++i) std::cout<<" ";
        //     std::cout<<_dt<<" "<<_sz<<"\n";
        //     _list * tt = _head;
        //     while(tt != tt -> __prnt -> _end){
        //         tt->_st->printData();
        //         tt = tt->_ft;
        //     }
        //     --c;
        // }

        size_t size(){
            return _sz;
        }


    };
}



