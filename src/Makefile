#
# Copyright (C) 2020 Linux Studio Plugins Project <https://lsp-plug.in/>
#           (C) 2020 Vladimir Sadovnikov <sadko4u@gmail.com>
#
# This file is part of lsp-dsp-lib
#
# lsp-dsp-lib is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# any later version.
#
# lsp-dsp-lib is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with lsp-dsp-lib.  If not, see <https://www.gnu.org/licenses/>.
#

CONFIG                 := $(CURDIR)/.config.mk

include $(CONFIG)
include $(CURDIR)/../project.mk

rwildcard               = $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))

CXX_SRCMAIN             = 
CXX_SRCEXT              = main/dsp.cpp main/generic/generic.cpp
CXX_SRCALL              = $(call rwildcard, main, *.cpp)
CXX_SRCTEST             = $(call rwildcard, test, *.cpp)
CXX_SRC                 = $(CXX_SRCMAIN)

CXX_OBJ                 = $(patsubst %.cpp, $($(ARTIFACT_VARS)_BIN)/%.o, $(CXX_SRC))
CXX_OBJEXT              = $(patsubst %.cpp, $($(ARTIFACT_VARS)_BIN)/%.o, $(CXX_SRCEXT))

ALL_HEADERS             = $(call rwildcard, $($(ARTIFACT_VARS)_INC), *.h)
CXX_FILE                = $(patsubst $($(ARTIFACT_VARS)_BIN)/%.o,%.cpp, $(@))
CXX_HEADERS             = $(foreach hdr,$(ARTIFACT_HEADERS),$(call rwildcard, $($(ARTIFACT_VARS)_INC)/$(hdr), *.h))
CXX_INSTHEADERS         = $(patsubst $($(ARTIFACT_VARS)_INC)/%,$(DESTDIR)$(INCDIR)/%,$(CXX_HEADERS))

ARTIFACT_BIN            = $($(ARTIFACT_VARS)_BIN)
ARTIFACT_LIB            = $(ARTIFACT_BIN)/$(LIBRARY_PREFIX)$($(ARTIFACT_VARS)_NAME)-$($(ARTIFACT_VARS)_VERSION)$(LIBRARY_EXT)
ARTIFACT_SLIB           = $(ARTIFACT_BIN)/$(LIBRARY_PREFIX)$($(ARTIFACT_VARS)_NAME)-$($(ARTIFACT_VARS)_VERSION)$(STATICLIB_EXT)
ARTIFACT_LIBLINK        = $(LIBRARY_PREFIX)$($(ARTIFACT_VARS)_NAME)$(LIBRARY_EXT)
ARTIFACT_SLIBLINK       = $(LIBRARY_PREFIX)$($(ARTIFACT_VARS)_NAME)$(STATICLIB_EXT)
ARTIFACT_PC             = $(ARTIFACT_BIN)/$($(ARTIFACT_VARS)_NAME)$(PKGCONFIG_EXT)
ARTIFACT_TESTBIN        = $(ARTIFACT_BIN)/$($(ARTIFACT_VARS)_NAME)-test$(EXECUTABLE_EXT)
ARTIFACT_OBJ            = $($(ARTIFACT_VARS)_OBJ)
ARTIFACT_MFLAGS         = $($(ARTIFACT_VARS)_MFLAGS) $(foreach dep,$(DEPENDENCIES),-DUSE_$(dep))

CFLAGS_DEPS             = $(foreach dep, $(DEPENDENCIES) $(ARTIFACT_VARS), $(if $($(dep)_CFLAGS), $($(dep)_CFLAGS)))
BUILD_DEPS              = $(foreach dep, $(DEPENDENCIES), $(if $($(dep)_OBJ), $(dep)))
LINKER_DEPS             = $(foreach dep, $(DEPENDENCIES), $(if $($(dep)_LDFLAGS), $($(dep)_LDFLAGS)))
LINKER_OBJS             = $(foreach dep, $(DEPENDENCIES), $(if $($(dep)_OBJ), $($(dep)_OBJ)))
BUILD_ALL               = $(ARTIFACT_LIB) $(ARTIFACT_SLIB) $(ARTIFACT_PC)

