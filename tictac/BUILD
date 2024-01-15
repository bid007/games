# clang -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL lib/raylib/libraylib.a tictac/main.cpp -o my_app -std=c++11
# bazel run -c dbg //tictac:main --run_under=lldb --sandbox_debug
cc_binary(
    name = "main",
    srcs = [
        "main.cpp",
    ],
    deps = [
      "@raylib",
    ],
    linkopts = ["-framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL"]
)
