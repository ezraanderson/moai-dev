//http://www.phailed.me/2011/02/polygonal-collision-detection/

#include "pch.h"
#include <moai-mathUtil/MOAIPolygon.h>
#include <moai-sim/MOAIDraw.h>

#include <vector>
#include "point.h"
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>



//LISTS
#include <map>
using namespace std;

//HEADER TO 
typedef struct {float x, y;} vec;
typedef struct {vec p0, dir;} ray;
typedef struct {vec p0, p1, dir;} seg;
typedef struct {int n; vec *vertices; seg *edges;} polygon; // Assumption: Simply connected => chain vertices together

//***************************************************************
vec v(float x, float y){
	vec a = {x, y};
	return a;
}
//***************************************************************
vec perp(vec v){
	vec b = {v.y, -v.x};
	return b;
}
//***************************************************************
vec normalize(vec v){
	float mag = sqrt(v.x*v.x + v.y*v.y);
	vec b = {v.x/mag, v.y/mag};
	return b;
}
//***************************************************************
seg segment(vec p0, vec p1){
	vec dir = {p1.x-p0.x, p1.y-p0.y};
	seg s = {p0, p1, dir};
	return s;
}
//***************************************************************
float dot(vec a, vec b){
	return a.x*b.x+a.y*b.y;
}
//***************************************************************
float* project(polygon a, vec axis){
	axis = normalize(axis);
	int i;
	float min = dot(a.vertices[0],axis); float max = min;
	for (i=0;i<a.n;i++){
		float proj = dot(a.vertices[i],axis);
		if (proj < min) min = proj; if (proj > max) max = proj;
	}
	float* arr = (float*)malloc(2*sizeof(float));
	arr[0] = min; arr[1] = max;
	return arr;
}
//***************************************************************
int contains(float n, float* range){
	float a = range[0], b = range[1];
	if (b<a) {a = b; b = range[0];}
	return (n >= a && n <= b);
}
//***************************************************************
int overlap(float* a_, float* b_){
	if (contains(a_[0],b_)) return 1;
	if (contains(a_[1],b_)) return 1;
	if (contains(b_[0],a_)) return 1;
	if (contains(b_[1],a_)) return 1;
	return 0;
}
//***************************************************************
int sat(polygon a, polygon b){
	int i;
	for (i=0;i<a.n;i++){
		vec axis = a.edges[i].dir;
		axis = perp(axis);
		float *a_ = project(a,axis);
		float *b_ = project(b,axis);
		if (!overlap(a_,b_)) return 0;
	}
	for (i=0;i<b.n;i++){
		vec axis = b.edges[i].dir;
		axis = perp(axis);
		float *a_ = project(a,axis); 
		float *b_ = project(b,axis);
		if (!overlap(a_,b_)){ 
		free(a_); free(b_);
		return 0;
		}
	}
	return 1;
}
//***************************************************************
//NEW POLYGON
polygon new_polygon(int nvertices, vec *vertices){
	seg *edges = (seg*)malloc(sizeof(seg)*(nvertices));
	int i;
	for (i = 0; i < nvertices-1; i++){
		vec dir = {vertices[i+1].x-vertices[i].x, vertices[i+1].y-vertices[i].y};
		seg cur = {vertices[i], vertices[i+1], dir};
		edges[i] = cur;
	}
	//BUILD THE LAST LINE FROM END TO START
	vec dir = {vertices[0].x-vertices[nvertices-1].x, vertices[0].y-vertices[nvertices-1].y};
	seg cur = {vertices[nvertices-1], vertices[0], dir};
	edges[nvertices-1] = cur;
	polygon shape = {nvertices, vertices, edges};
	return shape;
}
//***************************************************************
//READ IN FROM LUA
polygon Polygon(int nvertices, ...){
	va_list args;
	va_start(args, nvertices);
	vec *vertices = (vec*)malloc(sizeof(vec)*nvertices);
	int i;
	for (i = 0; i < nvertices; i++){

		vertices[i] = va_arg(args, vec);
		//printf("%d \n",va_arg(args, vec));
	}
	va_end(args);
	return new_polygon(nvertices, vertices);
}


