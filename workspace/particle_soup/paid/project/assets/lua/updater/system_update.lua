--******************************************************************************
--******************************************************************************
--******************************************************************************


lfs 	= require("lfs")


print('devPlatform:',	MOAIEnvironment.devPlatform)
print('devProduct:',	MOAIEnvironment.devProduct)
print('devModel:',		MOAIEnvironment.devModel)
print('osVersion:',		MOAIEnvironment.osVersion)
print('osBrand:  ',		MOAIEnvironment.osBrand)

print('')
print('')
print('appDisplayName:________  ',	    	MOAIEnvironment.appDisplayName  )
print('appID:________________  ',	    			MOAIEnvironment.appID           )
print('appVersion:___________  ',	    		MOAIEnvironment.appVersion      )
print('cacheDirectory:_______  ',	    	MOAIEnvironment.cacheDirectory  )
print('carrierISOCountryCode:  ',	MOAIEnvironment.carrierISOCountryCode)
print('carrierMobileCountryCode:  ',MOAIEnvironment.carrierMobileCountryCode)
print('carrierMobileNetworkCode:  ',MOAIEnvironment.carrierMobileNetworkCode)
print('carrierName:__________  ',	    		MOAIEnvironment.carrierName)
print('connectionType:_______  ',	    	MOAIEnvironment.connectionType)
print('countryCode:__________  ',	    		MOAIEnvironment.countryCode)
print('cpuabi:_______________  ',	    			MOAIEnvironment.cpuabi)
print('devBrand:_____________  ',	    		MOAIEnvironment.devBrand)
print('devName:______________  ',	    			MOAIEnvironment.devName)
print('devManufacturer:______  ',	    	MOAIEnvironment.devManufacturer)
print('devModel:_____________  ',	    		MOAIEnvironment.devModel)
print('devPlatform:__________  ',	    		MOAIEnvironment.devPlatform)
print('devProduct:___________  ',	    		MOAIEnvironment.devProduct)
print('documentDirectory:____  ',	    MOAIEnvironment.documentDirectory)
print('iosRetinaDisplay:_____  ',	    MOAIEnvironment.iosRetinaDisplay)
print('languageCode:_________  ',	    	MOAIEnvironment.languageCode)
print('numProcessors:________  ',	    	MOAIEnvironment.numProcessors)
print('osBrand:______________  ',	    			MOAIEnvironment.osBrand)
print('osVersion:____________  ',	    		MOAIEnvironment.osVersion)
print('resourceDirectory:____  ',	    MOAIEnvironment.resourceDirectory)
print('screenDpi:____________  ',	    		MOAIEnvironment.screenDpi)
print('verticalResolution:___  ',	    MOAIEnvironment.verticalResolution)
print('horizontalResolution:_  ',	MOAIEnvironment.horizontalResolution)
print('udid:_________________  ',	    			MOAIEnvironment.udid)
print('openUdid:_____________  ',	    		MOAIEnvironment.openUdid)
  print('screen Size',MOAIEnvironment.horizontalResolution, MOAIEnvironment.verticalResolution)
print('screen Size',MOAIEnvironment.screenWidth, MOAIEnvironment.screenHeigh)
print('')




--local jit = require("jit")
--
--   	local startTime = os.clock()
--  	local x=0; for i=1,1e9 do x=math.abs(x) end
--  	print("Jit Time",os.clock()-startTime)
--   
--
--print('Lua Versions:',_VERSION)
--print('Jit Status:'	 ,jit.status())
--






--******************************************************************************
--******************************************************************************
--******************************************************************************
--SYSTEM
system = {}


--file structur for game
system.paths = {}
system['paths']['sounds'] = 'app_sounds'
system['paths']['sounds'] = 'app_images'
system['paths']['fonts']  = 'app_font'



--******************************************************************************
--******************************************************************************
--******************************************************************************
--decoder
		baseEncode = MOAIDataBuffer.base64Encode
		baseDecode = MOAIDataBuffer.base64Decode
		jsonEncode = MOAIJsonParser.encode
		jsonDecode = MOAIJsonParser.decode
		


---*****************************************************************************
---*****************************************************************************
function system.getInfo(string)
 	  if 	 string == 'environment' 	then return   MOAIEnvironment.devPlatform
 	  elseif string == 'platformName' 	then return   MOAIEnvironment.devProduct
	  elseif string == 'model' 			then return   MOAIEnvironment.devModel
	  elseif string == 'osVersion'      then return   MOAIEnvironment.osVersion --xp
	  elseif string == 'osBrand'        then return   MOAIEnvironment.osBrand  --windows
	  end


end





 
if (MOAIEnvironment.osBrand == 'Windows') then

	system.isWindow = true
	system.osType   = 'windows'

			system.gameDirectory = MOAIFileSystem.getWorkingDirectory()
			system.baseDirectory = string.gsub(system.gameDirectory, '/game/lua/', "/")  --back to directories

			system.documentsDirectory 	= system.baseDirectory..'_system//windows_documents'
			system.cacheDirectory 		= system.baseDirectory..'_system//windows_cache'
	 		system.resourceDirectory  	= system.gameDirectory


elseif (MOAIEnvironment.osBrand == 'Linux') then

	system.isWindow = true
	system.osType   = 'Linux'

			system.gameDirectory = MOAIFileSystem.getWorkingDirectory()
			system.baseDirectory = MOAIFileSystem.getWorkingDirectory()  --back to directories

			system.documentsDirectory 	= system.baseDirectory..'_cache//windows_documents'
			system.cacheDirectory 		= system.baseDirectory..'_cache//windows_cache'
	 		system.resourceDirectory  	= system.gameDirectory







elseif (MOAIEnvironment.osBrand == 'OSX') and (MOAIEnvironment.OS_BRAND_OSX) then

	system.isOsx 	= true
	system.osType   = 'osx'

			system.gameDirectory = MOAIFileSystem.getWorkingDirectory()
			system.baseDirectory = string.gsub(system.gameDirectory, '/game/lua/', "/") --back to directories

			system.documentsDirectory = system.baseDirectory..'_system//osx_documents'
			system.cacheDirectory 	  = system.baseDirectory..'_system//osx_cache'
	 		system.resourceDirectory  = system.gameDirectory


elseif (MOAIEnvironment.osBrand == 'iOS') and (MOAIEnvironment.OS_BRAND_IOS) then

		system.isIos 	= true
		system.osType   = 'ios'

		        system.gameDirectory = MOAIFileSystem.getWorkingDirectory()

				system.documentsDirectory = MOAIEnvironment.documentDirectory
				system.cacheDirectory 	  = MOAIEnvironment.cacheDirectory
		 		system.resourceDirectory  = MOAIEnvironment.resourceDirectory




elseif (MOAIEnvironment.osBrand == 'Android') then


		--*************************************
		--android doesn't have a cache directory

		system.isAndroid = true
		system.osType   = 'android'

				--system.gameDirectory = MOAIEnvironment.resourceDirectory
		        system.gameDirectory = MOAIFileSystem.getWorkingDirectory()
				system.documentsDirectory = MOAIEnvironment.documentDirectory
				system.cacheDirectory 	  = MOAIEnvironment.documentDirectory
		 		system.resourceDirectory  = MOAIEnvironment.resourceDirectory






end


