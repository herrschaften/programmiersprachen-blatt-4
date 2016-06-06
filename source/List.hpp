# ifndef BUW_LIST_HPP
# define BUW_LIST_HPP
# include <cstddef>

// List . hpp
template <typename T>
struct List;

//  prev<-NODE->next mit value 
template <typename T >
struct ListNode{
	ListNode(): 
	m_value() , 
	m_prev(nullptr) , 
	m_next (nullptr) {}

	ListNode (T const& v , ListNode* prev , ListNode* next ): 
	m_value(v) , 
	m_prev (prev) , 
	m_next (next){}

	T m_value ;
	ListNode* m_prev ;
	ListNode* m_next ;
};

//----------------------------------------------------------------------
template <typename T>
struct ListIterator{

	typedef ListIterator<T> Self;

	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;
	typedef ptrdiff_t difference_type;
	typedef std::forward_iterator_tag iterator_category;

	friend class List <T>;

	//default iterator (leere liste)
	ListIterator() : m_node(nullptr) {}  

	//iterator läuft mit node bis eingegebenes n 
	ListIterator(ListNode <T>* n) : m_node(n) {}  

	//
	reference operator*() const{return(m_node->m_value);} 

	//
	pointer operator->() const{return &(m_node->m_value);} 

	//++a
	Self& operator++() {

		*this= next(); 
		return *this;
	} 

	//a++
	Self operator++(int) {

		Self tmp = *this;
		++(*this);
		return tmp;
	} 

	//gleich
	bool operator ==(const Self & x) const {return m_node == x.m_node;} 
 
	//nicht gleich
	bool operator != (const Self & x ) const {return m_node != x.m_node;}

	//
	Self next() const{

		if (m_node)
			return ListIterator(m_node-> m_next);
		else
			return ListIterator(nullptr);
	}

	Self prev() const{

		if (m_node)
			return ListIterator(m_node-> m_prev);
		else
			return ListIterator(nullptr);
	}
// not implemented yet
private:
	ListNode <T>* m_node = nullptr;
};

//---------------------------------------------------------------
template < typename T >
struct ListConstIterator{

	friend class List <T>;

public:
// not implemented yet


private:
	ListNode <T>* m_node = nullptr;
};

//----------------------------------------------------------------
template < typename T >
class List{

public:
	typedef T value_type;
	typedef T* pointer;
	typedef const T* const_pointer;
	typedef T& reference;
	typedef const T& const_reference;
	typedef ListIterator <T> iterator;
	typedef ListConstIterator <T> const_iterator;
	friend class ListIterator <T>;
	friend class ListConstIterator <T>;// not implemented yet

	List(): 
		m_size(0), 
		m_first(nullptr), 
		m_last(nullptr) 
		{}

	// copy konstruktor: List<int> l{l1} kopiert l1 in l
	List<T>(List<T> const& l): 
		m_size(0), 
		m_first(nullptr), 
		m_last(nullptr) 
		{
			for (auto it=l.begin(); it != l.end(); it++)
			{
				push_back(*it);
			}
		}

	//Move Construktor (&& move operator ?)
	List<T>(List<T> && l): 
		//werte aus list 
		m_size(l.m_size),
		m_first(l.m_first),
	  	m_last(l.m_last){

		l.m_size=0;
		l.m_first=nullptr;
		l.m_last=nullptr;
		
		}	
	
	
	~List(){clear();} 

	bool empty () const{

		return size() == 0;
	}

	std::size_t size () const{

		return m_size;
	}

	void push_front(T const&  v) {

		if(empty()){
			ListNode <T>* newleft= new ListNode<T> {v,  nullptr, nullptr};
			m_first=newleft;
			m_last=newleft;
		
		}
		else{

			ListNode <T>* newleft= new ListNode<T> {v,  nullptr, m_first};
			//prev von erstem wird zu newleft
			m_first->m_prev=newleft;
			//new left wird zu erstem 
			m_first=newleft;
			

		}
		m_size++;
	}

