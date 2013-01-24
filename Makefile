all: 1-typedefs 2-special_types 3-functions 4-jumptable 5-macros 5.5-xmacros 6-attributes

# You may need to remove -fnested-functions if your GCC doesn't support it
# This appears to be the case for earlier versions of GCC on Linux
ifneq ($(strip $(shell uname -s)),Linux)
FNESTED_FUNCTIONS_OPTION	:= -fnested-functions
else
FNESTED_FUNCTIONS_OPTION	:=
endif
$(warning Using FNESTED_FUNCTIONS_OPTION = $(FNESTED_FUNCTIONS_OPTION))

%: %.c
	gcc -std=gnu99 $(FNESTED_FUNCTIONS_OPTION) $< -o $@

jumptable.asm: 4-jumptable
	objdump -D 4-jumptable > jumptable.asm