vector<mPoint> points_a;
vector<mPoint> points_b;
//*******************************************************************************
int MOAIPolygon::_AABB ( lua_State* L ) {
MOAI_LUA_SETUP ( MOAIPolygon, "U" )

//polygon a = Polygon(4, v(0,0),v(0,5),v(5,4),v(3,0));  
//polygon b = Polygon(4, v(4,4),v(4,6),v(6,6),v(6,4));
//printf("%d\n", sat(a,b)); // 1: true

//
//		//POINTS
//		float px =  state.GetValue < float >( 2, 0 );
//		float py =  state.GetValue < float >( 3, 0 );
//
//		int x =0;
//		int y =0;	
//
////***************************************************************************
//			
//		u32 counter_a = 0;	
//		byte high_a=0;
//		lua_pushnil ( L );
//		while ( lua_next ( L, 2 ) != 0 ) {
//			if ( counter_a % 2 == 0 ) {
//				x = state.GetValue < float >( -1, 0 );		
//			} else {
//				y = state.GetValue < float >( -1, 0 );
//				++high_a;
//				points_a.push_back(mPoint(x,y));	
//				//printf("%f %f \n",x,y);
//			}	
//			++counter_a;
//			lua_pop ( L, 1 );
//		}
//
////***************************************************************************
//			
//		u32 counter_b = 0;	
//		byte high_b=0;
//		lua_pushnil ( L );
//		while ( lua_next ( L, 3 ) != 0 ) {
//			if ( counter_b % 2 == 0 ) {
//				x = state.GetValue < float >( -1, 0 );		
//			} else {
//				y = state.GetValue < float >( -1, 0 );		
//				++high_b;
//				points_b.push_back(mPoint(x,y));	
//				//printf("%f %f \n",x,y);
//			}	
//			++counter_b;
//			lua_pop ( L, 1 );
//		}
//


//***************************************************************************

		//polygon a = Polygon(high_a, v(points_a[0]._x,points_a[0]._y),v(points_a[1]._x,points_a[1]._y),v(points_a[2]._x,points_a[2]._y),v(points_a[3]._x,points_a[3]._y));  
	    //polygon b = Polygon(high_b, v(points_b[0]._x,points_b[0]._y),v(points_b[1]._x,points_b[1]._y),v(points_b[2]._x,points_b[2]._y),v(points_b[3]._x,points_b[3]._y));  
		//printf("%d\n", sat(a,b)); // 1: true

		points_a.clear();//	???
		points_b.clear();//	???

		 //std::free(points_a);
		 //std::free(points_b);
	//lua_pushboolean ( state,  sat(a,b));
 
	lua_pushboolean ( state,  true);
return 1;
}




//----------------------------------------------------------------//
MOAIPolygon::MOAIPolygon () 
{
	RTTI_BEGIN
		RTTI_EXTEND ( MOAILuaObject )
		RTTI_END
}

//----------------------------------------------------------------//
MOAIPolygon::~MOAIPolygon () {

	//if (this->mQueryList) {
	//	delete ( this->mQueryList );
	//};
}

//----------------------------------------------------------------//
void MOAIPolygon::RegisterLuaClass ( MOAILuaState& state ) {
	//luaL_Reg regTable [] = {
	//	{ NULL, NULL }
	//};
	//MOAILight::RegisterLuaClass ( state );
//	luaL_register ( state, 0, regTable );
}


