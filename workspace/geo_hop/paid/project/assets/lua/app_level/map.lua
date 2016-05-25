return {
  version = "1.1",
  luaversion = "5.1",
  orientation = "orthogonal",
  width = 15,
  height = 10,
  tilewidth = 32,
  tileheight = 32,
  properties = {},
  tilesets = {
    {
      name = "DEADDARK",
      firstgid = 1,
      tilewidth = 32,
      tileheight = 32,
      spacing = 0,
      margin = 0,
      image = "C:/Documents and Settings/Administrator/Desktop/EZRA_MOAI/MAP_EDITOR/GAMENAME/VS/_ASSETS/TILESET.png",
      imagewidth = 256,
      imageheight = 256,
      tileoffset = {
        x = 0,
        y = 0
      },
      properties = {},
      tiles = {}
    },
    {
      name = "numbers",
      firstgid = 65,
      tilewidth = 32,
      tileheight = 32,
      spacing = 0,
      margin = 0,
      image = "C:/Documents and Settings/Administrator/Desktop/tiled/numbers.png",
      imagewidth = 512,
      imageheight = 512,
      transparentcolor = "#ffffff",
      tileoffset = {
        x = 0,
        y = 0
      },
      properties = {},
      tiles = {}
    },
    {
      name = "objects",
      firstgid = 321,
      tilewidth = 32,
      tileheight = 32,
      spacing = 0,
      margin = 0,
      image = "C:/Documents and Settings/Administrator/Desktop/tiled/objects.png",
      imagewidth = 128,
      imageheight = 128,
      transparentcolor = "#ffffff",
      tileoffset = {
        x = 0,
        y = 0
      },
      properties = {},
      tiles = {}
    }
  },
  layers = {
    {
      type = "tilelayer",
      name = "level_1",
      x = 0,
      y = 0,
      width = 15,
      height = 10,
      visible = true,
      opacity = 0.44,
      properties = {},
      encoding = "lua",
      data = {
        1, 2, 2, 2, 2, 4, 0, 0, 0, 1, 2, 2, 2, 2, 4,
        9, 0, 0, 0, 0, 25, 3, 18, 3, 28, 0, 0, 0, 0, 9,
        9, 0, 0, 0, 0, 0, 9, 0, 11, 0, 0, 0, 0, 0, 9,
        9, 0, 0, 0, 0, 0, 25, 2, 28, 0, 0, 0, 0, 0, 9,
        9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9,
        9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9,
        9, 0, 0, 0, 0, 0, 1, 2, 4, 0, 0, 0, 0, 0, 9,
        9, 0, 0, 0, 0, 0, 11, 0, 11, 0, 0, 0, 0, 0, 9,
        9, 0, 0, 0, 0, 1, 27, 18, 27, 4, 0, 0, 0, 0, 9,
        25, 18, 18, 18, 18, 28, 0, 0, 0, 25, 2, 2, 2, 2, 28
      }
    },
    {
      type = "objectgroup",
      name = "Object Layer 1",
      visible = true,
      opacity = 1,
      properties = {},
      objects = {
        {
          name = "",
          type = "",
          shape = "rectangle",
          x = 26,
          y = 25.5,
          width = 141.5,
          height = 270.5,
          rotation = 0,
          visible = true,
          properties = {}
        },
        {
          name = "",
          type = "",
          shape = "rectangle",
          x = 150.5,
          y = 57.5,
          width = 50,
          height = 208.5,
          rotation = 0,
          visible = true,
          properties = {}
        },
        {
          name = "",
          type = "",
          shape = "rectangle",
          x = 183,
          y = 118.5,
          width = 119,
          height = 83,
          rotation = 0,
          visible = true,
          properties = {}
        },
        {
          name = "",
          type = "",
          shape = "rectangle",
          x = 281.5,
          y = 58,
          width = 58.5,
          height = 206.5,
          rotation = 0,
          visible = true,
          properties = {}
        },
        {
          name = "",
          type = "",
          shape = "rectangle",
          x = 312.5,
          y = 24.5,
          width = 144.5,
          height = 272,
          rotation = 0,
          visible = true,
          properties = {}
        }
      }
    }
  }
}
