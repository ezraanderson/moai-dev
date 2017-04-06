--****************************************
--ad commas
function comma_value(amount)
  local formatted = amount
  while true do
    formatted, k = string.gsub(formatted, "^(-?%d+)(%d%d%d)", '%1,%2')
    if (k==0) then
      break
    end
  end
  return formatted
end




--****************************************
--round
function round(val, decimal)
  if (decimal) then
    return math.floor( (val * 10^decimal) + 0.5) / (10^decimal)
  else
    return math.floor(val+0.5)
  end
end




--******************************************************************************
--memusages
function format_num(amount, decimal, prefix, neg_prefix)

  local str_amount,  formatted, famount, remain

  decimal = decimal or 2  -- default 2 decimal places
  neg_prefix = neg_prefix or "-" -- default negative sign

  famount = math.abs(round(amount,decimal))
  famount = math.floor(famount)

  remain = round(math.abs(amount) - famount, decimal)

        -- comma to separate the thousands
  formatted = comma_value(famount)

        -- attach the decimal portion
  if (decimal > 0) then
    remain = string.sub(tostring(remain),3)
    formatted = formatted .. "." .. remain ..
                string.rep("0", decimal - string.len(remain))
  end

        -- attach prefix string e.g '$'
  formatted = (prefix or "") .. formatted

        -- if value is negative then format accordingly
  if (amount<0) then
    if (neg_prefix=="()") then
      formatted = "("..formatted ..")"
    else
      formatted = neg_prefix .. formatted
    end
  end

  return formatted
end



--******************************************************************************

local myCache = {}

myCache['total']  		=0
myCache['lua']    		=0
myCache['texture']		=0
myCache['_luagc_count'] =0
myCache['_sys_rss']		=0
myCache['_sys_vs']		=0









function printMemeUsage()


			  --collectgarbage()

--print('----------------------------------------------------------')

--for k in pairs (memUsage) do
--    memUsage[k] = nil
--end
							 
    --memUsage 	= MOAISim.getMemoryUsage()

                            local memUsage 	= MOAISim.getMemoryUsage()
                            
						 	local total 	= memUsage['total'] 	/1024
                            local lua 		= memUsage['lua'] 		/1024
                            local texture   = memUsage['texture'] 	/1024
                            local lc        = memUsage['_luagc_count']
                            local sr        = memUsage['_sys_rss']
        					local sv        = memUsage['_sys_vs']


                            print('total:           '..format_num(total,2)		..' '..format_num(myCache['total'],2)		..' '..format_num(total-myCache['total'],2))
                            print('lua:             '..format_num(lua,2)		..' '..format_num(myCache['lua'],2)		..' '..format_num(lua-myCache['lua'],2))
                            print('texture:         '..format_num(texture,2)	..' '..format_num(myCache['texture'],2)	..' '..format_num(texture-myCache['texture'],2))
                            
                            
                            --print('_luagc_count:    '..format_num(lc,-2))
                            --print('_sys_rss:        '..format_num(sr,-2))
                            --print('_sys_vs:         '..format_num(sv,-2))
                            
--print('--------------------------------------------------------')
--
--											for k,v in pairs(memUsage) do
--													print(k..' '..v)
--											end
--print('----------------------------------------------------------')
                            
                                 		--for k,v in pairs(MOAISim.getMemoryUsage()) do

                                        --      print(k,v)
                                      
                                      --	end
                                      
                                      

                                      
                                      
                                      
                            
        if myCache['total'] == 0 then
        
					myCache['total']  		=total
					myCache['lua']    		=lua
					myCache['texture']		=texture
					myCache['lc']			=lc
					myCache['sr']			=sr
					myCache['sv']			=sv


   		end

                            
                            
                            
                            
                            
                            


print('')
end



--              	local memUsage 	= MOAISim.getMemoryUsage()
--
--                  				for k,v in pairs(memUsage) do
--													print(k..' '..v)
--								end
--
