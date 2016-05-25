


--RED,GREEN,BLUE,ALPHA

for i = 1, #mSprite do	



		mSprite[i]['color'][1]	= 1
		mSprite[i]['color'][2]	= 1
		mSprite[i]['color'][3]	= 1
		mSprite[i]['color'][4]	= 1

	

	mSprite[i]:setColor(unpack( mSprite[i]['color']	))

end
