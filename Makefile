TARGET					:= cluster

CFLAGS					:= -Wall -Wextra -pedantic
LDFLAGS					:=

CC						:= clang
LINK_CMD				:= clang

SRC_DIR					:= src
INT_DIR					:= bin
VEN_DIR					:= vendor
MLX_DIR					:= $(VEN_DIR)/minilibx-macos
INC_DIR					:= -I src -I $(MLX_DIR)
OUT_DIR					:= $(INT_DIR)

MLX_LIB					:= $(MLX_DIR)/libmlx.a

SRC_FILES				:= $(SRC_DIR)/main.c $(SRC_DIR)/gfx/image_buffer.c \
							$(SRC_DIR)/util/memory.c $(SRC_DIR)/gfx/window.c $(SRC_DIR)/gfx/renderer.c \
							$(SRC_DIR)/player/player.c $(SRC_DIR)/map/drop.c $(SRC_DIR)/map/rotate.c \
							$(SRC_DIR)/map/win.c $(SRC_DIR)/map/hex.c $(SRC_DIR)/map/grid.c \
							$(SRC_DIR)/util/syscalls.c $(SRC_DIR)/game/game.c $(SRC_DIR)/map/opt.c

BLACK					:="\033[0;30m"
RED						:="\033[0;31m"
GREEN					:="\033[0;32m"
ORANGE					:="\033[0;33m"
BLUE					:="\033[0;34m"
PURPLE					:="\033[0;35m"
CYAN					:="\033[0;36m"
LIGHT_GRAY				:="\033[0;37m"

DARK_GRAY				:="\033[1;30m"
LIGHT_RED				:="\033[1;31m"
LIGHT_GREEN				:="\033[1;32m"
YELLOW					:="\033[1;33m"
LIGHT_BLUE				:="\033[1;34m"
LIGHT_PURPLE			:="\033[1;35m"
LIGHT_CYAN				:="\033[1;36m"
WHITE					:="\033[1;37m"

RESET					:="\033[0m"

COMPILE_COLOR			:= $(GREEN)
LINK_COLOR				:= $(CYAN)
OBJECT_COLOR			:= $(RED)

ifndef config
	config				:= debug
endif

ifndef san
	san					:= address,undefined
endif

SILENT					:= @
ifdef verbose
	SILENT				:=
endif

ifeq ($(config), debug)
	CFLAGS				+= -g3 -Og -fsanitize=$(san) -DGF_BUILD_DEBUG
	LDFLAGS				+= -g3 -Og -fsanitize=$(san) -fno-inline
	OUT_DIR				:= $(INT_DIR)/debug
else ifeq ($(config), release)
	CFLAGS				+= -g -O1 -DGF_BUILD_RELEASE
	LDFLAGS				+= -g -O1
	OUT_DIR				:= $(INT_DIR)/release
else ifeq ($(config), distr)
	CFLAGS				+= -g0 -Ofast -DGF_BUILD_DISTR
	LDFLAGS				+= -g0 -Ofast
	OUT_DIR				:= $(INT_DIR)/distr
else
$(error "invalid config '$(config)")
endif

all: $(TARGET)

OBJ_FILES				:= $(patsubst $(SRC_DIR)/%,$(OUT_DIR)/%.o,$(basename $(SRC_FILES)))
DEP_FILES				:= $(patsubst $(SRC_DIR)/%,$(OUT_DIR)/%.d,$(basename $(SRC_FILES)))

$(TARGET): $(OBJ_FILES) $(MLX_LIB)
	@printf $(LINK_COLOR)Linking$(RESET)\ $(OBJECT_COLOR)$(notdir $@)$(RESET)\\n
	$(SILENT)$(LINK_CMD) $(LDFLAGS) -o $@ $(OBJ_FILES) -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

$(TEST_BOT): $(OBJ_FILES) $(MLX_LIB)
	@echo $(OBJ_FILES)
	@echo $(SRC_FILES)
	@printf $(LINK_COLOR)Linking$(RESET)\ $(OBJECT_COLOR)$(notdir $@)$(RESET)\\n
	$(SILENT)$(LINK_CMD) $(LDFLAGS) -o $@ $(OBJ_FILES) -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

$(OUT_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@printf $(COMPILE_COLOR)Compiling$(RESET)\ $(notdir $<)\\n
	$(SILENT)$(CC) $(CFLAGS) -c $< -o $@ -MMD $(INC_DIR)

$(MLX_LIB):
	$(SILENT)${MAKE} -C $(MLX_DIR)

clean:
	$(SILENT)rm -rf $(INT_DIR)
	$(SILENT)${MAKE} -C $(MLX_DIR) clean

re: clean all

run: all
	$(SILENT)./$(TARGET)

rerun: clean run

-include $(DEP_FILES)