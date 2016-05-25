local tick = 0


--RED,GREEN,BLUE,ALPHA

for i = 1, #mSprite do

	tick = tick + 1

	if tick == 1 then

			mSprite[i]['color'][1]	= 1.0 	--RED
			mSprite[i]['color'][2]	= 0.5 --GREEN
			mSprite[i]['color'][3]	= 0.0 --BLUE
			mSprite[i]['color'][4]	= 1.0 --ALPHA

	elseif tick == 2 then

			mSprite[i]['color'][1]	= 1 --RED
			mSprite[i]['color'][2]	= 0 --GREEN
			mSprite[i]['color'][3]	= 0 --BLUE
			mSprite[i]['color'][4]	= 1 --ALPHA

	elseif tick == 3 then

			mSprite[i]['color'][1]	= 1 --RED
			mSprite[i]['color'][2]	= 0 --GREEN
			mSprite[i]['color'][3]	= 0.5 --BLUE
			mSprite[i]['color'][4]	= 1 --ALPHA

			tick = 0
	end

	mSprite[i]:setColor(unpack( mSprite[i]['color']	))

end
