MOAISim.setTraceback(function() end)

local task_post  = MOAIHttpTask.new()
local ip_address = 'http://192.168.1.006:8080/updater/script.lua'


local function done_fetch()
	local start = loadstring (task_post:getString())
	start()
end

task_post:setVerb ( MOAIHttpTaskCurl.HTTP_POST )
task_post:setUrl ( ip_address )
task_post:setCallback ( done_fetch )
task_post:performSync () --very fast