ifeq ($(TEST), 1)
  ifeq ($($(ARTIFACT_VARS)_TESTING),1)
    CXX_SRC                += $(CXX_SRCTEST)
    BUILD_ALL              += $(ARTIFACT_TESTBIN)
  endif
  DEPENDENCIES           += $(TEST_DEPENDENCIES)
endif

ifeq ($(NO_DEPENDENCIES),1)
  BUILD_DEPS              =
endif

CXX_DEPS                = $(foreach src,$(CXX_SRCALL) $(CXX_SRCTEST),$(patsubst %.cpp,$(ARTIFACT_BIN)/%.d,$(src)))
CXX_DEPFILE             = $(patsubst $(ARTIFACT_BIN)/%.d,%.cpp,$(@))
CXX_DEPTARGET           = $(patsubst $(ARTIFACT_BIN)/%.d,%.o,$(@))

# Configre list of extended build parameters
X86_IMPL                = $(ARTIFACT_BIN)/main/x86/x86.o
SSE_IMPL                = $(ARTIFACT_BIN)/main/x86/sse.o
SSE2_IMPL               = $(ARTIFACT_BIN)/main/x86/sse2.o
SSE3_IMPL               = $(ARTIFACT_BIN)/main/x86/sse3.o
SSE4_IMPL               = $(ARTIFACT_BIN)/main/x86/sse4.o
AVX_IMPL                = $(ARTIFACT_BIN)/main/x86/avx.o
AVX2_IMPL               = $(ARTIFACT_BIN)/main/x86/avx2.o
ARM_IMPL                = $(ARTIFACT_BIN)/main/arm/arm.o
NEON_D32_IMPL           = $(ARTIFACT_BIN)/main/arm/neon-d32.o
AARCH64_IMPL            = $(ARTIFACT_BIN)/main/aarch64/aarch64.o
ASIMD_IMPL              = $(ARTIFACT_BIN)/main/aarch64/asimd.o

SSE_INSTR_SET           = -mmmx -m3dnow -msse
SSE2_INSTR_SET          = $(SSE_INSTR_SET) -msse2
SSE3_INSTR_SET          = $(SSE2_INSTR_SET) -msse3 -mssse3
SSE4_INSTR_SET          = $(SSE3_INSTR_SET) -msse4 -msse4a -msse4.1 -msse4.2
AVX_INSTR_SET           = -mavx -mvzeroupper
AVX2_INSTR_SET          = $(AVX_INSTR_SET) -mavx2
NEON_D32_INSTR_SET      = -mfpu=neon-vfpv4
ASIMD_INSTR_SET      	= -march=armv8-a+simd

ifeq ($(PLATFORM),BSD)
  ifeq ($(ARCHITECTURE), arm)
    CXX_OBJEXT             += $(ARM_IMPL) $(NEON_D32_IMPL)
  endif
endif

ifeq ($(ARCHITECTURE),i586)
  CXX_OBJEXT             += $(X86_IMPL) $(SSE_IMPL) $(SSE2_IMPL) $(SSE3_IMPL) $(SSE4_IMPL) $(AVX_IMPL) $(AVX2_IMPL)
else ifeq ($(ARCHITECTURE), x86_64)
  CXX_OBJEXT             += $(X86_IMPL) $(SSE_IMPL) $(SSE2_IMPL) $(SSE3_IMPL) $(SSE4_IMPL) $(AVX_IMPL) $(AVX2_IMPL)
else ifeq ($(ARCHITECTURE),armv7a)
  CXX_OBJEXT             += $(ARM_IMPL) $(NEON_D32_IMPL)
else ifeq ($(ARCHITECTURE),armv7ve)
  CXX_OBJEXT             += $(ARM_IMPL) $(NEON_D32_IMPL)