	void push_back(T const& v){

		if(empty()){
			//syntax neuer knoten: Listnode <T>* name= new Listnode <T> {wert, prev knoten, next knoten}
			ListNode <T>* newlast= new ListNode<T> {v,  nullptr, nullptr};
			m_first=newlast;
			m_last=newlast;

		}
	
		else{

			ListNode <T>* newlast= new ListNode<T> {v,  m_last, nullptr};
			//next von last wird neues last
			m_last->m_next=newlast;
			m_last=newlast;
		}
		m_size++;
	}

	void pop_front(){

		if(m_size>1){	
			auto x= m_first->m_next;
			delete m_first;
			x->m_prev=nullptr;
			m_first=x;
			m_size--;
		}
		else if(m_size==1){
			delete m_first;
			m_first=nullptr;
			m_last=nullptr;
			m_size--;
		}
	}	

	void pop_back(){

		if(m_size>1){

			auto x = m_last->m_prev;
			delete m_last;
			x->m_next=nullptr;
			m_last=x;
			m_size--;
		}
		else if(m_size==1){
			delete m_first;
			m_first=nullptr;
			m_last=nullptr;
			m_size--;


		}
	}

	T front(){

		return m_first->m_value;
	}

	T last(){

		return m_last->m_value;
	}

	void clear(){
		while(!(empty())){
			pop_back();
		}
	}

	iterator begin() const{

		return m_first;
	}

	iterator end() const{

		//letztes element zeigt auf nullptr like defaultconstruktor
		return ListIterator<T>();
	}

	//insert(zeiger, value)
	iterator insert(iterator it, T const & v ){

		//zeiger am anfang wird einfach davor geschoben mit push front
		if(it==begin()){
			push_front(v);
			return begin();
		}
		//zeiger am ende mit push back | begin=1 end=x 1|2|3|x  m_first=1 m_last=3
		else if(it==end()){
			push_back(v);
			return m_last;
		}
		else{

			ListNode <T>* newnode= new ListNode <T> {v, it.prev().m_node, it.m_node};
			
			//zeiger von el. vor node auf new node (next)
			it.prev().m_node->m_next=newnode;
			//zeiger von node auf new node (prev)
			it.m_node->m_prev=newnode;
			return newnode;
		}
	}
	
	void reverse(){

		//startet hinten geht nach vorne(next) bis nullptr erreicht
		for(auto x=m_last; x!=nullptr; x=x->m_next){

			//zeiger werden vertauscht
			std::swap(x->m_prev, x->m_next);

		}
		//start, endpunkt wird vertauscht
		std::swap(m_first, m_last);
	}


	

	

private:
	std::size_t m_size = 0;
	ListNode <T >* m_first = nullptr ;
	ListNode <T >* m_last = nullptr ;

};	

template <typename T>
bool operator==(List<T> const& xs, List<T> const& ys){

	//iterator auf beginn der Listen zählen mit ++ durch (später)
	ListIterator<T> itx = xs.begin(); 
	ListIterator<T> ity = ys.begin(); 

	//wird nur geändert zwei werte ungleich sonst bleibt es true
	bool op = true;
	

	//länge vergleichen
	if(xs.size() != ys.size()){ 

		op=false;
	}


	//jedes element vergleichen
	else{
		unsigned int grenze=0;
		//so lange elemente gleich und grenze kleiner liste weiter 
		while ((op==true)&(grenze<(xs.size()))){
			//abbruch wenn aktuellen elemente !=
			if(*itx != *ity){
				op = false;
			}
			else {
				//iterator weiter
				ity++;
				itx++; 
			}
				//grenze weiter
				grenze++;
		}
	}
	return op;
}

template <typename T>
bool operator!=(List<T> const& xs, List<T> const& ys){

	return !(xs==ys);
}

//dreht Liste um mit reverse
template <typename T> List <T> reverse(List <T> rev){

	rev.reverse();
	return rev;
}


//-------------------------------------------------------------------


#endif