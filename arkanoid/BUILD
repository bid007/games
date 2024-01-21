
cc_library (
  name = "lib",
  srcs = [
    "constants.h",
    "game_data.h",
    "contact_listener.h",
    "game_world.h",
    "game_world.cpp",
  ],
  deps = [
    "@raylib",
    "//box2d:box2d"
  ]
)

cc_binary(
    name = "main",
    srcs = [
        "main.cpp",
    ],
    deps = [":lib",],
    data = ["resources/hit.wav"],
    linkopts = ["-framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL"]
)