else ifeq ($(ARCHITECTURE),arm32)
  CXX_OBJEXT             += $(ARM_IMPL) $(NEON_D32_IMPL)
else ifeq ($(ARCHITECTURE),aarch64)
  CXX_OBJEXT             += $(AARCH64_IMPL) $(ASIMD_IMPL)
endif

# Define targets
.DEFAULT_GOAL = all
.PHONY: compile depend dep_clean all install uninstall
.PHONY: $(BUILD_DEPS)

compile: $(ARTIFACT_OBJ)

all: $(BUILD_ALL)

dep_clean:

$(CXX_DEPS): dep_clean
	@echo "  dep  [$(ARTIFACT_NAME)] $(CXX_DEPFILE)"
	@mkdir -p $(dir $(@))
	$(CXX) -MM -MT "\$$($(ARTIFACT_VARS)_BIN)/$(CXX_DEPTARGET)" -MF $(@) $(CXX_DEPFILE) $(CXXFLAGS) $(INCLUDE) $(CFLAGS_DEPS)

depend: $(CXX_DEPS)
	$(foreach dep,$(DEPENDENCIES) $(ARTIFACT_VARS),\
	  $(if $($(dep)_INC), \
	    $(eval SED_RULES += s/$(shell echo "$($(dep)_INC)" | sed "s/\\//\\\\\//g")/\$$$$\\($(dep)_INC\\)/g;)\
	  )\
	  $(if $($(dep)_BIN), \
	    $(eval SED_RULES += s/$(shell echo "$($(dep)_BIN)" | sed "s/\\//\\\\\//g")/\\$$$$\\($(dep)_BIN\\)/g;)\
	  )\
	)
	@cat $(CXX_DEPS) | sed -E "$(SED_RULES)" >Makefile.$(ARCHITECTURE).d

$(BUILD_DEPS):
	@echo "make $(notdir $($(@)_OBJ))"
	@$(MAKE) -s -C "$($(@)_PATH)" compile CONFIG="$(CONFIG)" NO_DEPENDENCIES="1" DEMO_TEST="0"

$(ARTIFACT_OBJ): $(BUILD_DEPS) $(CXX_OBJ) $(CXX_OBJEXT)
	@echo "  $(LD)   [$(ARTIFACT_NAME)] $(notdir $(ARTIFACT_OBJ))"
	@$(LD) -o $(ARTIFACT_OBJ) -r $(CXX_OBJ) $(CXX_OBJEXT)

$(ARTIFACT_LIB): $(ARTIFACT_OBJ)
	@echo "  $(CXX)  [$(ARTIFACT_NAME)] $(notdir $(ARTIFACT_LIB))"
	@$(CXX) -o $(ARTIFACT_LIB) $(LINKER_OBJS) $(ARTIFACT_OBJ) $(SO_FLAGS) $(LINKER_DEPS)
	
$(ARTIFACT_SLIB): $(ARTIFACT_OBJ)
	@echo "  $(AR)   [$(ARTIFACT_NAME)] $(notdir $(ARTIFACT_SLIB))"
	@$(AR) rcs $(ARTIFACT_SLIB) $(LINKER_OBJS) $(ARTIFACT_OBJ)

$(ARTIFACT_TESTBIN): $(ARTIFACT_OBJ)
	@echo "  $(CXX)  [$(ARTIFACT_NAME)] $(notdir $(ARTIFACT_TESTBIN))"
	@$(CXX) -o $(ARTIFACT_TESTBIN) $(LINKER_OBJS) $(ARTIFACT_OBJ) $(EXE_FLAGS) $(LINKER_DEPS)

$(CXX_OBJ) $(CXX_OBJEXT):
	@echo "  $(CXX)  [$(ARTIFACT_NAME)] $(CXX_FILE)"
	@mkdir -p $(dir $@)
	@$(CXX) -o $(@) -c $(CXX_FILE) -fPIC $(CXXFLAGS) $(ARTIFACT_MFLAGS) $(EXT_FLAGS) $(INCLUDE) $(CFLAGS_DEPS)

