#ifndef POINT_GUARD
#define POINT_GUARD
class mPoint{
    public:
		float _x;
		float _y;
		float _mag;
		int   _tag;
		mPoint(float x, float y);
		~mPoint();
		void show();
		float x();
		float y();
		void x(float x);
		void y(float y);  
};
#endif