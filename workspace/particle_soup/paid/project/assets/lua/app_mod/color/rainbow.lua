local colorMap =
{
	{1,0,0,1},
	{0,1,0,1},
	{0,0,1,1},
	{1,0,1,1},
	{1,1,0,1},
	{0,1,1,1},
}

for i = 1, #mSprite do
	local random_number = math.random(#colorMap)
	mSprite[i]['color'][1]	= colorMap[random_number][1]
	mSprite[i]['color'][2]	= colorMap[random_number][2]
	mSprite[i]['color'][3]	= colorMap[random_number][3]
	mSprite[i]['color'][4]	= colorMap[random_number][4]
	mSprite[i]:setColor(unpack( mSprite[i]['color']	))

end



