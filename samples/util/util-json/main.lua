----------------------------------------------------------------
-- Copyright (c) 2010-2011 Zipline Games, Inc. 
-- All Rights Reserved. 
-- http://getmoai.com
----------------------------------------------------------------

object = {
	foo = "str1",
	bar = 3,
	baz = 123.456,
	fee = {
		a = 1,
		b = 2,
		c = 3,
	},
	fie = {
		4,
		5,
		6,
	},
}



str = MOAIJsonParser.encode ( object,MOAIJsonParser.JSON_INDENT )


local dataBuffer  = MOAIDataBuffer.new()
  dataBuffer:setString(str)
  dataBuffer:save('stance.json')

print ( str )

object = MOAIJsonParser.decode ( str )








--[[
for key, value in pairs ( object ) do
	print ( key .. " = " .. value )
end
]]--
