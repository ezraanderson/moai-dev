
--NEED TO FIX THE SMOOTHNESS BY ADDING A LIGHT TEXTURE AROUND THE HERO THAT IS THE SAME SIZE OF THE GRID FOG


local width = 1280
local height = 720
local current_dir = MOAIFileSystem.getWorkingDirectory()

--************************************************************************************************************
--************************************************************************************************************
--SET_UP

MOAISim.openWindow ( "test", width, height )

local viewport    = MOAIViewport.new ()
      viewport:setSize ( width, height )
      viewport:setScale ( width, -height )
      
local camera_main = MOAICamera2D.new ()

local fitter = MOAICameraFitter2D.new ()
      fitter:setViewport ( viewport )
      fitter:setCamera ( camera_main )
      fitter:setBounds ( 1280*-1*0.5, 720*-1*0.5, 1280*0.5, 720*0.5 )
      fitter:start ()       

local layer_tilemap = MOAILayer2D.new ()
      layer_tilemap:setViewport ( viewport )
      layer_tilemap:setCamera ( camera_main )      
      MOAISim.pushRenderPass ( layer_tilemap )      
      
local layer_fog = MOAILayer2D.new ()
      layer_fog:setViewport ( viewport )  
      MOAISim.pushRenderPass ( layer_fog ) 

local layer_hud = MOAILayer2D.new ()
      layer_hud:setViewport ( viewport )      
      MOAISim.pushRenderPass ( layer_hud )

--************************************************************************************************************
--************************************************************************************************************
--MAP

local map = {}
      map['width']  = 300
      map['height'] = 300

--************************************************************************************************************
--************************************************************************************************************
--FLOOR

local floor_texture= MOAITexture.new()
      floor_texture:setFilter ( MOAITexture.GL_LINEAR ) --smooth
      floor_texture:load(current_dir..'/tiles/grass.png' , MOAIImage.PREMULTIPLY_ALPHA )


local floor_deck = MOAITileDeck2D.new ()
      floor_deck:setSize ( 1, 1, 64/64, 64/64, 1/64, 1/64, 64/66, 64/64 ) 
      floor_deck:setUVRect(-0.5, 0.5, 0.5, -0.5)              
      floor_deck:setTexture ( floor_texture )

local floor_grid = MOAIGrid.new ()
      floor_grid:setSize ( map['width'],map['height'], 32, 32,0,0,32,32 )

local floor_prop = MOAIProp2D.new ()
      floor_prop:setGrid ( floor_grid )
      floor_prop:setDeck ( floor_deck )
      floor_prop:setLoc ( 0, 0)
      floor_prop:setColor(1,1,1,1)   

      layer_tilemap:insertProp ( floor_prop ) 

      for y = 0,map['height']-1 do 
        for x = 0,map['width']-1 do   
          floor_grid:setTile(x+1, y+1, 1)
        end 
      end 

--************************************************************************************************************
--************************************************************************************************************
--FOG
local fog_texture= MOAITexture.new()
      fog_texture:setFilter ( MOAITexture.GL_LINEAR ) --smooth
      fog_texture:load(current_dir..'/tiles/fog.png' , MOAIImage.PREMULTIPLY_ALPHA )


local fog_deck = MOAITileDeck2D.new ()
      fog_deck:setSize ( 1, 1, 64/64, 64/64, 1/64, 1/64, 64/66, 64/64 ) 
      fog_deck:setUVRect(-0.5, 0.5, 0.5, -0.5)              
      fog_deck:setTexture ( fog_texture )    
      

local fog_grid = MOAIGrid.new ()
      fog_grid:setSize ( map['width']*2,map['height']*2, 16, 16,0,0,16,16 ) --x2 smaller
      fog_grid:initRectGrid( map['width']*2,map['height']*2,16,16,-32,-32) --x2 Bigger   

local fog_prop = MOAIProp2D.new ()
      fog_prop:setGrid ( fog_grid )
      fog_prop:setDeck ( fog_deck )  
      fog_prop:setBlendMode(MOAIProp.BLEND_ADD)      
      
