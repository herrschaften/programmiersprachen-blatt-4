#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include <cmath>
#include "List.hpp"


TEST_CASE ("diesdas","[1]"){

	List<int> l;

	REQUIRE(l.empty());

	REQUIRE(l.size()==0);

	


}

TEST_CASE ("push it","[2]"){

	List < int > list ;

	list.push_front (42);

	REQUIRE(42 == list.front());

	list.push_front (4);

	REQUIRE(4 == list.front());	
	REQUIRE(list.size()==2);

}


TEST_CASE ("push back","[2]"){

	List<int> list;

	list.push_back(3);

	REQUIRE(3 == list.last());

	list.push_back(2);

	REQUIRE(2 == list.last());
}


TEST_CASE ("pop it","[2]"){

	List<int> list;

	list.push_front(4);
	
	
	list.pop_front();
	REQUIRE(list.empty());

	list.push_front(3);
	REQUIRE(list.size()==1);

	list.push_front(3);
	REQUIRE(list.size()==2);

	REQUIRE(list.front()==3);

	list.push_back(5);
	REQUIRE(list.last()==5);

	list.pop_front();
	REQUIRE(list.size()==2);

	list.pop_back();
	REQUIRE(list.size()==1);

}

TEST_CASE ("pop back","[2]"){

	List<int> list;

	list.push_front(3);

	list.pop_back();
	REQUIRE(list.empty());

	list.push_back(4);
	list.push_back(2);

	list.pop_back();

	REQUIRE(list.last()==4);
}

TEST_CASE("cleardiss" "[3]"){
	List<int> l;

	l.push_back(2);
	l.push_back(3);
	l.push_back(4);
	l.clear();

	REQUIRE(l.empty());
}

TEST_CASE("iteration" "[4]"){

	List<int> l;
	l.push_back(1);
	auto i=l.begin();
	REQUIRE(*i==1);
	//REQUIRE(ListIterator()==nullptr);


//TESTS ÜBERARBEITEN
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!	

	int a = 3;
	int b = a++;
	REQUIRE(b==3);
	REQUIRE(a==4);

	int c = ++a;
	REQUIRE(c==5);
	REQUIRE(a==5);

	l.push_back(2);
	l.push_back(3);
	l.push_back(4);



	int Summe = 0;

	for(int i : l){

		Summe+= i;

	}

	REQUIRE(Summe==10);


}



TEST_CASE ( " should be an empty range after default construction " ,"[5]" ){

	List <int> list ;
	auto b =list.begin();
	auto e =list.end();
	REQUIRE (b == e);

}

TEST_CASE ( " provide acces to the first element with begin " , "[5]" ){

	List<int> list ;
	list.push_front(42);
	REQUIRE(42 == *list.begin());

}

TEST_CASE("gleichungleich" "[6]"){


		List<int>listx ;
		List<int>listy ;
		List<int>listz ;
		for (int i=0; i<10; i++)
		{ 
			listz.push_back(i);
				
		}

		//gleich leere liste
		REQUIRE(listx==listy);
		

		//x und y mit 1 bis 10 füllen
		for (int i=0; i<10; i++)
		{ 
			listx.push_back(i);
			listy.push_back(i);
			REQUIRE(listx==listy);		
		}

		REQUIRE(listx == listy);
		REQUIRE(listz == listy);
		//UNgleichheit:
		listy.push_back(1);
		REQUIRE((listx!=listy)); 
		listx.push_back(2);
		REQUIRE((listx!=listy)); 

		listx.pop_back();
		listy.pop_back();
		listy.pop_back();
		listy.push_back(1);
		REQUIRE((listx!=listy)); 
		listy.clear();
		listx.clear();

		for (int i=1; i<10; i++)
		{ 
			listx.push_back(i);
			listy.push_back(2*i);
			REQUIRE(listx!=listy);		
		}			
}



TEST_CASE ( " copy constructor" , " [7] " )
{
List < int > list ;
list . push_front (1);
list . push_front (2);
list . push_front (3);
list . push_front (4);
List < int > list2 { list };
REQUIRE ( list == list2 );

//test ob wirklich verschiedene listen
list.pop_front();
REQUIRE(list2.front()==4);
}


TEST_CASE("insert", "[8]"){


	List<int> l;
	List<int> l1;

	auto it=l.begin();
	
	l.insert(it, 2);

	REQUIRE(l.front()==2);

	for(int i=0; i<6; i++){
		l1.push_back(i);

	}

	auto dis=l1.begin();


	l1.insert(dis, 9);


	for(auto i: l1){
		//l1.push_back(i);
		std::cout<< i <<std::endl;
	}

	REQUIRE(l1.front()==9);
	REQUIRE(l1.last()==5);
}


TEST_CASE ("reverse", "[9]"){

	List<int> l;

	for(int i=1; i<6; i++){

		l.push_back(i);
	}

	l.reverse();
	
	REQUIRE(l.front()==5);
	REQUIRE(l.last()==1);


}	

TEST_CASE ("move constructor", "[12]"){

	List < int > list ;
	list.push_front (1);
	list.push_front (2);
	list.push_front (3);
	list.push_front (4);
	List<int>list2(std::move(list));
	REQUIRE (0==list.size());
	REQUIRE (list.empty());
	REQUIRE (4==list2.size());

}


TEST_CASE("liste in vek", "[10]") {
  	List<int> l;
	for(int i=1; i<6; i++){l.push_back(i);}


  std::vector<unsigned int> vek(l.size());
  std::copy(l.begin(), l.end(), std::begin(vek));

  REQUIRE(1 == vek[0]);
  REQUIRE(2 == vek[1]);
  REQUIRE(3 == vek[2]);
  REQUIRE(4 == vek[3]);
  REQUIRE(5 == vek[4]);
}





int main(int argc, char * argv[]) {

  return Catch::Session().run(argc, argv);



}


