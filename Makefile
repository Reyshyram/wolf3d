##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## Makefile used to compile the project, as well as the libraries in lib/
##

NAME			:= wolf3d
CC				:= epiclang

# --- Folders
SRC_DIR			:= src
LIB_DIR			:= lib
TESTS_DIR		:= tests
INC_DIR			:= include
OBJS_DIR		:= obj

# --- Libraries
# Finds every folder in lib/ to archive into a lib[folder].a file
LIB_PATHS		:= $(shell find $(LIB_DIR) -mindepth 1 -maxdepth 1 -type d)
LIB_NAMES		:= $(notdir $(LIB_PATHS))
LIB_TARGETS		:= $(foreach lib,$(LIB_NAMES),$(LIB_DIR)/lib$(lib).a)

# --- Files to compile
SRCS			:= $(shell find $(SRC_DIR) -type f -name '*.c')
LIB_SRCS		:= $(shell find $(LIB_DIR) -type f -name '*.c')
OBJ_SRCS		:= $(SRCS:%.c=$(OBJS_DIR)/%.o)
OBJ_LIB			:= $(LIB_SRCS:%.c=$(OBJS_DIR)/%.o)

# --- Tests
OBJ_NO_MAIN		:= $(filter-out $(OBJS_DIR)/$(SRC_DIR)/main.o, $(OBJ_SRCS))
TESTS_TARGET	:= unit_tests
TESTS_SRCS		:= $(shell find $(TESTS_DIR) -type f -name '*.c')
OBJ_TESTS		:= $(TESTS_SRCS:%.c=$(OBJS_DIR)/%.o)

# --- Flags
CPPFLAGS		:= -I$(INC_DIR) -MMD -MP
CFLAGS			:= -Wall -Wextra -std=gnu2x
_COVERAGE_FLAGS	:= --coverage
COVERAGE_FLAGS	:=
LDFLAGS			:= -L$(LIB_DIR)
# Automatically link all libs in the lib/ folder
LDLIBS			:= $(foreach lib,$(LIB_NAMES),-l$(lib)) -lcsfml-window -lcsfml-graphics -lcsfml-system -lcsfml-audio -lm
AR				:= ar
ARFLAGS			:= rc

# --- Colors
BOLD			:= \033[1m
FAINT			:= \033[2m
GREEN			:= \033[32m
YELLOW			:= \033[33m
BLUE			:= \033[34m
RESET			:= \033[0m

# --- Rules
all: $(LIB_TARGETS) $(NAME)

debug: CFLAGS += -g3
debug: CFLAGS += -DDEBUG
debug: CC = gcc
debug: all

$(NAME): $(LIB_TARGETS) $(OBJ_SRCS)
	@printf "$(YELLOW)Linking $(NAME)...$(RESET)\n"
	@$(CC) -o $@ $(OBJ_SRCS) $(CFLAGS) $(LDFLAGS) $(LDLIBS)
	@printf "$(BOLD)$(GREEN)./$@ compiled successfully (˶ᵔ ᵕ ᵔ˶)$(RESET)\n"

# --- Libs
# Macro to create a lib/libname.a file for every folder in lib/
# Use $$ to expand the variable when the rule is called and not now
define GEN_LIB_RULE
$(LIB_DIR)/lib$(1).a: $(filter $(OBJS_DIR)/$(LIB_DIR)/$(1)/%, $(OBJ_LIB))
	@printf "$(YELLOW)Archiving lib$(1).a...$(RESET)\n"
	@mkdir -p $(LIB_DIR)
	@$(AR) $(ARFLAGS) $$@ $$^
endef

$(foreach lib,$(LIB_NAMES),$(eval $(call GEN_LIB_RULE,$(lib))))

# --- Compilation
$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@printf "$(FAINT)Compiling $(BOLD)$<$(RESET)\n"
	@$(CC) $(CPPFLAGS) $(CFLAGS) $(COVERAGE_FLAGS) -c $< -o $@

# --- Clean
clean:
	@printf "Cleaning objects...\n"
	@rm -rf $(OBJS_DIR)

fclean: clean
	@printf "Cleaning binaries...\n"
	@rm -f $(NAME) $(TESTS_TARGET) $(LIB_TARGETS)

re:
	@$(MAKE) fclean --no-print-directory
	@$(MAKE) all --no-print-directory

# --- Tests
unit_tests: COVERAGE_FLAGS += $(_COVERAGE_FLAGS)
$(OBJ_LIB): COVERAGE_FLAGS =
unit_tests: $(LIB_TARGETS) $(OBJ_NO_MAIN) $(OBJ_TESTS)
	@printf "$(YELLOW)Linking tests binary...$(RESET)\n"
	@$(CC) -o $(TESTS_TARGET) $(OBJ_NO_MAIN) $(OBJ_TESTS) \
		$(CFLAGS) $(CPPFLAGS) \
		$(LDFLAGS) $(LDLIBS) $(_COVERAGE_FLAGS) -lcriterion
	@printf "$(GREEN)$(BOLD)Tests compiled successfully (˶ᵔ ᵕ ᵔ˶)$(RESET)\n"

tests_run: unit_tests
	@printf "$(BOLD)$(YELLOW)Running tests...$(RESET)\n"
	@./$(TESTS_TARGET)

tests_clean:
	@printf "Cleaning coverage data...\n"
	@find . -type f \( -name '*.gcda' -o -name '*.gcno' \) -delete

# --- Special
.PHONY: all clean fclean re unit_tests tests_run tests_clean debug
-include $(OBJ_SRCS:.o=.d) $(OBJ_LIB:.o=.d) $(OBJ_TESTS:.o=.d)
