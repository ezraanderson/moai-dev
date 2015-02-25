------------------------------------------------------------------------
--
-- Moai 3D model viewer
--
------------------------------------------------------------------------

local windowTitle = 'Moai 3D viewer'

local viewportWidth = 640
local viewportHeight = 480

local textSize = 24

local creditString = 'Low poly TF2 character by Tommy Tallian'

-- A string of all ASCII printable characters to preload
local charCodes = ''
for i = 32, 126 do charCodes = charCodes .. string.char(i) end

local viewport = MOAIViewport.new()
local camera = MOAICamera.new()
local prop = MOAIProp.new()
local font = MOAIFont.new()
local textBox = MOAITextBox.new()
local layer = MOAILayer.new()

-- Configure the viewport
viewport:setSize(viewportWidth, viewportHeight)
viewport:setScale(viewportWidth, viewportHeight)

-- Configure the camera
camera:setLoc(0, 0, camera:getFocalLength(viewportWidth))

-- Configure the prop
prop:setDeck(require('engineer'))
prop:setTexture('engineer.png')
prop:setShader(MOAIShaderMgr.getShader(MOAIShaderMgr.MESH_SHADER))
prop:setCullMode(MOAIProp.CULL_NONE)
prop:setDepthTest(MOAIProp.DEPTH_TEST_LESS)

-- Configure the font for text output
font:load('Bangers.ttf')
font:preloadGlyphs(charCodes, textSize)

-- Configure text output
textBox:setFont(font)
textBox:setTextSize(textSize)
textBox:setYFlip(true)
textBox:setRect(0, 0, viewportWidth, viewportHeight)
textBox:setLoc(-viewportWidth / 2, -viewportHeight / 2)

-- Configure the layer
layer:setViewport(viewport)
layer:setCamera(camera)
layer:insertProp(prop)
layer:insertProp(textBox)

-- Set a softer clear color and enable the depth buffer
MOAIGfxDevice.getFrameBuffer():setClearColor(0.05, 0.05, 0.1, 1.0)
MOAIGfxDevice.getFrameBuffer():setClearDepth(true)

-- Open the window and display the layer
MOAISim.openWindow(windowTitle, viewportWidth, viewportHeight)
MOAISim.pushRenderPass(layer)

--
-- Yield for a specified number of frames
--
function wait(frames)
    for i = 1, frames do
        coroutine.yield()
    end
end

--
--
--
function updateProp()
    while true do
        MOAIThread.blockOnAction(prop:moveRot(135, 360, 0, 3))
    end
end

--
-- Periodically update performance stats
--
function updateTextBox()
    while true do
        local fps = MOAISim.getPerformance()
        local ram = MOAISim.getMemoryUsage().total / 1024
        local s = string.format('%1.1f fPS\n%1.1f kB\n', fps, ram)
        textBox:setString(s .. creditString)
        wait(60)
    end
end

local threadFunctions = {updateProp, updateTextBox}
local threads = {}

for i = 1, #threadFunctions do
    threads[i] = MOAICoroutine.new()
    threads[i]:run(threadFunctions[i])
end
