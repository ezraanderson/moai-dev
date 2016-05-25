for i = 1, #mSprite do


	mSprite[i]['color'][1]	= math.random(355)/255
	mSprite[i]['color'][2]	= math.random(355)/255
	mSprite[i]['color'][3]	= math.random(355)/255
	mSprite[i]['color'][4]	= math.random(355)/255

	mSprite[i]:setColor(unpack( mSprite[i]['color']	))

end