//----------------------------------------------------------------//
void MOAIPolygon::RegisterLuaFuncs ( MOAILuaState& state ) {
	// here are the instance methods:
	luaL_Reg regTable [] = {

		{ "AABB",	  _AABB },
		
		{ NULL, NULL }
	};
	luaL_register ( state, 0, regTable );
	//state.SetField ( -1, "TRIANGLE",			( u32 )mTriangle);
	//state.SetField ( -1, "CIRCLE"  ,			( u32 )mCircle);


}
























 class key_comparer {
   public:
     bool operator() (const string* e1, const string* e2) 
     {
         return e1 < e2; // strict weak ordering required
     }
 };


 //*******************************************************************************
 int binarySearch(std::map <int, int> mymap,int size, int key){
	 
	 int start=1, end=size; int mid=(start+end)/2;
	 int cnt = 0;
	 int cache_last = 0;
  while(start<=end&&mymap[mid]!=key){
  //printf("  + * cnt %d cut %d %d \n",cnt,mid,mymap[mid]);
	  cnt = cnt + 1;
	 // int a = mymap[mid]->
	  //int(mymap[mid]->second);	 
	   //if (mymap[mid]== 0) {
		//}else

	    if(mymap[mid]<key){

          start=mid+1;
		  printf("  + * cnt %d cut %d %d \n",cnt,mid,mymap[mid]);

			//THE LAST LEFT SIDE : SHOLD BE POINTER
		  	//if (mymap[mid] != 0) {
			//	cache_last = mymap[mid];
			//};

      } else {
		   printf("  - * cnt %d cut %d %d \n",cnt,mid,mymap[mid]);
          end=mid-1;
      }
       mid=(start+end)/2;



     }// While Loop End

 if(mymap[mid]==key) {
    return mid; //Returnig to main
 }else {
	 return mid;//Returnig to main
 };

 //return cache_last;


  // cout<<"\n\n\n";
}// binarySearch Function Ends Here

 

////printf("%d\n", sat(a,b)); // 1: true
//DataArray<id> customerRecords[2];

//DataArray<DataID> data;
//
//	data.TryToGet(1);

//id = arrayCounterIncrementedOnAlloc << 16 | itemArrayIndex;
//DataArray<id> * data = new DataArray<id>[3];




	//DataArray

//DataArray &DataArra =  DataArray.Alloc();
//DataArray joe = { 1, 32, 60000.0 };
//id a = 1;

//DataArray<id>* me = new DataArray<id>();  

//me->Alloc();

//DataArray<id> *foo2 = DataArray<id>->TryToGet(1);

//DataArray<id> &Data = DataArray.Alloc();

//data.Alloc();

//DataArray &DataArray = DataArray.Alloc();

//DataID fooID = foos.GetID();
//foos.Free(foo);
//Foo *foo2 = foos.TryToGet(fooID);
//if (foo2 == NULL) print('foo was deleted');

//STORE THIS STUFF IN A LIST
//FIND THE CENTER OF THE POLYGON
//MAKE A CIRCLE AROUND THE POLYGON
//DETERMINE IF STATIC
//polygon a = Polygon(4, v(0,0),v(0,3),v(3,3),v(3,0));
//polygon b = Polygon(4, v(4,4),v(4,6),v(6,6),v(6,4));
//printf("DO_COLLID: %d\n", sat(a,b)); // 0 : false
//
////polygon a = Polygon(4, v(0,0),v(0,5),v(5,4),v(3,0));  
////polygon b = Polygon(4, v(4,4),v(4,6),v(6,6),v(6,4));
////printf("%d\n", sat(a,b)); // 1: true
//
//std::map <int, int> mymap;

	//int i;
	//for (i = 0; i < 100000-1; i++){
	//	mymap[i]=i;
	//};

//mymap[1]=1;
//mymap[2]=3;
//mymap[3]=5;
//mymap[4]=7;
//mymap[5]=10;
////mymap[6]=6;
////mymap[7]=7;
////mymap[8]=8;
////mymap[9]=9;
////mymap[10]=10;
//
//
////int a = mymap[1]->;
//
//// std::cout << "a => " << mymap.find(6)->second << '\n';
//
//int c = mymap.size();
//int r = binarySearch(mymap,c,11);
//
// printf("return :: %d %d %d \n",c,r,mymap[r]);

