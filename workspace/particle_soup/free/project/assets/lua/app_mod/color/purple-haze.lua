local tick = 0

for i = 1, #mSprite do


			tick = tick + 1



			if tick == 1 then

					mSprite[i]['color'][1]	= 1
					mSprite[i]['color'][2]	= 0
					mSprite[i]['color'][3]	= 1
					mSprite[i]['color'][4]	= 1

			else

					mSprite[i]['color'][1]	= 1
					mSprite[i]['color'][2]	= 1
					mSprite[i]['color'][3]	= 1
					mSprite[i]['color'][4]	= 1

					tick = 0
			end

mSprite[i]:setColor(unpack( mSprite[i]['color']	))

end