--************************************************************************************************************
--************************************************************************************************************     
--FRAME_BUFFER     


local viewport_framebuffer = MOAIViewport.new ()
      viewport_framebuffer:setSize ( width, height )
      --viewport_framebuffer:setSize (-32,-32, width+32, height+32 ) --not correct need to sort out gutter for cliping and offset for the gutter
      viewport_framebuffer:setScale ( width, height )

local layer_framebuffer = MOAILayer2D.new ()
      layer_framebuffer:setViewport ( viewport_framebuffer )	
      layer_framebuffer:setCamera(camera_main)

local texture_frameBuffer = MOAIFrameBufferTexture.new ()
      texture_frameBuffer:setRenderTable ({ layer_framebuffer })
      texture_frameBuffer:init ( width, height )
      texture_frameBuffer:setClearColor ( 0, 0, 0, 0 )
      
      MOAIRenderMgr.setBufferTable ({ texture_frameBuffer })  --render table    

      layer_framebuffer:insertProp ( fog_prop ) --INSERT FOG

local  gfxQuad = MOAIGfxQuad2D.new ()
       gfxQuad:setTexture ( texture_frameBuffer )
       gfxQuad:setRect ( -width*.5, -height*.5, width*.5, height*.5 )
       gfxQuad:setUVRect ( 0, 0, 1, 1 )

local  prop = MOAIProp2D.new ()
       prop:setDeck ( gfxQuad ) 
       prop:setBlendMode(MOAIProp.BLEND_MULTIPLY)
       layer_fog:insertProp ( prop )      
       
       
--************************************************************************************************************
--************************************************************************************************************  
--HERO

local hero_texture= MOAITexture.new()
      hero_texture:setFilter ( MOAITexture.GL_LINEAR ) --smooth
      hero_texture:load(current_dir..'/tiles/moai.png' , MOAIImage.PREMULTIPLY_ALPHA )

local hero_quad = MOAIGfxQuad2D.new ()
      hero_quad:setTexture ( hero_texture )
      hero_quad:setRect ( -16, 16, 16, -16 )
 
      
local hero_prop = MOAIProp2D.new ()
      hero_prop:setDeck(hero_quad)
      hero_prop:setLoc ( 0, 0)
      hero_prop:setColor(1,1,1,1)  
      hero_prop:setLoc(map['width']*32*.5,map['width']*32.*.5)
      
      layer_tilemap:insertProp ( hero_prop )

      --LINK TO HERO
      camera_main:setAttrLink ( MOAIProp2D.INHERIT_LOC,  hero_prop, MOAIProp2D.TRANSFORM_TRAIT ) 
      
      
--*******************************************************************************
--ENTER FRAME : WITH KEYBOARD : MOVE WITH WASD
local keyboard = MOAIInputMgr.device.keyboard
local function _enterframe()    
  
  while true do
    
  local hero_x,hero_y =   hero_prop:getLoc()
  
  if 	keyboard:keyIsDown ( 'w' ) then hero_y = hero_y - 2 end
  if 	keyboard:keyIsDown ( 'a' ) then hero_x = hero_x - 2 end
  if 	keyboard:keyIsDown ( 's' ) then hero_y = hero_y + 2 end
  if 	keyboard:keyIsDown ( 'd' ) then hero_x = hero_x + 2 end  
  
--SET LIGHT NODES FOR FOG
--NEED TO FIGURE OUT A SMOOTHER DRAW METHOD
    local fX  = (math.floor(hero_x/16))
    local fY  = (math.floor(hero_y/16))

    local fogX=fX+1-4
    local fogY=fY+1-4
    for y = 1, 8 do    
     for x = 1,8 do         
        fog_grid:setTile(fogX, fogY, 1) 
        fogX = fogX + 1      
     end
    fogX =fX+1-4
    fogY =fogY + 1  
    end

    hero_prop:setLoc(hero_x,hero_y)

  local delta=	coroutine.yield()
  end

end
  
  
local mThread_enterframe = MOAICoroutine.new ()
mThread_enterframe:run ( _enterframe ) 
  
  
  
  