//mymap.find(5.5);

//stdut << secoLEFT SIDE THEN MOVE FORWARD

//for (std::map<int, int>::iterator i = mymap.begin(); i != mymap.end(); i++)
//{
//    cout << i->second << "\n";
//}



//	map <string, int> m;
//
//    m["5"] = 2;
//	m["1"] = 1;
//	m["44"] = 4;
//  	m["33"] = 3;
//
//
//
//assert(m.size() > 1);
//int i = 0;
//for (std::map<T>::const_iterator i = m.begin(); i != m.end(); ++i) {
//    std::map<T>::const_iterator j = i + 1;
//    while ( j != m.end() ) {
//        assert(*i < *j);
//        ++j;
//    }
//}



//auto cmp = [](std::pair<K,V> const & a, std::pair<K,V> const & b) 
//{ 
//     return a.second != b.second?  a.second < b.second : a.first < b.first;
//};
//std::sort(m.begin(), m.end(), cmp);


	// std::stable_sort(m.begin(), m.end(),key_comparer);

	//m.sort

	//std::stable_sort(m.begin(), m.end(), key_comparer);
	//std::stable_sort(m.begin(), m.end());


// Assuming that hm is an instance of hash_map:
//for (auto it = m.begin(); it != m.end(); ++it) // for each item in the hash map:
//{
//	  cout << m[it->first] << endl;
//    // it->first is current key
//    // ... you can push_back it to a vector<Key> or do whatever you want
//}


  //std::cout << "elements in mymap:" << '\n';
  //std::cout << "5 => " << m.find("5")->first << '\n';
  //std::cout << "1 => " << m.find("1")->second << '\n';
  //std::cout << "44 => " << m.find("44")->second << '\n';

//m.find("44");



//hash_map<string, void *> hashMap;
//vector<string> keys;
//keys.reserve(hashMap.size());
//
//for (hash_map<string, void *>::iterator iter = hashMap.begin(); 
//                                        iter != hashMap.end(); 
//                                        ++iter)
//{
//    keys.push_back(iter->first);
//}


//printf("Shit \n");





//typedef int id;
//typedef SomeStruct* pSomeStruct;
// typedef int* id;
// 
//template <class T>
//struct DataArray
//{
//  void Init(int count); // allocs items (max 64k), then Clear()
//  void Dispose();       // frees items
//  void Clear();         // resets data members, (runs destructors* on outstanding items, *optional)
//
//  T &Alloc();           // alloc (memclear* and/or construct*, *optional) an item from freeList or items[maxUsed++], sets id to (nextKey++ << 16) | index
//  void Free(T &);       // puts entry on free list (uses id to store next)
//
//  int GetID(T &);       // accessor to the id part if Item
//
//  T &Get(id);            // return item[id & 0xFFFF]; 
//  T *TryToGet(id);      // validates id, then returns item, returns null if invalid.  for cases like AI references and others where 'the thing might have been deleted out from under me'
//
//  bool Next(T *&);      // return next item where id & 0xFFFF0000 != 0 (ie items not on free list)
//
//  struct Item {
//    T item;
//    int id;             // (key << 16 | index) for alloced entries, (0 | nextFreeIndex) for free list entries
//  };
//
//  Item *items;
//  int maxSize;          // total size
//  int maxUsed;          // highest index ever alloced
//  int count;            // num alloced items
//  int nextKey;          // [1..2^16] (don't let == 0)
//  int freeHead;         // index of first free entry
//};

// typedef int DataID;
//
//template <class T>
//struct DataArray
//{
//  void Init(int count);
//  void Dispose();      
//  void FreeAll();
//
//  T &Alloc();
//  void Free(T &);
//
//  DataID GetID(T &);
//
//  T &Get(DataID);
//  T *TryToGet(DataID);
//
//  bool Next(T *&);
//
//  struct DataArrayItem
//  {
//     T item;
//     DataID id;
//  };
//};
