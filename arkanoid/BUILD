cc_binary(
    name = "main",
    srcs = [
        "main.cpp",
    ],
    deps = [
      "@raylib",
      "//box2d:box2d",
    ],
    linkopts = ["-framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL"]
)
