# Top-level -*- Makefile -*- for Unix Squeak!
#
# last edited: Wed Oct  7 14:02:40 1998 by piumarta (Ian Piumarta) on lebrac

# See src/GNUmakefile for more information about building the virtual
# machine.

# To build <target> on the local platform, use:
# 	make <target> [makevar overrides...]
#
# To use a non-default build directory, use:
#	make <target> VMBUILD="build-dir" [makevar overrides...]
#
# To build <target> for all platforms, use:
#	make all TARGET=<target> [makevar overrides...]
#
# To override the default list of build hosts, use:
#	make all HOSTS="list..." TARGET=<target> [makevar overrides...]
#
# (where <target> can be:
#	mkdir		- create the build directory
#	rmdir		- remove the build directory
#			- (empty) default: build "SqueakVM" from "interp.c"
# or any of the top-level targets defined in src/GNUmakefile).

export MAKEFLAGS=--no-print-directory

.PHONY:	default all mkdir rmdir release bin

include src/GNUmakefile.conf

HOSTS=	fantasio fricotin xombul bernin
PWD=	$(shell pwd)

default:
	$(MAKE) -C $(VMBUILD)

all:
	@for HOST in $(HOSTS) ; do \
	   echo ; echo "*** building on $$HOST:$(PWD)" ; echo ; \
	   rsh $$HOST "$(MAKE) -C $(PWD) $(TARGET) $(MAKEFLAGS)" ; \
	 done

mkdir:
	@echo "*** creating $(VMBUILD)..."
	@[ -d $(VMBUILD) ] || mkdir $(VMBUILD)
	@( cd $(VMBUILD) ; \
	   /bin/rm -f GNUmake* ; \
	   ln -s -f ../src/GNUmakefile . ; \
	   $(MAKE) -I../src links )

rmdir:
	@echo "*** removing $(VMBUILD)..."
	@[ -d $(VMBUILD) ] && /bin/rm -rf $(VMBUILD)

release:
	/bin/rm -rf ../release
	mkdir ../release
	cp -p  GNUmakefile ../release
	-[ -f interp.c ] && cp -p interp.c ../release
	-[ -f translator.c ] && cp -p translator.c ../release
	cp -pr bin ../release
	cp -pr util ../release
	cp -pr src ../release
	/bin/rm -f ../release/src/*~ ../release/util/*~

# pass all other targets down

.DEFAULT:
	$(MAKE) -C $(VMBUILD) $@