$(ARTIFACT_PC):
	@echo "prefix=$(PREFIX)" > "$(ARTIFACT_PC)"
	@echo "exec_prefix=$(BINDIR)" >> "$(ARTIFACT_PC)"
	@echo "includedir=$(INCDIR)" >> "$(ARTIFACT_PC)"
	@echo "libdir=$(LIBDIR)" >> "$(ARTIFACT_PC)"
	@echo "" >> $(ARTIFACT_PC) >> "$(ARTIFACT_PC)"
	@echo "Name: $($(ARTIFACT_VARS)_NAME)" >> "$(ARTIFACT_PC)"
	@echo "Description: $($(ARTIFACT_VARS)_DESC)" >> "$(ARTIFACT_PC)"
	@echo "Version: $($(ARTIFACT_VARS)_VERSION)" >> "$(ARTIFACT_PC)"
	@echo "Cflags: -I\$${includedir}" >> "$(ARTIFACT_PC)"
	@echo "Libs: -L\$${libdir} -l$(notdir $($(ARTIFACT_VARS)_NAME))" >> "$(ARTIFACT_PC)"

install: all
	@echo "Installing $($(ARTIFACT_VARS)_NAME)"
	@mkdir -p "$(DESTDIR)$(INCDIR)"
	@mkdir -p "$(DESTDIR)$(LIBDIR)/pkgconfig"
	@cp -r $($(ARTIFACT_VARS)_INC)/* "$(DESTDIR)$(INCDIR)/"
	@cp $(ARTIFACT_PC) "$(DESTDIR)$(LIBDIR)/pkgconfig/"
	@echo $(INSTALL) $(ARTIFACT_LIB) $(ARTIFACT_SLIB) -t "$(DESTDIR)$(LIBDIR)"
	@$(INSTALL) $(ARTIFACT_LIB) $(ARTIFACT_SLIB) -t "$(DESTDIR)$(LIBDIR)"
	@ln -sf $(notdir $(ARTIFACT_LIB)) "$(DESTDIR)$(LIBDIR)/$(ARTIFACT_LIBLINK)"
	@ln -sf $(notdir $(ARTIFACT_SLIB)) "$(DESTDIR)$(LIBDIR)/$(ARTIFACT_SLIBLINK)"
	@echo "Install OK"

uninstall:
	@echo "Uninstalling $($(ARTIFACT_VARS)_NAME)"
	@-rm -f "$(DESTDIR)$(LIBDIR)/$(notdir $(ARTIFACT_LIB))"
	@-rm -f "$(DESTDIR)$(LIBDIR)/$(ARTIFACT_LIBLINK)"
	@-rm -f "$(DESTDIR)$(LIBDIR)/$(ARTIFACT_SLIBLINK)"
	@-rm -f "$(DESTDIR)$(LIBDIR)/pkgconfig/$(notdir $(ARTIFACT_PC))"
	@echo rm -f $(CXX_INSTHEADERS)
	@-rm -f $(CXX_INSTHEADERS)
	@echo "Uninstall OK"

# Additional extended rules:
$(SSE_IMPL):        EXT_FLAGS=$(SSE_INSTR_SET)
$(SSE2_IMPL):       EXT_FLAGS=$(SSE2_INSTR_SET)
$(SSE3_IMPL):       EXT_FLAGS=$(SSE3_INSTR_SET)
$(SSE4_IMPL):       EXT_FLAGS=$(SSE4_INSTR_SET)
$(AVX_IMPL):        EXT_FLAGS=$(AVX_INSTR_SET)
$(AVX2_IMPL):       EXT_FLAGS=$(AVX2_INSTR_SET)
$(NEON_D32_IMPL):   EXT_FLAGS=$(NEON_D32_INSTR_SET)
$(ASIMD_IMPL):      EXT_FLAGS=$(ASIMD_INSTR_SET)

# Dependencies
-include $(CURDIR)/Makefile.$(ARCHITECTURE).d
