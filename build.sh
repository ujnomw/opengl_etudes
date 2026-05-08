mkdir build && \
clang++ src/main.cpp src/glad.c \                                                                                                                                                    ✔  5s  21:33:12
  -Iinclude \
  -I/opt/homebrew/include \
  -L/opt/homebrew/lib \
  -lglfw \
  -framework OpenGL \
  -o app
