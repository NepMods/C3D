CC = gcc
CFLAGS = -Wall -std=c11 -Ilibs/glad/include -Ilibs/ -Isrc
LIBS = -lglfw -ldl -lm

SRC = src/main.c \
	  libs/glad/src/glad.c \
	  libs/c_dynamic_array/cda.c \
	  libs/c_dynamic_array/arena_alloc/arena.c \
	  src/engine/core/renderer/renderer.c \
	  src/engine/core/shader/shader.c \
	  src/engine/core/scene/scene.c \
	  src/engine/core/matrix4x4/matrix4x4.c \
	  src/engine/core/transform/transform.c \
	  src/engine/core/Camera/Camera.c \
	  src/engine/vec3/vec3.c \
      src/engine/core/vertex/vertex.c \
      src/engine/triangle/Triangle.c \
      src/engine/helper/helper.c \
      src/engine/Mesh/mesh.c \
      src/engine/Rect/Rect.c



OBJ = $(patsubst %.c,build/%.o,$(SRC))
TARGET = opengl_gui

# Ensure build directories exist
BUILD_DIRS = $(sort $(dir $(OBJ)))

all: $(TARGET)

# Create build directories if they don't exist
$(BUILD_DIRS):
	mkdir -p $@

# Link target
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o build/$@ $^ $(LIBS)

# Compile .c -> .o
build/%.o: %.c | $(BUILD_DIRS)
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	./build/$(TARGET)

clean:
	rm -rf build/*

build_shader:
	 xxd -i assets/shaders/vertex_shader.glsl > src/engine/core/shader/vertex_shader.h
	 xxd -i assets/shaders/fragment_shader.glsl > src/engine/core/shader/fragment_shader.h