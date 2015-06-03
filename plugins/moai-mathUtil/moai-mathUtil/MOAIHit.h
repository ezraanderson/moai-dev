#ifndef ZLHIT_H
#define	ZLHIT_H

template < typename TYPE >
class ZLMetaHit {
public:
	TYPE	mX;
	TYPE	mY;
	TYPE	mDistance;
	//----------------------------------------------------------------//
	TYPE SetLength ( TYPE length ) {
		TYPE scale;
		scale = this->Length () / length;

		this->mX = this->mX / scale;
		this->mY = this->mY / scale;
		this->mDistance = this->mDistance / scale;

		return length;
	}
	//----------------------------------------------------------------//
	TYPE GetComp ( const u8 idx ) const {
		switch ( idx ) {			
			case 0:
				return this->mX;			
			case 1:
				return this->mY;			
			default:
				return this->mDistance;
		}
	}
	//----------------------------------------------------------------//
	void Init ( TYPE x, TYPE y, TYPE distance ) {
		mX = x;
		mY = y;
		mDistance = distance;
	}
	//----------------------------------------------------------------//
	ZLMetaHit () {
	}
	//----------------------------------------------------------------//
	ZLMetaHit ( TYPE x, TYPE y, TYPE distance ) :
		mX ( x ),
		mY ( y ),
		mDistance ( distance ) {
	}

	//----------------------------------------------------------------//
	~ZLMetaHit () {
	}
};
typedef ZLMetaHit < float > ZLHit;
#endif
